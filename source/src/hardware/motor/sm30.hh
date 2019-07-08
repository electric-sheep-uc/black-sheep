#pragma once

#include "motor.hh"

/**
 * sm30.hh
 *
 * This is the specific class for the SM30 motor.
 **/
class SM30 : public Motor{
  using Motor::Motor;

  private:
    /* Bit rate for serial communications */
    enum BAUD_RATE{
      BIT_1M =   0x00, /* 1000000 */
      BIT_500K = 0x01, /*  500000 */
      BIT_250K = 0x02, /*  250000 */
      BIT_128K = 0x03, /*  128000 */
      BIT_115K = 0x04, /*  115200 */
      BIT_77K =  0x05, /*   76800 */
      BIT_58K =  0x06, /*   57600 */
      BIT_38K =  0x07  /*   36400 */
    };

    /* Return delay in micro seconds after sending command */
    enum RETURN_DELAY_TIME{
      US0 =  0x00,
      US2 =  0x01,
      US4 =  0x02,
      US6 =  0x03,
      US8 =  0x04,
      US10 = 0x05,
      US12 = 0x06,
      US14 = 0x07,
      US16 = 0x08
      /* NOTE: There are also valid values higher than this. */
    };

    /* Response level */
    enum RESPONSE_STATUS_LEVEL{
      YES_RESPONSE =     0x00, /* Respond to all */
      LIMITED_RESPONSE = 0x01 /* Only read and ping */
    };

    /* Temperature of motors */
    enum TEMPERATURE{
      DEG65 = 65,
      DEG70 = 70,
      DEG75 = 75,
      DEG80 = 80,
      DEG85 = 85,
      DEG90 = 90,
      DEG95 = 95
      /* NOTE: High accuracy is possible. */
    };

    /* Voltage of motors */
    enum VOLTAGE{
      V9_5 =   95,
      V10 =   100,
      V10_5 = 105,
      V11 =   110,
      V11_5 = 115,
      V12 =   120,
      V12_5 = 125,
      V13 =   130,
      V13_5 = 135,
      V14 =   140,
      V14_5 = 145
      /* NOTE: High accuracy is possible. */
    };

    /* The maximum maximum torque value */
    #define MAX_MAX_TORQUE 1000

    /* Alarm condition bits */
    #define TEST_LED_ALARM_CONDITION_OVERLOAD    0b00100000
    #define TEST_LED_ALARM_CONDITION_OVERCURRENT 0b00001000
    #define TEST_LED_ALARM_CONDITION_OVERHEAT    0b00000100
    #define TEST_LED_ALARM_CONDITION_ANGLE_FAULT 0b00000010
    #define TEST_LED_ALARM_CONDITION_VOLTAGE     0b00000001

    /* Servo run mode */
    enum OPERATING_MODE{
      TORQUE = 0x02, /* Maintain torque */
      SPEED =  0x01, /* Wheel mode */
      SERVO =  0x00
    };

    /* Torque output switch */
    enum TORQUE_SWITCH{
      ON =  0x01,
      OFF = 0x00
    };

    /* EEPROM lock function */
    enum LOCK_SIGN{
      EEPROM_WRITE = 0x00, /* NOTE: This will wear out the memory and is slower! */
      RAM_WRITE =    0x01
    };

    double offset;
    double targetPosition;
    double currentPosition;
    long long currentPositionTimestamp;
    int temperature;

  public:
    void init();

    void setTargetPosition(double r, bool ofst);

    double getTargetPosition(bool ofst);

    void setCurrentPosition(double r, long long t, bool ofst);

    double getCurrentPosition(bool ofst);

    long long getCurrentPositionTimestamp();

    /**
     * setTempDeg()
     *
     * Set the temperature read from the motor in degrees.
     *
     * @param temp The temperature in degrees.
     **/
    void setTempDeg(int temp);

    /**
     * getTempDeg()
     *
     * Get the temperature read in degrees.
     *
     * @return The current temperature, otherwise -1.
     **/
    int getTempDeg();
};
