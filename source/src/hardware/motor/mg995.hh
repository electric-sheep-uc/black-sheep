#pragma once

#include "motor.hh"

/**
 * mg995.hh
 *
 * This is the specific class for the MG995 motor.
 **/
class MG995 : public Motor{
  using Motor::Motor;

  private:
    double offset;
    double targetPosition;
    double currentPosition;
    long long currentPositionTimestamp;

  public:
    void init();

    void setTargetPosition(double r, bool ofst);

    double getTargetPosition(bool ofst);

    void setCurrentPosition(double r, long long t, bool ofst);

    double getCurrentPosition(bool ofst);

    long long getCurrentPositionTimestamp();
};
