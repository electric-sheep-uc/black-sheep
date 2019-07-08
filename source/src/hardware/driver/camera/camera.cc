#include "camera.hh"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/types.h>

#include "../../../main.hh"
#include "../../../log.hh"

Camera::Camera(){
  running = true;
  /* Pull in configuration values */
  const char* dev = Main::config->getString("vision.camera.interface").c_str();
  width = *Main::config->getInt("vision.camera.width").get();
  height = *Main::config->getInt("vision.camera.height").get();
  /* Get camera file descriptor */
  cam.fd = v4l2_open(dev, O_RDWR | O_NONBLOCK, 0);
  if(cam.fd < 0){
    WARNM("Failed to open camera interface -> ", dev);
    running = false;
  }
  /* Query the device capabilities */
  struct v4l2_capability cap;
  if(Camera::V4L_xioctl(cam.fd, VIDIOC_QUERYCAP, &cap) < 0){
    WARN("Unable to retrieve device capabilities.");
    running = false;
  }
  /* Ensure we can capture video frames (single-planar) */
  if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)){
    WARN("Unable to capture video.");
    running = false;
  }
  /* Ensure we can stream images */
  if(!(cap.capabilities & V4L2_CAP_STREAMING)){
    WARN("Unable to capture video.");
    running = false;
  }
  /* Set the format */
  struct v4l2_format fmt;
  memset(&(fmt), 0, sizeof(fmt));
  fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  fmt.fmt.pix.width = width;
  fmt.fmt.pix.height = height;
  fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
  fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
  /* Take control of the camera */
  if(Camera::V4L_xioctl(cam.fd, VIDIOC_S_FMT, &fmt) < 0){
    WARN("Unable to set camera format.");
    running = false;
  }
  /* Check whether pixel format is supported */
  if(fmt.fmt.pix.pixelformat != V4L2_PIX_FMT_YUYV){
    WARN("Camera doesn't support pixel format.");
    running = false;
  }
  /* Check if the camera returned our requested format */
  if((fmt.fmt.pix.width != (unsigned int)width) || (fmt.fmt.pix.height != (unsigned int)height)){
    WARN("Camera failed to open in desired resolution.");
    running = false;
  }
  /* Regardless, update the width and height */
  width = fmt.fmt.pix.width;
  height = fmt.fmt.pix.height;
  struct v4l2_control ctrl;
  /* Set the camera brightness */
  ctrl.id = V4L2_CID_BRIGHTNESS;
  ctrl.value = 128;
  if(Camera::V4L_xioctl(cam.fd, VIDIOC_S_CTRL, &ctrl) < 0){
    WARN("Unable to set camera brightness.");
    running = false;
  }
  /* Set the camera contrast */
  ctrl.id = V4L2_CID_CONTRAST;
  ctrl.value = 128;
  if(Camera::V4L_xioctl(cam.fd, VIDIOC_S_CTRL, &ctrl) < 0){
    WARN("Unable to set camera contrast.");
    running = false;
  }
  /* Set the camera saturation */
  ctrl.id = V4L2_CID_SATURATION;
  ctrl.value = 64;
  if(Camera::V4L_xioctl(cam.fd, VIDIOC_S_CTRL, &ctrl) < 0){
    WARN("Unable to set camera saturation.");
    running = false;
  }
  /* Set the camera hue */
  ctrl.id = V4L2_CID_HUE;
  ctrl.value = 0;
  if(Camera::V4L_xioctl(cam.fd, VIDIOC_S_CTRL, &ctrl) < 0){
    WARN("Unable to set camera hue.");
    running = false;
  }
  /* Set the camera gamma */
  ctrl.id = V4L2_CID_GAMMA;
  ctrl.value = 4;
  if(Camera::V4L_xioctl(cam.fd, VIDIOC_S_CTRL, &ctrl) < 0){
    WARN("Unable to set camera gamma.");
    running = false;
  }
  /* Set the camera sharpness */
  ctrl.id = V4L2_CID_SHARPNESS;
  ctrl.value = 4;
  if(Camera::V4L_xioctl(cam.fd, VIDIOC_S_CTRL, &ctrl) < 0){
    WARN("Unable to set camera sharpness.");
    running = false;
  }
  /* Set the camera backlight compensation */
  ctrl.id = V4L2_CID_BACKLIGHT_COMPENSATION;
  ctrl.value = 0;
  if(Camera::V4L_xioctl(cam.fd, VIDIOC_S_CTRL, &ctrl) < 0){
    WARN("Unable to set camera backlight compensation.");
    running = false;
  }
  /* Request that the camera maps to memory */
  struct v4l2_requestbuffers req;
  memset(&(req), 0, sizeof(req));
  req.count = 1;
  req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  req.memory = V4L2_MEMORY_MMAP;
  if(Camera::V4L_xioctl(cam.fd, VIDIOC_REQBUFS, &req) < 0){
    WARN("Unable to map camera memory to buffers.");
    running = false;
  }
  /* Setup buffers */
  cam.buffers = (Camera::V4LBuffer*)calloc(req.count, sizeof(*cam.buffers));
  for(cam.numBuffers = 0; cam.numBuffers < req.count; ++cam.numBuffers){
    memset(&(cam.buffer), 0, sizeof(cam.buffer));
    cam.buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    cam.buffer.memory = V4L2_MEMORY_MMAP;
    cam.buffer.index = cam.numBuffers;
    if(Camera::V4L_xioctl(cam.fd, VIDIOC_QUERYBUF, &cam.buffer)){
      WARN("Unable to query buffer.");
      running = false;
    }
    cam.buffers[cam.numBuffers].length = cam.buffer.length;
    cam.buffers[cam.numBuffers].start = v4l2_mmap(NULL, cam.buffer.length,
      PROT_READ | PROT_WRITE, MAP_SHARED, cam.fd, cam.buffer.m.offset);
    if(MAP_FAILED == cam.buffers[cam.numBuffers].start){
      WARN("Camera failed to map memory.");
      running = false;
    }
  }
  for(unsigned int i = 0; i < cam.numBuffers; ++i){
    memset(&(cam.buffer), 0, sizeof(cam.buffer));
    cam.buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    cam.buffer.memory = V4L2_MEMORY_MMAP;
    cam.buffer.index = i;
    if(Camera::V4L_xioctl(cam.fd, VIDIOC_QBUF, &cam.buffer) < 0){
      WARN("Unable to initialize buffer.");
      running = false;
    }
  }
  enum v4l2_buf_type type;
  type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  if(Camera::V4L_xioctl(cam.fd, VIDIOC_STREAMON, &type) < 0){
    WARN("Unable to start stream.");
    running = false;
  }
}

bool Camera::isRunning(){
  return running;
}

void Camera::update(){
  fd_set fds;
  struct timeval tv;
  int r;
  do{
    FD_ZERO(&fds);
    FD_SET(cam.fd, &fds);
    /* Timeout */
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    r = select(cam.fd + 1, &fds, NULL, NULL, &tv);
  }while((r < 0 && (errno == EINTR)));
  if(r < 0){
    WARN("Camera failed to update.");
  }
  memset(&(cam.buffer), 0, sizeof(cam.buffer));
  cam.buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  cam.buffer.memory = V4L2_MEMORY_MMAP;
  if(Camera::V4L_xioctl(cam.fd, VIDIOC_DQBUF, &cam.buffer) < 0){
    WARN("Unable to dequeue buffer.");
  }
  if(Camera::V4L_xioctl(cam.fd, VIDIOC_QBUF, &cam.buffer) < 0){
    WARN("Unable to queue buffer.");
  }
}

unsigned char* Camera::getImage(){
  return ((unsigned char*)cam.buffers[cam.buffer.index].start);
}

int Camera::getImageSize(){
  return cam.buffers[cam.buffer.index].length;
}

int Camera::getWidth(){
  return width;
}

int Camera::getHeight(){
  return height;
}

void Camera::close(){
  running = false;
  enum v4l2_buf_type type;
  type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  Camera::V4L_xioctl(cam.fd, VIDIOC_STREAMOFF, &type);
  for(unsigned int i = 0; i < cam.numBuffers; ++i){
    v4l2_munmap(cam.buffers[i].start, cam.buffers[i].length);
  }
  v4l2_close(cam.fd);
  free(cam.buffers);
}

int Camera::V4L_xioctl(int fd, unsigned long int request, void* arg){
  int r = -1;
  do{
    r = v4l2_ioctl(fd, request, arg);
  }while(r < 0 && ((errno == EINTR) || (errno == EAGAIN)));
  if(r < 0){
    switch(errno){
      case EAGAIN:
        WARNM("Camera failed to handle I/O, code -> ", "EAGAIN");
        break;
      case EINVAL:
        WARNM("Camera failed to handle I/O, code -> ", "EINVAL");
        break;
      case ENOMEM:
        WARNM("Camera failed to handle I/O, code -> ", "ENOMEM");
        break;
      case EIO:
        WARNM("Camera failed to handle I/O, code -> ", "EIO");
        break;
      default:
        WARNI("Camera failed to handle I/O, code -> ", errno);
        break;
    }
  }
  return r;
}
