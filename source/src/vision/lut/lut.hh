#pragma once

#include "colour.hh"
#include "../runner.hh"

/**
 * lut.hh
 *
 * Look up table to transform pixels into labels.
 **/
class LUT : public Runner{
  public:
    enum Mask{
      BALL = 1
    };
  private:
    unsigned char* lut;

  public:
    /**
     * LUT()
     *
     * Initialize the LUT runner.
     **/
    LUT();

    /**
     * ~LUT()
     *
     * Free up reserved memory.
     **/
    ~LUT();

    unsigned int process(int x, int y, Colour::YUV p, unsigned char l);
};
