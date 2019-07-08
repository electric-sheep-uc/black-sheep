#include "vision.hh"

#include "ball/ball.cc"
#include "integral/integral.cc"
#include "lut/lut.cc"
#include "../log.hh"
#include "../main.hh"

Vision::Vision(){
  /* Pull values from config */
  useDNN = *Main::config->getInt("vision.dnn.active").get() > 0;
  width = *Main::config->getInt("vision.camera.width").get();
  height = *Main::config->getInt("vision.camera.height").get();
  area = width * height;
  /* Allocate memory for image processing */
  rgb = (unsigned char*)malloc(area * 3 * sizeof(unsigned char));
  if(!useDNN){
    mask = (unsigned char*)malloc(area * 3 * sizeof(unsigned char));
    xDiv = *Main::config->getInt("vision.processing.x-div").get();
    yDiv = *Main::config->getInt("vision.processing.y-div").get();
    /* Create runners */
    lut = (Runner*)(new LUT());
    integral = (Runner*)(new Integral());
    ball = (Runner*)(new Ball((Integral*)integral, xDiv - 1, yDiv - 1));
  }else{
    mask = rgb;
    /* Prepare to run DDN */
    char* cfgFile = const_cast<char*>(Main::config->getString("vision.dnn.config-file").c_str());
    char* weightFile = const_cast<char*>(Main::config->getString("vision.dnn.weight-file").c_str());
    thresh = *Main::config->getDouble("vision.dnn.thresh").get();
    hierThresh = *Main::config->getDouble("vision.dnn.thresh").get();
    net = load_network_custom(cfgFile, weightFile, 0, 1);
    fuse_conv_batchnorm(*net);
    if(net->layers[net->n - 1].classes != OBJECT::LENGTH){
      WARN("Incorrect number of names for loaded network.");
    }
    netArea = net->w * net->h;
    netArea2 = netArea * 2;
    stb = (float*)malloc(netArea * 3 * sizeof(float));
    raw.w = net->w;
    raw.h = net->h;
    raw.c = 3;
    raw.data = stb;
    srand(2222222);
  }
}

Vision::~Vision(){
  free(rgb);
  if(useDNN){
    free(mask);
    free(stb);
  }
}

void Vision::preprocess(unsigned char* frame){
  Main::time->eventStart("vision", "pixel-convert");
  /* Loop over the pixels and allow the runners to process */
  #pragma omp parallel for collapse(2)
  for(int y = 0; y < height; y++){
    for(int x = 0; x < width; x += 2){
      Colour::YUV yuv0;
      Colour::YUV yuv1;
      Colour::RGB rgb0;
      Colour::RGB rgb1;
      int o = (x / 2) + (y * width / 2);
      int o4 = o * 4;
      int o6 = o * 6;
      /* Create the pixel */
      yuv0.y = frame[o4    ];
      yuv0.u = frame[o4 + 1];
      yuv0.v = frame[o4 + 3];
      yuv1.y = frame[o4 + 2];
      yuv1.u = frame[o4 + 1];
      yuv1.v = frame[o4 + 3];
      /* Clone RGB values from frame */
      rgb0 = Colour::slowYuvToRgb(yuv0);
      rgb1 = Colour::slowYuvToRgb(yuv1);
      memcpy(rgb + o6    , &rgb0, sizeof(Colour::RGB));
      memcpy(rgb + o6 + 3, &rgb1, sizeof(Colour::RGB));
      if(useDNN){
        /* Do nothing */
      }else{
        /* Generate a label for the pixel */
        unsigned char p0 = lut->process(x    , y, yuv0, 0);
        unsigned char p1 = lut->process(x + 1, y, yuv1, 0);
        /* Perform integral image on pixel */
        integral->process(x    , y, yuv0, p0);
        integral->process(x + 1, y, yuv1, p1);
        /* Draw default labels */
        mask[o6    ] = 0x00;
        mask[o6 + 1] = 0x00;
        mask[o6 + 2] = 0x00;
        mask[o6 + 3] = 0x00;
        mask[o6 + 4] = 0x00;
        mask[o6 + 5] = 0x00;
        /* Assign labels colours and draw to image */
        if((p0 & LUT::Mask::BALL) > 0){
          mask[o6    ] = 0xFF;
          mask[o6 + 3] = 0x00;
        }
        if((p1 & LUT::Mask::BALL) > 0){
          mask[o6    ] = 0x00;
          mask[o6 + 3] = 0xFF;
        }
      }
    }
  }
  Main::time->eventEnd("vision", "pixel-convert");
  if(useDNN){
    Main::time->eventStart("vision", "image-resize");
    /* Resize and convert to STB */
    float xScale = (float)(width - 1) / (net->w - 1);
    float yScale =  (float)(height - 1) / (net->h - 1);
    for(int y = 0; y < net->h; y++){
      int ynetw = y * net->w;
      for(int x = 0; x < net->h; x++){
        int s = ((int)(x * xScale) * 3) + ((int)(y * yScale) * 3 * width);
        int d = ynetw + x;
        stb[           d] = (float)rgb[s    ] / 255.0f;
        stb[netArea  + d] = (float)rgb[s + 1] / 255.0f;
        stb[netArea2 + d] = (float)rgb[s + 2] / 255.0f;
      }
    }
    Main::time->eventEnd("vision", "image-resize");
  }
}

void Vision::process(){
  /* Get new candidates */
  if(useDNN){
    Main::time->eventStart("vision", "network-predict");
    network_predict(*net, raw.data);
    Main::time->eventEnd("vision", "network-predict");
  }else{
    Main::time->eventStart("vision", "process-balls");
    /* Clear ball candidates for this loop */
    ((Ball*)ball)->clear();
    /* Ball detection. */
    Colour::YUV p;
    for(int y = 0; y < height; y += yDiv){
      for(int x = 0; x < width; x += xDiv){
        ball->process(x, y, p, 0);
      }
    }
    Main::time->eventEnd("vision", "process-balls");
  }
  Main::time->eventStart("vision", "process-candidates");
  if(useDNN){
    int nboxes = 0;
    detection* dets = get_network_boxes(
      net,
      net->w,
      net->h,
      thresh,
      hierThresh,
      0,
      1,
      &nboxes,
      0
    );
    /* Transfer best candidates */
    cands.clear();
    for(int i = 0; i < nboxes && i < *Main::config->getInt("vision.dnn.max-detect").get(); i++){
      int classID = -1;
      float prob = thresh;
      for(int z = 0; z < OBJECT::LENGTH; z++){
        if(dets[i].prob[z] > prob){
          classID = z;
          prob = dets[i].prob[z];
        }
      }
      if(classID >= 0){
        cands.push_back({
          dets[i].bbox.x,
          dets[i].bbox.y,
          dets[i].bbox.w,
          dets[i].bbox.h,
          (Vision::OBJECT)classID
        });
      }
    }
    free_detections(dets, nboxes);
  }else{
    ((Ball*)ball)->finalize();
    cands = ((Ball*)ball)->getCandidates();
  }
  Main::time->eventEnd("vision", "process-candidates");
}

unsigned char* Vision::getImage(IMG_TYPE imageType){
  switch(imageType){
    case MASK:
      return mask;
    case RGB:
      return rgb;
    default :
      WARN("Unsupported image type.");
      return rgb;
  }
  return rgb;
}

std::vector<Vision::Candidate> Vision::getCandidates(){
  return cands;
}
