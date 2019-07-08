#pragma once

#include <ctime>
#include <string>

#include "vision/lut/colour.hh"
#include "utils/clock.hh"

#define CLASS() std::string(__FILE__).substr(std::string(__FILE__).find_last_of('/') + 1)
#define HEADER() printf("[%lli] %s->%s()::%i ", CLOCK::CURRENT_TIME_MILLIS(), CLASS().c_str(), __FUNCTION__, __LINE__)
#define LOG(s) {HEADER(); printf("%s\n", s);}
#define LOGB(s,b) {HEADER(); printf("%s0x%02X\n", s, b);}
#define LOGI(s,i) {HEADER(); printf("%s%i\n", s, i);}
#define LOGL(s,l) {HEADER(); printf("%s%lli\n", s, l);}
#define LOGF(s,f) {HEADER(); printf("%s%f\n", s, f);}
#define LOGM(s,m) {HEADER(); printf("%s%s\n", s, m);}
#define WARN(s) {HEADER(); printf("\033[0;31m%s\033[0m\n", s);}
#define WARNB(s,b) {HEADER(); printf("\033[0;31m%s\033[0m0x%02X\n", s, b);}
#define WARNI(s,i) {HEADER(); printf("\033[0;31m%s\033[0m%i\n", s, i);}
#define WARNL(s,l) {HEADER(); printf("\033[0;31m%s\033[0m%lli\n", s, l);}
#define WARNF(s,f) {HEADER(); printf("\033[0;31m%s\033[0m%i\n", s, f);}
#define WARNM(s,m) {HEADER(); printf("\033[0;31m%s\033[0m%s\n", s, m);}

class LOG{
  public:
    enum PIXEL{
      HSV,
      RGB,
      YUYV422
    };

  private:
    static unsigned char* CONVERT(
      int width,
      int height,
      unsigned char* data,
      unsigned long size,
      PIXEL from,
      PIXEL to
    ){
      Colour::HSV hsv0;
      Colour::HSV hsv1;
      Colour::RGB rgb0;
      Colour::RGB rgb1;
      Colour::YUV yuv0;
      Colour::YUV yuv1;
      unsigned char* temp;
      unsigned char* d;
      d = (unsigned char*)malloc(width * height * 3);
      for(int y = 0; y < height; y++){
        for(int x = 0; x < width / 2; x++){
          int o = x + (y * width / 2);
          switch(from){
            case RGB:
              rgb0.r = data[(o * 6) + 0];
              rgb0.g = data[(o * 6) + 1];
              rgb0.b = data[(o * 6) + 2];
              rgb1.r = data[(o * 6) + 3];
              rgb1.g = data[(o * 6) + 4];
              rgb1.b = data[(o * 6) + 5];
              switch(to){
                case HSV:
                  hsv0 = Colour::rgbToHsv(rgb0);
                  hsv1 = Colour::rgbToHsv(rgb1);
                  d[(o * 6) + 0] = hsv0.h;
                  d[(o * 6) + 1] = hsv0.s;
                  d[(o * 6) + 2] = hsv0.v;
                  d[(o * 6) + 3] = hsv1.h;
                  d[(o * 6) + 4] = hsv1.s;
                  d[(o * 6) + 5] = hsv1.v;
                  break;
                case RGB:
                  d[(o * 6) + 0] = rgb0.r;
                  d[(o * 6) + 1] = rgb0.g;
                  d[(o * 6) + 2] = rgb0.b;
                  d[(o * 6) + 3] = rgb1.r;
                  d[(o * 6) + 4] = rgb1.g;
                  d[(o * 6) + 5] = rgb1.b;
                  break;
                default:
                  WARN("Not a supported colour conversion.");
                  break;
              }
              break;
            case YUYV422:
              yuv0.y = data[(o * 4) + 0];
              yuv0.u = data[(o * 4) + 1];
              yuv0.v = data[(o * 4) + 3];
              yuv1.y = data[(o * 4) + 2];
              yuv1.u = data[(o * 4) + 1];
              yuv1.v = data[(o * 4) + 3];
              switch(to){
                case HSV:
                  temp = CONVERT(width, height, data, size, from, PIXEL::RGB);
                  d = CONVERT(width, height, temp, size, PIXEL::RGB, PIXEL::HSV);
                  free(temp);
                  return d;
                case RGB:
                  rgb0 = Colour::yuvToRgb(yuv0);
                  rgb1 = Colour::yuvToRgb(yuv1);
                  d[(o * 6) + 0] = rgb0.r;
                  d[(o * 6) + 1] = rgb0.g;
                  d[(o * 6) + 2] = rgb0.b;
                  d[(o * 6) + 3] = rgb1.r;
                  d[(o * 6) + 4] = rgb1.g;
                  d[(o * 6) + 5] = rgb1.b;
                  break;
                default:
                  WARN("Not a supported colour conversion.");
                  return d;
              }
              break;
            default:
              WARN("Not a supported colour conversion.");
              return d;
          }
        }
      }
      return d;
    }

  public:
    static void SAVE_PPM(
      const char* name,
      int width,
      int height,
      unsigned char* data,
      unsigned long size,
      PIXEL from,
      PIXEL to
    ){
      SAVE_PPM(name, width, height, CONVERT(width, height, data, size, from, to), width * height * 3);
    }

  private:
    static void SAVE_PPM(
      const char* name,
      int width,
      int height,
      unsigned char* data,
      unsigned long size
    ){
      FILE *fout;
      fout = fopen(name, "w");
      if(!fout){
        WARNM("Unable to save image -> ", name);
      }
      fprintf(fout, "P6\n%d %d 255\n", width, height);
      fwrite(data, size, 1, fout);
      fclose(fout);
      free(data);
    }
};
