#pragma once

#include "driver/gpio/gpio.hh"
#include "driver/i2c/gyro.hh"
#include "driver/i2c/pca9685servo.cpp"
#include "driver/serial/smartcontroller.hh"
#include "motor/motor.hh"

/**
 * hardware.hh
 *
 * Basic class for keeping track of and interacting with available hardware.
 **/
class Hardware{
  private:
    int numMotors;
    bool running;
    Gyro* gyro;
    GPIO* playButton;
    GPIO* relaxButton;
    GPIO* smartRelay;
    GPIO* pwmRelay;
    PCA9685Servo* pwm;
    SmartController* sca;
    SmartController* scb;
    Motor** motors;
    long headMask;
    long armMask;
    long legMask;

  public:
    /**
     * Hardware()
     *
     * Initialize the required hardware.
     **/
    Hardware();

    /**
     * ~Hardware()
     *
     * Destructor for the hardware object, where we perform a close.
     **/
    ~Hardware();

    /**
     * update()
     *
     * Allow the hardware to perform a time based update.
     *
     * @param pose The motor positions in the current time to be used in the
     * update. Note that NULL indicates that no action is required and no
     * action should be taken to change motor positions.
     **/
    void update(int* pose);

    /**
     * close()
     *
     * Stop all hardware communications and safely close them if possible.
     **/
    void close();

    /**
     * isRunning()
     *
     * Allow callers to check whether the hardware is currently operational.
     *
     * @return True if ready to go, false otherwise.
     **/
    bool isRunning(){
      return running;
    }

    /**
     * getMotors()
     *
     * Return access to the motors.
     *
     * @return The motors.
     **/
    Motor** getMotors();

    /**
     * getGyro()
     *
     * Get access to the gyro data.
     *
     * @return Access to the gyro.
     **/
    Gyro* getGyro();

    /**
     * getPlayButton()
     *
     * Return access to GPIO pin.
     *
     * @return The GPIO pin.
     **/
    GPIO* getPlayButton();

    /**
     * getRelaxButton()
     *
     * Return access to GPIO pin.
     *
     * @return The GPIO pin.
     **/
    GPIO* getRelaxButton();

    /**
     * getHeadMask()
     *
     * Get the binary mask for head motors.
     *
     * @return Binary mask.
     **/
    long getHeadMask();

    /**
     * getArmsMask()
     *
     * Get the binary mask for arm motors.
     *
     * @return Binary mask.
     **/
    long getArmsMask();

    /**
     * getLegsMask()
     *
     * Get the binary mask for leg motors.
     *
     * @return Binary mask.
     **/
    long getLegsMask();
};
