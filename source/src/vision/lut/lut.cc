#include "lut.hh"

#include "../../main.hh"

LUT::LUT(){
  int hMin = *Main::config->getInt("vision.labels.ball.h.min").get();
  int hMax = *Main::config->getInt("vision.labels.ball.h.max").get();
  int sMin = *Main::config->getInt("vision.labels.ball.s.min").get();
  int sMax = *Main::config->getInt("vision.labels.ball.s.max").get();
  int vMin = *Main::config->getInt("vision.labels.ball.v.min").get();
  int vMax = *Main::config->getInt("vision.labels.ball.v.max").get();
  lut = (unsigned char*)malloc(256 * 256 * 256 * sizeof(unsigned char));
  Colour::YUV yuv;
  Colour::RGB rgb;
  Colour::HSV hsv;
  hMax -= hMin;
  hMax = hMax >= 0 ? hMax : 255 - hMax;
  sMax -= sMin;
  sMax = sMax >= 0 ? sMax : 255 - sMax;
  vMax -= vMin;
  vMax = vMax >= 0 ? vMax : 255 - vMax;
  /* Label the data */
  for(int y = 0; y <= 255; y++){
    for(int u = 0; u <= 255; u++){
      for(int v = 0; v <= 255; v++){
        yuv.y = y;
        yuv.u = u;
        yuv.v = v;
        rgb = Colour::slowYuvToRgb(yuv);
        hsv = Colour::slowRgbToHsv(rgb);
        /* Clear */
        lut[y << 16 | u << 8 | v] = 0;
        /* Ball */
        if(
          hsv.h - hMin >= 0 && hsv.h - hMin <= hMax &&
          hsv.s - sMin >= 0 && hsv.s - sMin <= sMax &&
          hsv.v - vMin >= 0 && hsv.v - vMin <= vMax
        ){
          lut[y << 16 | u << 8 | v] |= Mask::BALL;
        }
      }
    }
  }
}

LUT::~LUT(){
  free(lut);
}

unsigned int LUT::process(int x, int y, Colour::YUV p, unsigned char l){
  return lut[p.y << 16 | p.u << 8 | p.v];
}
