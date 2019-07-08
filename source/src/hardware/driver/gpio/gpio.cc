#include "gpio.hh"

#undef delayMicroseconds
#undef delay
#include "wiringPi/wiringPi/piHiPri.c"
#include "wiringPi/wiringPi/softPwm.c"
#include "wiringPi/wiringPi/softTone.c"
#ifndef WIRINGPI_C
  #define WIRINGPI_C
  #include "wiringPi/wiringPi/wiringPi.c"
#endif

void GPIO::init(){
  #if RPI == 1
    wiringPiSetup();
  #else
    WARN("Unable to setup GPIOs");
  #endif
}

GPIO::GPIO(std::string pinName, PIN pin, VOLTAGE volt, CAPABILITY cap){
  ready = false;
  name = pinName;
  p = pin;
  v = volt;
  c = cap;
  #if RPI == 1
    switch(c){
      case CAPABILITY::OUT :
        pinMode(p, OUTPUT);
        break;
      case CAPABILITY::IN :
        pullUpDnControl(p, PUD_UP);
      default :
        pinMode(p, INPUT);
        break;
    }
    ready = true;
  #else
    ready = false;
  #endif
}

GPIO::~GPIO(){
  /* Do nothing */
}

void GPIO::setDigitalOutput(bool out){
  if(p > 0 && c == CAPABILITY::OUT){
    #if RPI == 1
      digitalWrite(p, out ? HIGH : LOW);
    #else
      WARN("Not running on Raspberry Pi");
    #endif
  }else{
    WARN("Pin not able to output");
  }
}

void GPIO::setAnalogueOutput(double out){
  /* TODO: Implement this. */
  WARN("Not implemented");
}

bool GPIO::getDigitalInput(){
  if(p > 0 && c == CAPABILITY::IN){
    #if RPI == 1
      return digitalRead(p) != HIGH;
    #else
      WARN("Not running on Raspberry Pi");
    #endif
  }else{
    WARN("Pin not able to input");
  }
  /* Default return value */
  return false;
}

double GPIO::getAnalogueInput(){
  /* TODO: Implement this. */
  WARN("Not implemented");
  return -1;
}

std::string GPIO::getName(){
  return name;
}

bool GPIO::isReady(){
  return ready;
}
