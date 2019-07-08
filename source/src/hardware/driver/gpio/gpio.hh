#pragma once

/**
 * gpio.hh
 *
 * Control a GPIO on the main control board.
 **/
class GPIO{
  public:
    /* NOTE: https://www.raspberrypi.org/documentation/usage/gpio/README.md */
    enum PIN{
      NONE = 0,
      V33_0  =  1, V50_0  =  2,
      GPIO2  =  3, V50_1  =  4,
      GPIO3  =  5, GND_0  =  6,
      GPIO4  =  7, GPIO14 =  8,
      GND_1  =  9, GPIO15 = 10,
      GPIO17 = 11, GPIO18 = 12,
      GPIO27 = 13, GND_2  = 14,
      GPIO22 = 15, GPIO23 = 16,
      V33_1  = 17, GPIO24 = 18,
      GPIO10 = 19, GND_3  = 20,
      GPIO9  = 21, GPIO25 = 22,
      GPIO11 = 23, GPIO8  = 24,
      GND_4  = 25, GPIO7  = 26,
      GPIO0  = 27, GPIO1  = 28,
      GPIO5  = 29, GND_5  = 30,
      GPIO6  = 31, GPIO12 = 32,
      GPIO13 = 33, GND_6  = 34,
      GPIO19 = 35, GPIO16 = 36,
      GPIO26 = 37, GPIO20 = 38,
      GND_7  = 39, GPIO21 = 40
    };

    enum VOLTAGE{
      V3_3 = 33,
      V5 = 50
    };

    enum CAPABILITY{
      POWER,
      IN,
      OUT
    };

  private:
    bool ready;
    std::string name;
    PIN p;
    VOLTAGE v;
    CAPABILITY c;

  public:
    /**
     * init()
     *
     * Initialize the hardware for the GPIOs.
     **/
    static void init();

    /**
     * GPIO()
     *
     * Initialize the GPIO with known information.
     *
     * @param pinName A human readable label for the pin.
     * @param pin The pin label.
     * @param volt The voltage range of the pin.
     * @param cap The capabilities of the GPIO pin.
     **/
    GPIO(std::string pinName, PIN pin, VOLTAGE volt, CAPABILITY cap);

    /**
     * ~GPIO()
     *
     * Free up memory associated with the class.
     **/
    ~GPIO();

    /**
     * setDigitalOutput()
     *
     * Set the pin high or low.
     *
     * @param out True if pin high, otherwise false.
     **/
    void setDigitalOutput(bool out);

    /**
     * setAnalogueOutput()
     *
     * Set the pin voltage.
     *
     * @param out The voltage to set on the pin.
     **/
    void setAnalogueOutput(double out);

    /**
     * getDigitalInput()
     *
     * Read the pin high or low.
     *
     * @return True for high, false for low.
     **/
    bool getDigitalInput();

    /**
     * getAnalogueInput()
     *
     * Read the pin voltage.
     *
     * @return The voltage on the pin, otherwise -1.
     **/
    double getAnalogueInput();

    /**
     * getName()
     *
     * Get the human readable name for this pin.
     *
     * @return The name of the pin.
     **/
    std::string getName();

    /**
     * isReady()
     *
     * Check whether the GPIO pin can be used.
     *
     * @return True if ready, otherwise false.
     **/
    bool isReady();
};
