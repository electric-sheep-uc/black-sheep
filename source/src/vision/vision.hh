#pragma once

#include <darknet.h>
#include <vector>

#include "runner.hh"

/**
 * vision.hh
 *
 * Processes the camera images and returns object candidates.
 **/
class Vision{
  public:
    enum IMG_TYPE{
      MASK,
      RGB
    };

    enum OBJECT{
      BALL = 0,
      GOAL = 1,
      LENGTH = 2
    };

    typedef struct{
      float x;
      float y;
      float w;
      float h;
      OBJECT obj;
    }Candidate;

  private:
    bool useDNN;
    unsigned char* mask;
    unsigned char* rgb;
    int width;
    int height;
    int area;
    std::vector<Vision::Candidate> cands;
    /* Old vision variables */
    int xDiv;
    int yDiv;
    Runner* lut;
    Runner* integral;
    Runner* ball;
    /*  DNN specific variables*/
    float* stb;
    float thresh;
    float hierThresh;
    network* net;
    int netArea;
    int netArea2;
    image raw;

  public:
    /**
     * Vision()
     *
     * Initialize the vision processing pipeline.
     **/
    Vision();

    /**
     * ~Vision()
     *
     * Destructor for the vision processing pipeline.
     **/
    ~Vision();

    /**
     * preprocess()
     *
     * Begin pre-processing the image for the vision system to process.
     *
     * @param frame The raw camera frame data.
     **/
    void preprocess(unsigned char* frame);

    /**
     * process()
     *
     * Process the camera image.
     **/
    void process();

    /**
     * getImage()
     *
     * Get an image from the vision processing. NOTE: This will fail with
     * multiple clients. This image can also be easily corrupted, but it's only
     * for debug purposes so we take the fasted option.
     *
     * @param imageType The image type to be cloned.
     * @return A clone of the current image in the array.
     **/
    unsigned char* getImage(IMG_TYPE imageType);

    /**
     * getCandidates()
     *
     * Get the current object candidates.
     *
     * @return The object candidates.
     **/
    std::vector<Vision::Candidate> getCandidates();
};
