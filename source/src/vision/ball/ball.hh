#pragma once

#include "../runner.hh"

#include <vector>

#include "../vision.hh"
#include "../integral/integral.hh"

/**
 * ball.hh
 *
 * Process the camera data and find ball candidates.
 **/
class Ball : public Runner{
  private:
    Integral* integral;
    double ballRatio;
    double mergeRatio;
    int width;
    int height;
    int xDiv;
    int yDiv;
    int minBallArea;
    std::vector<Vision::Candidate> objects;

  public:
    /**
     * Ball()
     *
     * Initialize the Ball runner.
     *
     * @param i Reference to the integral processing.
     * @param xSize The X divisor.
     * @param ySize The Y divisor.
     **/
    Ball(Integral* i, int xSize, int ySize);

    /**
     * ~Ball()
     *
     * Free up reserved memory.
     **/
    ~Ball();

    unsigned int process(int x, int y, Colour::YUV p, unsigned char l);

    /**
     * finalize()
     *
     * Reduce the number of candidates my merging similar areas and favouring
     * candidates that meet desired feature properties.
     **/
    void finalize();

    /**
     * getCandidates()
     *
     * Get the object candidates found.
     *
     * @return The object candidates.
     **/
    std::vector<Vision::Candidate> getCandidates();

    /**
     * clear()
     *
     * Clear the previous data.
     **/
    void clear();
};
