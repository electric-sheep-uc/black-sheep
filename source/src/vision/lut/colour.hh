#pragma once

#include "../../utils/math.hh"

#define GET_R_FROM_YUV(y, u, v) ((298 * y + 409 * v + 128) >> 8)
#define GET_G_FROM_YUV(y, u, v) ((298 * y - 100 * u - 208 * v + 128) >> 8)
#define GET_B_FROM_YUV(y, u, v) ((298 * y + 516 * u + 128) >> 8)

#define ENABLE_COLOUR_LUT FALSE

/**
 * colour.hh
 *
 * Perform colour conversions.
 **/
class Colour{
  public:
    typedef struct{
      unsigned char y;
      unsigned char u;
      unsigned char v;
    }YUV;

    typedef struct{
      unsigned char h;
      unsigned char s;
      unsigned char v;
    }HSV;

    typedef struct{
      unsigned char r;
      unsigned char g;
      unsigned char b;
    }RGB;

#if ENABLE_COLOUR_LUT == TRUE
    static RGB* y2r;
    static HSV* r2h;
#endif

    /**
     * slowYuvToRgb()
     *
     * Convert a single YUV pixel to RGB.
     *
     * @param yuv The YUV pixel to be converted.
     * @return Reference to the RGB pixel.
     **/
    static RGB slowYuvToRgb(YUV yuv){
      RGB rgb;
      int y = yuv.y - 16;
      int u = yuv.u - 128;
      int v = yuv.v - 128;
      rgb.r = CLAMP(GET_R_FROM_YUV(y, u, v), 0, 255);
      rgb.g = CLAMP(GET_G_FROM_YUV(y, u, v), 0, 255);
      rgb.b = CLAMP(GET_B_FROM_YUV(y, u, v), 0, 255);
      return rgb;
    }

    /**
     * slowRgbToHsv()
     *
     * Convert a single RGB pixel to HSV.
     *
     * @param rgb The RGB pixel to be converted.
     * @return Reference to the HSV pixel.
     **/
    static HSV slowRgbToHsv(RGB rgb){
      HSV hsv;
      int min = MIN(rgb.r, MIN(rgb.g, rgb.b));
      int max = MAX(rgb.r, MAX(rgb.g, rgb.b));
      /* V */
      hsv.v = max;
      if(hsv.v == 0){
        hsv.h = 0;
        hsv.s = 0;
        /* Nothing else to compute */
        return hsv;
      }
      /* S */
      hsv.s = 255 * (max - min) / hsv.v;
      if(hsv.s == 0){
        hsv.h = 0;
        /* Nothing else to compute */
        return hsv;
      }
      /* H */
      if(max == rgb.r){
        hsv.h =   0 + 43 * (rgb.g - rgb.b) / (max - min);
      }else if(max == rgb.g){
        hsv.h =  85 + 43 * (rgb.b - rgb.r) / (max - min);
      }else{
        hsv.h = 171 + 43 * (rgb.r - rgb.g) / (max - min);
      }
      return hsv;
    }

#if ENABLE_COLOUR_LUT == TRUE
    /**
     * init()
     *
     * Initialize the colour space look up tables.
     **/
    static void init(){
      y2r = (RGB*)malloc(256 * 256 * 256 * sizeof(RGB));
      for(int y = 0; y <= 255; y++){
        for(int u = 0; u <= 255; u++){
          for(int v = 0; v <= 255; v++){
            YUV yuv;
            yuv.y = y;
            yuv.u = u;
            yuv.v = v;
            RGB rgb = slowYuvToRgb(yuv);
            y2r[y << 16 | u << 8 | v].r = rgb.r;
            y2r[y << 16 | u << 8 | v].g = rgb.g;
            y2r[y << 16 | u << 8 | v].b = rgb.b;
          }
        }
      }
      r2h = (HSV*)malloc(256 * 256 * 256 * sizeof(HSV));
      for(int r = 0; r <= 255; r++){
        for(int g = 0; g <= 255; g++){
          for(int b = 0; b <= 255; b++){
            RGB rgb;
            rgb.r = r;
            rgb.g = g;
            rgb.b = b;
            HSV hsv = slowRgbToHsv(rgb);
            r2h[r << 16 | g << 8 | b].h = hsv.h;
            r2h[r << 16 | g << 8 | b].s = hsv.s;
            r2h[r << 16 | g << 8 | b].v = hsv.v;
          }
        }
      }
    }
#endif

#if ENABLE_COLOUR_LUT == TRUE
    /**
     * yuvToRgb()
     *
     * Convert a single YUV pixel to RGB.
     *
     * @param yuv The YUV pixel to be converted.
     * @return Reference to the RGB pixel.
     **/
    static RGB yuvToRgb(YUV yuv){
      return y2r[yuv.y << 16 | yuv.u << 8 | yuv.v];
    }
#endif

#if ENABLE_COLOUR_LUT == TRUE
    /**
     * rgbToHsv()
     *
     * Convert a single RGB pixel to HSV.
     *
     * @param rgb The RGB pixel to be converted.
     * @return Reference to the HSV pixel.
     **/
    static HSV rgbToHsv(RGB rgb){
      return r2h[rgb.r << 16 | rgb.g << 8 | rgb.b];
    }
#endif
};

/* NOTE: C++ gets upset about undefined variables at compile time. */
#if ENABLE_COLOUR_LUT == TRUE
Colour::RGB* Colour::y2r = NULL;
Colour::HSV* Colour::r2h = NULL;
#endif
