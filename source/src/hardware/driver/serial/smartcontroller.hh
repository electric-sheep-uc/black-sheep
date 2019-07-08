#pragma once

#include "serial.hh"

#include "../../../log.hh"

/**
 * smartcontroller.hh
 *
 * This class is responsible for implementing the serial protocol to
 * communicate with the smart motors. Importantly, this class only understand
 * the motors for the purpose of creating valid packets - otherwise this class
 * is completely unaware of how they behave or what should be expected from
 * communication.
 **/
class SmartController : public Serial{
  using Serial::Serial;

  public:
    /* The commands that can be sent to servos */
    enum CMD{
      PING =           0x01, /* Query work status */
      READ_DATA =      0x02, /* Query the characters in the control table */
      WRITE_DATA =     0x03, /* Write characters to the control table */
      REGWRITE_DATA =  0x04, /* Similar to WRITE_DATA, but the control
                                characters are not take action immediately
                                after written ,until the ACTION command
                                arrives */
      ACTION =         0x05, /* Trigger REGWRITE_DATA write action */
      SYNCWRITE_DATA = 0x83, /* Using in simultaneous control of multiple
                                servos */
      RESET =          0x06  /* Reset the control table to the factory value */
    };

    /* The memory addresses of internal servo table */
    enum ADD_TABLE{
      /* Values in EEPROM       Command  R/w  Default */
      /* Reserved               0x00      /           */
      /* Reserved               0x01      /           */
      /* Reserved               0x02      /           */
      SW_VERSION_LOW =          0x03, /* R/           */
      SW_VERSION_HIGH =         0x04, /* R/           */
      ID =                      0x05, /* R/W  0       */
      BAUD_RATE =               0x06, /* R/W  0       */
      RETURN_DELAY_TIME =       0x07, /* R/W  0       */
      RESPONSE_STATUS_LEVEL =   0x08, /* R/W  1       */
      MIN_ANGLE_LIMIT_LOW =     0x09, /* R/W  0       */
      MIN_ANGLE_LIMIT_HIGH =    0x0A, /* R/W  0       */
      MAX_ANGLE_LIMIT_LOW =     0x0B, /* R/W  15      */
      MAX_ANGLE_LIMIT_HIGH =    0x0C, /* R/W  255     */
      MAX_TEMPERATURE_LIMIT =   0x0D, /* R/W  80      */
      MAX_INPUT_VOLTAGE =       0x0E, /* R/W  140     */
      MIN_INPUT_VOLTAGE =       0x0F, /* R/W  60      */
      MAX_TORQUE_LOW =          0x10, /* R/W  3       */
      MAX_TORQUE_HIGH =         0x11, /* R/W  232     */
      /* Reserved               0x12      /           */
      UNLOADING_CONDITION =     0x13, /* R/W  47      */
      LED_ALARM_CONDITION =     0x14, /* R/W  47      */
      P =                       0x15, /* R/W  15      */
      D =                       0x16, /* R/W  0       */
      I =                       0x17, /* R/W  0       */
      MIN_PWM_LOW =             0x18, /* R/W  100     */
      MIN_PWM_HIGH =            0x19, /* R/W  100     */
      CLOCKWISE_NO_CARE =       0x1A, /* R/W  1       */
      CNTR_CLOCKWISE_NO_CARE =  0x1B, /* R/W  1       */
      INTEGRATION_LIMIT_LOW =   0x1C, /* R/W  0       */
      INTEGRATION_LIMIT_HIGH =  0x1D, /* R/W  0       */
      /* Reserved               0x1E      /           */
      /* Reserved               0x1F      /           */
      /* Reserved               0x20      /           */
      POSITION_CORRECT_LOW =    0x21, /* R/W  0       */
      POSITION_CORRECT_HIGH =   0x22, /* R/W  0       */
      OPERATING_MODE =          0x23, /* R/W  0       */
      PROTECTION_CURRENT_LOW =  0x24, /* R/W  7       */
      /* Reserved               0x25      /           */
      /* Reserved               0x26      /           */
      /* Reserved               0x27      /           */

      /* Values in RAM          Command  R/w  Default */
      TORQUE_SWITCH_LOW =       0x28, /* R/W  0       */
      /* Reserved               0x29      /           */
      TARGET_POSITION_LOW =     0x2A, /* R/W          */
      TARGET_POSITION_HIGH =    0x2B, /* R/W          */
      RUNNING_TIME_LOW =        0x2C, /* R/W  0       */
      RUNNING_TIME_HIGH =       0x2D, /* R/W  0       */
      RUNNING_SPEED_LOW =       0x2E, /* R/W  0       */
      RUNNING_SPEED_HIGH =      0x2F, /* R/W  0       */
      LOCK_SIGN =               0x30, /* R/W  0       */
      /* Reserved               0x31      /           */
      /* Reserved               0x32      /           */
      /* Reserved               0x33      /           */
      /* Reserved               0x34      /           */
      /* Reserved               0x35      /           */
      /* Reserved               0x36      /           */
      /* Reserved               0x37      /           */
      CURRENT_POSITION_LOW =    0x38, /* R/           */
      CURRENT_POSITION_HIGH =   0x39, /* R/           */
      CURRENT_SPEED_LOW =       0x3A, /* R/           */
      CURRENT_SPEED_HIGH =      0x3B, /* R/           */
      CURRENT_LOAD_LOW =        0x3C, /* R/           */
      CURRENT_LOAD_HIGH =       0x3D, /* R/           */
      CURRENT_VOLTAGE =         0x3E, /* R/           */
      CURRENT_TEMPERATURE =     0x3F, /* R/           */
      REG_WRITE_LOGO =          0x40, /* R/   0       */
      /* Reserved               0x41      /           */
      MOBILE_SIGN =             0x42, /* R/           */
      CURRENT_TARGET_POS_LOW =  0x43, /* R/           */
      CURRENT_TARGET_POS_HIGH = 0x44, /* R/           */
      CURRENT_CURRENT_LOW =     0x45, /* R/           */
      CURRENT_CURRENT_HIGH =    0x46  /* R/           */
    };

    /* Basic packet structure */
    struct Packet{
      unsigned int id;
      CMD cmd;
      unsigned char* param;
      int numParam;
      bool response;
    };

    void startComms();

    unsigned char checkSum(Packet pkt);

    /**
     * writePacket()
     *
     * Write a packet to the smart motor controller and doesn't wait for a
     * response.
     *
     * @param pkt A packet to be sent.
     * @param dummy A dummy parameter to control which version of this method
     *is needed.
     **/
    void writePacket(Packet pkt, bool dummy);

    /**
     * writePacket()
     *
     * Write a packet to the smart motor controller and waits for a response.
     *
     * @param pkt A packet to be sent.
     * @return A valid packet if it exists, otherwise NULL.
     **/
    Packet writePacket(Packet pkt);

    /**
     * readPacket()
     *
     * Read a packet if available and get a valid payload. Note that this
     * method is rarely used, the caller is the master and the motor is the
     * slave.
     *
     * @param pkt This can be any packet as this only acts as a data store and
     * will be overridden.
     * @return A valid packet if it exists, otherwise NULL.
     **/
    Packet readPacket(Packet pkt);
};
