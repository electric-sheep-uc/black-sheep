#include "gyro.hh"

#ifndef WIRINGPI_C
  #define WIRINGPI_C
  #include "../gpio/wiringPi/wiringPi/wiringPi.c"
#endif
#include "../gpio/wiringPi/wiringPi/wiringPiI2C.c"

Gyro::Gyro(){
  /* Get configuration variables */
  accFallThresh = *Main::config->getDouble("gyro.fall-acc-thresh").get();
  accFallTime = *Main::config->getLong("gyro.fall-acc-time-ms").get();
  /* Make initial values look half sane */
  aFull = 0;
  aX = 0;
  aY = 0;
  aZ = 0;
  gX = 0;
  gY = 0;
  gZ = 0;
  lastUpdate = -1;
  fallingStart = -1;
  #if RPI == 1
    /* Get file handle */
    fd = wiringPiI2CSetup(I2C_ADDRESS);
    /* Write to sample rate register */
    wiringPiI2CWriteReg8(fd, SMPLRT_DIV, /*0x07*/0x00);
    /* Write to power management register */
    wiringPiI2CWriteReg8(fd, PWR_MGMT_1, /*0x01*/0x00);
    /* Write to Configuration register */
    wiringPiI2CWriteReg8(fd, CONFIG, 0);
    /* Write to Gyro Configuration register */
    wiringPiI2CWriteReg8(fd, GYRO_CONFIG, 24);
    /* Write to interrupt enable register */
    wiringPiI2CWriteReg8(fd, INT_ENABLE, /*0x01*/0x00);
  #else
    WARN("Can't initialize gyro");
  #endif
}

Gyro::~Gyro(){
  /* Do nothing */
}

void Gyro::update(){
  /* Read raw values and convert */
  aX = (float)readFromAddress(ACCEL_XOUT_H) / ACC_CONVERT;
  aY = (float)readFromAddress(ACCEL_YOUT_H) / ACC_CONVERT;
  aZ = (float)readFromAddress(ACCEL_ZOUT_H) / ACC_CONVERT;
  gX = (float)readFromAddress(GYRO_XOUT_H) / GYRO_CONVERT;
  gY = (float)readFromAddress(GYRO_YOUT_H) / GYRO_CONVERT;
  gZ = (float)readFromAddress(GYRO_ZOUT_H) / GYRO_CONVERT;
  /* Store time stamp */
  lastUpdate = CLOCK::CURRENT_TIME_MILLIS();
  /* Calculate full acceleration force */
  aFull = sqrt((aX * aX) + (aY * aY) + (aZ * aZ));
  LOGF("aFull -> ", aFull);//TODO
  /* Check for falling condition */
  if(abs(aZ) < accFallThresh){
    /* Set a time stamp if we haven't already */
    if(fallingStart < 0){
      fallingStart = CLOCK::CURRENT_TIME_MILLIS();
    }
  }else{
    /* Invalidate fall start */
    fallingStart = -1;
  }
}

bool Gyro::isFalling(){
  /* Make sure the fall time is valid and we are sure about falling */
  return fallingStart > 0 && lastUpdate - fallingStart >= accFallTime;
}

bool Gyro::fallenFront(){
  return aY < 0;
}

Eigen::Vector3f Gyro::getAcc(){
  return Eigen::Vector3f(aX, aY, aZ);
}

Eigen::Vector3f Gyro::getGyro(){
  return Eigen::Vector3f(gX, gY, gZ);
}

int Gyro::readFromAddress(int address){
  #if RPI == 1
    unsigned char highByte = wiringPiI2CReadReg8(fd, address);
    unsigned char lowByte = wiringPiI2CReadReg8(fd, address + 1);
    int value = (highByte << 8) | lowByte;
    /* Two's compliment */
    if(value > 32767){
      value -= 65536;
    }
    return value;
  #else
    return 0;
  #endif
}
