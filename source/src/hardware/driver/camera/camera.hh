#pragma once

#include "/usr/include/libv4l2.h"
#include <linux/videodev2.h>

/**
 * camera.hh
 *
 * Handles capturing camera images.
 **/
class Camera{
  private:
    typedef struct{
      void *start;
      size_t length;
    } V4LBuffer;

    typedef struct{
      int fd;
      V4LBuffer* buffers;
      struct v4l2_buffer buffer;
      unsigned int numBuffers;
    } V4L;

    V4L cam;
    int width;
    int height;
    bool running;

  public:
    /**
     * Camera()
     *
     * Initialize the camera.
     **/
    Camera();

    /**
     * isRunning()
     *
     * Check to see whether the camera is actually running.
     *
     * @return True if running, otherwise false.
     **/
    bool isRunning();

    /**
     * update()
     *
     * Update the internal memory with a copy of the camera image. This method
     * blocks until a camera frame is available.
     **/
    void update();

    /**
     * getImage()
     *
     * Get a pointer to the currently stored image.
     *
     * @return Pointer to the current image.
     **/
    unsigned char* getImage();

    /**
     * getImageSize()
     *
     * Get the linear byte size of the image in RAM.
     *
     * @return The byte size of the image.
     **/
    int getImageSize();

    /**
     * getWidth()
     *
     * Get the width if the output image.
     *
     * @return The width of the output image, -1 on error.
     **/
    int getWidth();

    /**
     * getHeight()
     *
     * Get the height of the output image.
     *
     * @return The height of the output image, -1 on error.
     **/
    int getHeight();

    /**
     * close()
     *
     * Close the camera device.
     **/
    void close();

  private:
    /**
     * V4L_xioctl()
     *
     * Take control of a video for Linux device.
     *
     * @param fd The file descriptor of the camera device.
     * @param reqeust The requested format from the camera itself.
     * @param arg Arguments to be passed to the camera.
     * @return The return code after performing the operation.
     **/
    int V4L_xioctl(int fd, unsigned long int request, void* arg);
};
