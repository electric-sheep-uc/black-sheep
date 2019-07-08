#pragma once

#include <Eigen/Dense>

/* Device Address/Identifier for MPU6050 */
#define I2C_ADDRESS  0x68
#define PWR_MGMT_1   0x6B
#define SMPLRT_DIV   0x19
#define CONFIG       0x1A
#define GYRO_CONFIG  0x1B
#define INT_ENABLE   0x38
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define GYRO_XOUT_H  0x43
#define GYRO_YOUT_H  0x45
#define GYRO_ZOUT_H  0x47

/* Gyro magic values */
#define ACC_CONVERT 16384.0
#define GYRO_CONVERT 131.0

/**
 * gyro.hh
 *
 * Handle the gyro hardware and convert raw values into something meaningful,
 * as well as offering common helper functions.
 **/
class Gyro{
  private:
    double accFallThresh;
    long long accFallTime;
    int fd;
    float aFull;
    float aX;
    float aY;
    float aZ;
    float gX;
    float gY;
    float gZ;
    long long lastUpdate;
    long long fallingStart;

  public:
    /**
     * Gyro()
     *
     * Initialize the gyro instance and send the initial packets to get the
     * correct format.
     **/
    Gyro();

    /**
     * ~Gyro()
     *
     * Free up any used memory.
     **/
    ~Gyro();

    /**
     * update()
     *
     * Update our internal picture of the gyro data.
     **/
    void update();

    /**
     * isFalling()
     *
     * Check if the gyro believes the agent is falling.
     *
     * @return True if falling, false otherwise.
     **/
    bool isFalling();

    /**
     * fallenFront()
     *
     * If we have fallen, figure out which side that is.
     *
     * @return True if fallen front, false if fallen back.
     **/
    bool fallenFront();

    /**
     * getAcc()
     *
     * Get the accleration data for the X, Y, Z axis.
     *
     * @return Acceleration data.
     **/
    Eigen::Vector3f getAcc();

    /**
     * getGyro()
     *
     * Get the gyro data for the X, Y, Z axis.
     *
     * @return Gyro data.
     **/
    Eigen::Vector3f getGyro();

  private:
    /**
     * readFromAddress()
     *
     * Read a raw value from a given address.
     *
     * @param address The address to be read from.
     * @return The read message.
     **/
    int readFromAddress(int address);
};
