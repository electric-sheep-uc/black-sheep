#include "ball.hh"

#include "../../main.hh"
#include "../../utils/math.hh"

Ball::Ball(Integral* i, int xSize, int ySize){
  integral = i;
  ballRatio = *Main::config->getDouble("vision.processing.ball-ratio").get();
  mergeRatio = *Main::config->getDouble("vision.processing.merge-ratio").get();
  width = *Main::config->getInt("vision.camera.width").get();
  height = *Main::config->getInt("vision.camera.height").get();
  xDiv = xSize;
  yDiv = ySize;
  minBallArea = (xDiv * yDiv) * ballRatio;
}

Ball::~Ball(){
  objects.clear();
}

unsigned int Ball::process(int x, int y, Colour::YUV p, unsigned char l){
  int x0 = x;
  int y0 = y;
  int x1 = x0 + xDiv;
  int y1 = y0 + yDiv;
  /* Find candidates */
  if(integral->getCount(LUT::Mask::BALL, x0, y0, x1, y1) >= minBallArea){
    /* Expand each candidate and find maximum edges */
    bool north = true;
    bool east = true;
    bool south = true;
    bool west = true;
    while((north || east || south || west) && x0 > 0 && x1 < width - 1 && y0 > 0 && y1 < height - 1){
      north = false;
      east = false;
      south = false;
      west = false;
      if(integral->getCount(LUT::Mask::BALL, x0, y0 - 1, x1, y0) >= ballRatio * (x1 - x0)){
        north = true;
        --y0;
      }
      if(integral->getCount(LUT::Mask::BALL, x1, y0, x1 + 1, y1) >= ballRatio * (y1 - y0)){
        east = true;
        ++x1;
      }
      if(integral->getCount(LUT::Mask::BALL, x0, y1, x1, y1 + 1) >= ballRatio * (x1 - x0)){
        south = true;
        ++y1;
      }
      if(integral->getCount(LUT::Mask::BALL, x0 - 1, y0, x0, y1) >= ballRatio * (y1 - y0)){
        west = true;
        --x0;
      }
    }
    /* TODO: Test candidates against features. */
    float x = (float)x0 / (float)width;
    float y = (float)y0 / (float)height;
    float w = ((float)x1 / (float)width) - x;
    float h = ((float)y1 / (float)height) - y;
    objects.push_back({x + (w / 2), y + (h / 2), w, h, Vision::OBJECT::BALL});
  }
  return 0;
}

void Ball::finalize(){
  /* Merge candidates */
  for(unsigned int i = 0; i < objects.size(); i++){
    for(unsigned int j = 0; j < objects.size(); j++){
      /* Don't merge with self */
      if(i != j){
        double oix0 = objects[i].x - (objects[i].w / 2);
        double oiy0 = objects[i].y - (objects[i].h / 2);
        double oix1 = objects[i].x + (objects[i].w / 2);
        double oiy1 = objects[i].y + (objects[i].h / 2);
        double ojx0 = objects[j].x - (objects[j].w / 2);
        double ojy0 = objects[j].y - (objects[j].h / 2);
        double ojx1 = objects[j].x + (objects[j].w / 2);
        double ojy1 = objects[j].y + (objects[j].h / 2);
        /* Check if merge ratio met */
        double aInt = MAX(0, MIN(oix1, ojx1) - MAX(oix0, ojx0)) *
                      MAX(0, MIN(oiy1, ojy1) - MAX(oiy0, ojy0));
        double aI = (oix1 - oix0) * (oiy1 - oiy0);
        double aJ = (ojx1 - ojx0) * (ojy1 - ojy0);
        double aMin = MIN(aI, aJ);
        if(aInt / aMin > mergeRatio){
          objects[i].x = MIN(objects[i].x, objects[j].x);
          objects[i].y = MIN(objects[i].y, objects[j].y);
          objects[i].w = MAX(objects[i].w, objects[j].w);
          objects[i].h = MAX(objects[i].h, objects[j].h);
          objects.erase(objects.begin() + j);
          j--;
        }
      }
    }
  }
  /* TODO: Order candidates relative to size (largest first). */
}

std::vector<Vision::Candidate> Ball::getCandidates(){
  return objects;
}

void Ball::clear(){
  objects.clear();
}
