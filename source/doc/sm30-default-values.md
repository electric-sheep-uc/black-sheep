# SM30 Default Values

The following are a capture of the default values of the SM30.

**NOTE:** This was recorded once for one motor - it's assumed that there is no
variance in these factory values.

|Values in EEPROM         |Pos  |R/W|Default|Actual|
|:-----------------------:|:---:|:-:|:-----:|:----:|
|*Reserved*               |0x00 | / |       |0x06  |
|*Reserved*               |0x01 | / |       |0x01  |
|*Reserved*               |0x02 | / |       |0x00  |
|SW_VERSION_LOW =         |0x03 |R/ |       |0x01  |
|SW_VERSION_HIGH =        |0x04 |R/ |       |0x00  |
|ID =                     |0x05 |R/W|0      |0x01  |
|BAUD_RATE =              |0x06 |R/W|0      |0x04  |
|RETURN_DELAY_TIME =      |0x07 |R/W|0      |0x00  |
|RESPONSE_STATUS_LEVEL =  |0x08 |R/W|1      |0x01  |
|MIN_ANGLE_LIMIT_LOW =    |0x09 |R/W|0      |0x00  |
|MIN_ANGLE_LIMIT_HIGH =   |0x0A |R/W|0      |0x00  |
|MAX_ANGLE_LIMIT_LOW =    |0x0B |R/W|15     |0xFF  |
|MAX_ANGLE_LIMIT_HIGH =   |0x0C |R/W|255    |0x0F  |
|MAX_TEMPERATURE_LIMIT =  |0x0D |R/W|80     |0x50  |
|MAX_INPUT_VOLTAGE =      |0x0E |R/W|140    |0x0A  |
|MIN_INPUT_VOLTAGE =      |0x0F |R/W|60     |0x46  |
|MAX_TORQUE_LOW =         |0x10 |R/W|3      |0xEA  |
|MAX_TORQUE_HIGH =        |0x11 |R/W|232    |0x03  |
|*Reserved*               |0x12 | / |       |0x01  |
|UNLOADING_CONDITION =    |0x13 |R/W|47     |0x25  |
|LED_ALARM_CONDITION =    |0x14 |R/W|47     |0x25  |
|P =                      |0x15 |R/W|15     |0x0F  |
|D =                      |0x16 |R/W|0      |0x0F  |
|I =                      |0x17 |R/W|0      |0x00  |
|MIN_PWM_LOW =            |0x18 |R/W|100    |0x5A  |
|MIN_PWM_HIGH =           |0x19 |R/W|100    |0x00  |
|CLOCKWISE_NO_CARE =      |0x1A |R/W|1      |0x02  |
|CNTR_CLOCKWISE_NO_CARE = |0x1B |R/W|1      |0x02  |
|INTEGRATION_LIMIT_LOW =  |0x1C |R/W|0      |0x00  |
|INTEGRATION_LIMIT_HIGH = |0x1D |R/W|0      |0x00  |
|*Reserved*               |0x1E | / |       |0x01  |
|*Reserved*               |0x1F | / |       |0x05  |
|*Reserved*               |0x20 | / |       |0x00  |
|POSITION_CORRECT_LOW =   |0x21 |R/W|0      |0x00  |
|POSITION_CORRECT_HIGH =  |0x22 |R/W|0      |0x00  |
|OPERATING_MODE =         |0x23 |R/W|0      |0x00  |
|PROTECTION_CURRENT_LOW = |0x24 |R/W|7      |0x20  |
|*Reserved*               |0x25 | / |       |0x03  |
|*Reserved*               |0x26 | / |       |0x00  |
|*Reserved*               |0x27 | / |       |0x00  |

|Values in RAM            |Pos  |R/W|Default|Actual|
|:-----------------------:|:---:|:-:|:-----:|:----:|
|TORQUE_SWITCH_LOW =      |0x28 |R/W|0      |0x00  |
|*Reserved*               |0x29 | / |       |0x00  |
|TARGET_POSITION_LOW =    |0x2A |R/W|       |0x00  |
|TARGET_POSITION_HIGH =   |0x2B |R/W|       |0x00  |
|RUNNING_TIME_LOW =       |0x2C |R/W|0      |0x00  |
|RUNNING_TIME_HIGH =      |0x2D |R/W|0      |0x00  |
|RUNNING_SPEED_LOW =      |0x2E |R/W|0      |0x00  |
|RUNNING_SPEED_HIGH =     |0x2F |R/W|0      |0x00  |
|LOCK_SIGN =              |0x30 |R/W|0      |0x01  |
|*Reserved*               |0x31 | / |       |0x00  |
|*Reserved*               |0x32 | / |       |0x00  |
|*Reserved*               |0x33 | / |       |0x00  |
|*Reserved*               |0x34 | / |       |0x00  |
|*Reserved*               |0x35 | / |       |0x00  |
|*Reserved*               |0x36 | / |       |0x00  |
|*Reserved*               |0x37 | / |       |0x00  |
|CURRENT_POSITION_LOW =   |0x38 |R/ |       |0x2B  |
|CURRENT_POSITION_HIGH =  |0x39 |R/ |       |0x07  |
|CURRENT_SPEED_LOW =      |0x3A |R/ |       |0x00  |
|CURRENT_SPEED_HIGH =     |0x3B |R/ |       |0x00  |
|CURRENT_LOAD_LOW =       |0x3C |R/ |       |0x00  |
|CURRENT_LOAD_HIGH =      |0x3D |R/ |       |0x00  |
|CURRENT_VOLTAGE =        |0x3E |R/ |       |0x7C  |
|CURRENT_TEMPERATURE =    |0x3F |R/ |       |0x1A  |
|REG_WRITE_LOGO =         |0x40 |R/ |0      |0x00  |
|*Reserved*               |0x41 | / |       |0x00  |
|MOBILE_SIGN =            |0x42 |R/ |       |0x00  |
|CURRENT_TARGET_POS_LOW = |0x43 |R/ |       |0x2B  |
|CURRENT_TARGET_POS_HIGH =|0x44 |R/ |       |0x07  |
|CURRENT_CURRENT_LOW =    |0x45 |R/ |       |0x00  |
|CURRENT_CURRENT_HIGH =   |0x46 |R/ |       |0x00  |
