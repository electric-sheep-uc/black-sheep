#pragma once

#include "../lut/lut.hh"

/**
 * integral.hh
 *
 * Perform integral image on the data.
 **/
class Integral : public Runner{
  private:
    int width;
    int height;
    int* ball;

  public:
    /**
     * Integral()
     *
     * Initialize the Integral runner.
     **/
    Integral();

    /**
     * Integral()
     *
     * Initialize the Integral runner.
     *
     * @param w Width of the image.
     * @param h Height of the image.
     **/
    Integral(int w, int h);

    /**
     * ~Integral()
     *
     * Free up reserved memory.
     **/
    ~Integral();

    unsigned int process(int x, int y, Colour::YUV p, unsigned char l);

    /**
     * getCount()
     *
     * Get the count of found labels for an area of interest.
     *
     * @param label The label of interest.
     * @param x0 Upper left.
     * @param y0 Upper left.
     * @param x1 Lower right.
     * @param y1 Lower right.
     * @return The count.
     **/
    int getCount(LUT::Mask label, int x0, int y0, int x1, int y1);
};
