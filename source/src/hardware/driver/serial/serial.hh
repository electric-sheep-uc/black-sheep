#pragma once

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "../../../log.hh"

/**
 * serial.hh
 *
 * Basic serial interface.
 **/
class Serial{
  private:
    const char* device;

  public:
    int fd;

    /**
     * Serial()
     *
     * Initialize the variables used for serial communications.
     *
     * @param dev The device location.
     **/
    Serial(const char* dev){
      device = dev;
      fd = -1;
    }

    /**
     * ~Serial()
     *
     * Destructor for the serial object which makes sure the port is correctly
     * closed.
     **/
    ~Serial(){
      /* Attempt to close before destroying */
      closePort();
    }

    /**
     * openPort()
     *
     * Open the serial port for writing data.
     **/
    void openPort(){
      /* Open port for read/write, non-controlling and non-blocking */
      fd = open(device, O_RDWR | O_NOCTTY /*| O_NDELAY*/);
      LOGI("Smart controller fd -> ", fd);
      /* Check if the port was opened */
      if(!isActive()){
        WARNI("Not active, fd -> ", fd);
        fd = -1;
      }
    }

    /**
     * startComms()
     *
     * Starts any appropriate communications or specific port configuration.
     **/
    virtual void startComms() = 0;

    /**
     * closePort()
     *
     * Close the serial port if it is currently open.
     **/
    void closePort(){
      /* Make sure the file descriptor has been set */
      if(isActive()){
        close(fd);
        fd = -1;
      }
    }

    /**
     * isActive()
     *
     * Check whether the port is active.
     *
     * @return True if the port is open, false if there has been some error or
     * it is not open.
     **/
    bool isActive(){
      return fd >= 0;
    }

    /**
     * readByte()
     *
     * Read a single byte if it is available.
     *
     * @return The byte, otherwise -1.
     **/
    int readByte(){
      static unsigned char c = 0;
      /* Make sure this is worth it */
      if(!isActive()){
        return -1;
      }
      /* Perform the read */
      if(read(fd, &c, 1) >= 0){
        /* The character that was read */
        return (int)c;
      }else{
        /* Nothing to read */
        return -1;
      }
    }

    /**
     * writeByte()
     *
     * Write a single byte without checking the serial buffer.
     *
     * @param c The byte to be written.
     **/
    void writeByte(unsigned char c){
      /* Make sure this is worth it */
      if(!isActive()){
        return;
      }
      /* Perform the write */
      write(fd, &c, 1);
    }
};
