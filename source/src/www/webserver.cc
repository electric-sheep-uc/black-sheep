#include "webserver.hh"

#define __STDC_FORMAT_MACROS
#include "EmbeddableWebServer/EmbeddableWebServer.h"

#include <jpeglib.h>
#include <string>

#include "../main.hh"

/* NOTE: Slight hack as this library is written like C. */
int width;
int height;
unsigned char* img;

WebServer::WebServer(){
  port = *Main::config->getInt("www.port").get();
  width = *Main::config->getInt("vision.camera.width").get();
  height = *Main::config->getInt("vision.camera.height").get();
  img = (unsigned char*)malloc(width * height * 3 * sizeof(unsigned char));
}

WebServer::~WebServer(){
  free(img);
}

/**
 * init_buffer()
 *
 * Hook for JPEG buffer initialization.
 *
 * @param cinfo The compression information.
 **/
void init_buffer(jpeg_compress_struct* cinfo){
}

/**
 * empty_buffer()
 *
 * Hook for JPEG buffer cleaning.
 *
 * @param cinfo The compression information.
 * @return True means buffer is empty, otherwise false.
 **/
boolean empty_buffer(jpeg_compress_struct* cinfo){
  return true;
}

/**
 * term_buffer()
 *
 * Hook for JPEG terminal buffer.
 *
 * @param cinfo The compression information.
 **/
void term_buffer(jpeg_compress_struct* cinfo){
}

void WebServer::run(){
  acceptConnectionsUntilStoppedFromEverywhereIPv4(NULL, port);
}

struct Response* createResponseForRequest(
  const struct Request* request,
  struct Connection* connection){
  /* Serve static files */
  if(request->pathDecoded == strstr(request->pathDecoded, "/static")){
    return responseAllocServeFileFromRequestPath("/static", request->path, request->pathDecoded, "./www/static");
  }
  /* Handle JSON operations */
  if(request->pathDecoded == strstr(request->pathDecoded, "/json")){
    /* Check if configuration related request */
    if(request->pathDecoded == strstr(request->pathDecoded, "/json/config")){
      /* Check if all required */
      if(request->pathDecoded == strstr(request->pathDecoded, "/json/config/all")){
        return responseAllocJSONWithFormat(Main::config->getDump().c_str());
      }
      /* Check if template required */
      if(request->pathDecoded == strstr(request->pathDecoded, "/json/config/temp")){
        return responseAllocJSONWithFormat(Main::config->getTempDump().c_str());
      }
      /* Check if we are sent an update */
      if(request->pathDecoded == strstr(request->pathDecoded, "/json/config/update")){
        std::string params = request->body.contents;
        unsigned int pair;
        /* Find the key value pairs */
        for(unsigned int x = 0; x < params.length(); x = ++pair){
          pair = params.find_first_of('&', x);
          pair = pair != std::string::npos ? pair : params.length();
          int split = params.find_first_of('=', x);
          std::string key = params.substr(x, split - x).c_str();
          /* NOTE: Use the decoder offered by the server software. */
          //std::string val = params.substr(split + 1, pair - (split + 1)).c_str();
          std::string val = strdupDecodePOSTParam((key + "=").c_str(), request, "");
          /* Update JSON configuration */
          Main::config->setObject(key, val);
        }
      }
      /* Tell the config to save a delta of itself */
      if(request->pathDecoded == strstr(request->pathDecoded, "/json/config/save")){
        Main::config->write();
        return responseAllocHTMLWithFormat("OK");
      }
    }
    /* Check if motion related request */
    if(request->pathDecoded == strstr(request->pathDecoded, "/json/motion")){
      return responseAllocJSONWithFormat(Main::mot->getPoseDump().c_str());
    }
    /* Check if timing related request */
    if(request->pathDecoded == strstr(request->pathDecoded, "/json/timing")){
      return responseAllocJSONWithFormat(Main::time->getData().c_str());
    }
  }
  /* Handle vision operations */
  if(request->pathDecoded == strstr(request->pathDecoded, "/vision")){
    /* Give a list of possible debug options */
    if(request->pathDecoded == strstr(request->pathDecoded, "/vision/options")){
      return responseAllocWithFormat(
        200,
        "OK",
        "application/json",
        "{\"types\":[{\"type\":\"mask\"},{\"type\":\"rgb\"}]}"
      );
    }
    /* Requester wants an actual image */
    if(request->pathDecoded == strstr(request->pathDecoded, "/vision/image")){
      std::vector<Vision::Candidate> cands = Main::vis->getCandidates();
      /* Requester wants an mask image */
      if(request->pathDecoded == strstr(request->pathDecoded, "/vision/image/mask")){
        memcpy(
          img,
          Main::vis->getImage(Vision::IMG_TYPE::MASK),
          width * height * 3 * sizeof(unsigned char)
        );
      }
      /* Requester wants an RGB image */
      if(request->pathDecoded == strstr(request->pathDecoded, "/vision/image/rgb")){
        memcpy(
          img,
          Main::vis->getImage(Vision::IMG_TYPE::RGB),
          width * height * 3 * sizeof(unsigned char)
        );
      }
      /* Draw bounding boxes */
      int drawThick = *Main::config->getInt("vision.draw-thickness").get();
      for(unsigned int i = 0; i < cands.size(); i++){
        Vision::Candidate c = cands[i];
        unsigned char r = 0;
        unsigned char g = 0;
        unsigned char b = 0;
        switch(c.obj){
          case Vision::OBJECT::BALL :
            r = 0xFF;
            g = 0xFF;
            b = 0xFF;
            break;
          case Vision::OBJECT::GOAL :
            r = 0xFF;
            g = 0xFF;
            b = 0x00;
            break;
          case Vision::OBJECT::LENGTH :
          default :
            WARNI("Unsupported label type ", c.obj);
            break;
        }
        int x0 = CLAMP((c.x - (c.w / 2)) * width , 0, width  - 1);
        int y0 = CLAMP((c.y - (c.h / 2)) * height, 0, height - 1);
        int x1 = CLAMP((c.x + (c.w / 2)) * width , 0, width  - 1);
        int y1 = CLAMP((c.y + (c.h / 2)) * height, 0, height - 1);
        for(int y = y0; y < y1; y++){
          for(int x = CLAMP(x0 - drawThick, 0, width - 1); x < x0; x++){
            /* Left */
            img[(y * width * 3) + (x * 3) + 0] = r;
            img[(y * width * 3) + (x * 3) + 1] = g;
            img[(y * width * 3) + (x * 3) + 2] = b;
          }
          for(int x = x1; x < CLAMP(x1 + drawThick, 0, width - 1); x++){
            /* Right */
            img[(y * width * 3) + (x * 3) + 0] = r;
            img[(y * width * 3) + (x * 3) + 1] = g;
            img[(y * width * 3) + (x * 3) + 2] = b;
          }
        }
        for(int x = x0; x < x1; x++){
          for(int y = CLAMP(y0 - drawThick, 0, height - 1); y < y0; y++){
            /* Top */
            img[(y * width * 3) + (x * 3) + 0] = r;
            img[(y * width * 3) + (x * 3) + 1] = g;
            img[(y * width * 3) + (x * 3) + 2] = b;
          }
          for(int y = y1; y < CLAMP(y1 + drawThick, 0, height - 1); y++){
            /* Bottom */
            img[(y * width * 3) + (x * 3) + 0] = r;
            img[(y * width * 3) + (x * 3) + 1] = g;
            img[(y * width * 3) + (x * 3) + 2] = b;
          }
        }
      }
      /* TODO: Pre-compute the compression headers. */
      struct jpeg_compress_struct cinfo;
      struct jpeg_error_mgr jerr;
      struct jpeg_destination_mgr dmgr;
      /* Allocate memory for the image */
      JOCTET* out_buffer = new JOCTET[width * height * 3];
      /* Setup image destination buffers */
      dmgr.init_destination = init_buffer;
      dmgr.empty_output_buffer = empty_buffer;
      dmgr.term_destination = term_buffer;
      dmgr.next_output_byte = out_buffer;
      dmgr.free_in_buffer = width * height * 3;
      /* Setup compression settings */
      cinfo.err = jpeg_std_error(&jerr);
      jpeg_create_compress(&cinfo);
      cinfo.dest = &dmgr;
      cinfo.image_width = width;
      cinfo.image_height = height;
      cinfo.input_components = 3;
      cinfo.in_color_space = JCS_RGB;
      /* Initialize compression parameters */
      jpeg_set_defaults(&cinfo);
      jpeg_set_quality(
        &cinfo,
        *Main::config->getInt("vision.processing.debug-compression").get(),
        true
      );
      jpeg_start_compress(&cinfo, true);
      /* Copy data to JPEG buffers */
      JSAMPROW row_ptr;
      while(cinfo.next_scanline < cinfo.image_height){
        row_ptr = (JSAMPROW)&img[cinfo.next_scanline * width * 3];
        jpeg_write_scanlines(&cinfo, &row_ptr, 1);
      }
      /* Compress */
      jpeg_finish_compress(&cinfo);
      /* Clean-up and send */
      jpeg_destroy_compress(&cinfo);
      /* Send to browser */
      const char headers[] =
        "HTTP/1.1 200 0K\r\n"
        "Content-Type: image/jpeg\r\n\r\n";
      send(connection->socketfd, headers, strlen(headers), MSG_NOSIGNAL);
      send(connection->socketfd, out_buffer, width * height * 3, MSG_NOSIGNAL);
      free(out_buffer);
      return NULL;
    }
  }
  /* Serve root by default */
  return responseAllocServeFileFromRequestPath("/", "/index.html", "/index.html", "./www");
}
