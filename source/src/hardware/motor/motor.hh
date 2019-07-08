#pragma once

#include <string>

/**
 * motor.hh
 *
 * Basic interface for motors.
 **/
class Motor{
  public:
    /* Different connected hardware types */
    enum TYPE{
      SM30,
      FS6535M,
      MG995
    };

    /* Different positions of motors and their IDs */
    enum POSITION{
      NECK_PITCH =                    0x02,
      NECK_YAW =                      0x03,
      SHOULDER_PITCH_LEFT =           0x04,
      SHOULDER_PITCH_RIGHT =          0x05,
      SHOULDER_ROLL_LEFT =            0x06,
      SHOULDER_ROLL_RIGHT =           0x07,
      ELBOW_PITCH_LEFT =              0x08,
      ELBOW_PITCH_RIGHT =             0x09,
      HIP_YAW_LEFT =                  0x0A,
      HIP_YAW_RIGHT =                 0x0B,
      HIP_ROLL_LEFT =                 0x0C,
      HIP_ROLL_RIGHT =                0x0D,
      HIP_PITCH_LEFT =                0x0E,
      HIP_PITCH_RIGHT =               0x0F,
      KNEE_PITCH_LEFT =               0x10,
      KNEE_PITCH_RIGHT =              0x11,
      ANKLE_PITCH_LEFT =              0x12,
      ANKLE_PITCH_RIGHT =             0x13,
      ANKLE_ROLL_LEFT =               0x14,
      ANKLE_ROLL_RIGHT =              0x15,
      ALL_MOTORS =                    0xFE
    };

  private:
    TYPE type;
    POSITION position;
    std::string name;

  public:
    /**
     * Motor()
     *
     * Initialize our internal belief about the motors.
     *
     * @param motorType The type of the motor we are expected to interface
     * with.
     * @param kinematicPosition The kinematic position of the motor, so that we
     * know how to treat it.
     * @param motorName The name of the motor that corresponds to the one given
     * in config files.
     **/
    Motor(TYPE motorType, POSITION kinematicPosition, std::string motorName){
      type = motorType;
      position = kinematicPosition;
      name = motorName;
    }

    /**
     * init()
     *
     * Allow for this motor to be initialized.
     **/
    virtual void init() = 0;

    /**
     * getMotorType()
     *
     * Get the type of the motor.
     *
     * @return The type of the motor.
     **/
    TYPE getMotorType(){
      return type;
    }

    /**
     * getKinematicPosition()
     *
     * Get the kinematic position of the motor.
     *
     * @return The position of the motor.
     **/
    POSITION getKinematicPosition(){
      return position;
    }

    /**
     * getMotorName()
     *
     * Gets the name of this motor.
     *
     * @return The name of this motor.
     **/
    std::string getMotorName(){
      return name;
    }

    /**
     * setTargetPosition()
     *
     * Set the motor target position.
     *
     * @param r The target position in radians.
     * @param ofst True if the value is provided with the motor offset already
     * added.
     **/
    virtual void setTargetPosition(double r, bool ofst) = 0;

    /**
     * getTargetPosition()
     *
     * Get the target position of the motor.
     *
     * @param ofst True if it is required that the motor offset be added.
     * @return The target position in radians.
     **/
    virtual double getTargetPosition(bool ofst) = 0;

    /**
     * setCurrentPosition()
     *
     * Set the current position of the motor.
     *
     * @param r The current position in radians.
     * @param t The wall clock time this was measured.
     * @param ofst True if the value is provided with the motor offset already
     * added.
     **/
    virtual void setCurrentPosition(double r, long long t, bool ofst) = 0;

    /**
     * getCurrentPosition()
     *
     * Get the current position of this motor. In it's simplest form, this
     * method simply returns the last set target position. This may be used by
     * the caller to determine where a motor should be in theory, even if the
     * motor is not currently in this position.
     *
     * @param ofst True if it is required that the motor offset be added.
     * @return Some estimation of the motors current position, either derived
     * from the last requested target angle or through observation.
     **/
    virtual double getCurrentPosition(bool ofst) = 0;

    /**
     * getCurrentPositionTimestamp()
     *
     * Get the wall time for when the current position for this motor was set
     * in milliseconds.
     *
     * @return The time this motor was last set in milliseconds.
     **/
    virtual long long getCurrentPositionTimestamp() = 0;
};
