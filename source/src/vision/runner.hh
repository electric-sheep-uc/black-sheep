#pragma once

#include "lut/colour.hh"

/**
 * runner.hh
 *
 * A template for running image processing.
 **/
class Runner{
  public:
    /**
     * process()
     *
     * Process a given pixel.
     *
     * @param x The X position of the pixel.
     * @param y The Y position of the pixel.
     * @param p The pixel.
     * @param l The pixel label.
     * @return The replacement pixel.
     **/
    virtual unsigned int process(int x, int y, Colour::YUV p, unsigned char l) = 0;
};
