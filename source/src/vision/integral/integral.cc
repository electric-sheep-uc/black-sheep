#include "integral.hh"

#include "../../main.hh"
#include "../../log.hh"

Integral::Integral(){
  width = *Main::config->getInt("vision.camera.width").get() + 1;
  height = *Main::config->getInt("vision.camera.height").get() + 1;
  ball = (int*)calloc(width * height, sizeof(int));
}

Integral::Integral(int w, int h){
  width = w + 1;
  height = h + 1;
  ball = (int*)calloc(width * height, sizeof(int));
}

Integral::~Integral(){
  free(ball);
}

unsigned int Integral::process(int x, int y, Colour::YUV p, unsigned char l){
  /* Pre-compute stream offset */
  ++x;
  ++y;
  int o = x + (y * width);
  /* Ball */
  ball[o] = (l & LUT::Mask::BALL) > 0 ? 1 : 0;
  ball[o] += ball[o - 1];
  ball[o] += ball[o - width];
  ball[o] -= ball[(o - width) - 1];
  /* NOTE: We don't want to return anything here. */
  return 0;
}

int Integral::getCount(LUT::Mask label, int x0, int y0, int x1, int y1){
  int* data;
  switch(label){
    case LUT::Mask::BALL:
      data = ball;
      break;
    default:
      WARN("Unimplemented label.");
      break;
  }
  ++x1;
  ++y1;
  return data[x1 + (y1 * width)] +
         data[x0 + (y0 * width)] -
         data[x0 + (y1 * width)] -
         data[x1 + (y0 * width)];
}
