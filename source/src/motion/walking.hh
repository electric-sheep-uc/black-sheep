#pragma once

#include "ikwalk/CubicSpline.cpp"
#include "ikwalk/IKWalk.cpp"
#include "ikwalk/HumanoidModel.cpp"
#include "ikwalk/LegIK.cpp"
#include "ikwalk/Polynom.cpp"
#include "ikwalk/Spline.cpp"

#include "../hardware/motor/motor.hh"

/**
 * walking.hh
 *
 * This class handles the walking - specifically planning on how to achieve a
 * walk from a given state given the requirements.
 **/
class Walking{
  private:
    struct Rhoban::IKWalkParameters params;
    struct Rhoban::IKWalkOutputs outputs;
    int numMotors;
    double rampEnabledGain;
    double rampForwardGain;
    double rampSideGain;
    double rampTurnGain;
    double maxStepGain;
    double maxLateralGain;
    double maxTurnGain;
    int* pose;
    double targetForwardGain;
    double targetSideGain;
    double targetTurnGain;
    long long prevTimestamp;
    double phase;

  public:
    /**
     * Walking()
     *
     * Initialize the walking class.
     **/
    Walking();

    /**
     * ~Walking()
     *
     * Destructor for the class.
     **/
    ~Walking();

    /**
     * getPose()
     *
     * Get the current walk pose.
     *
     * @param motors The current motor information.
     * @return The current walk pose.
     **/
    int* getPose(Motor** motors);

    /**
     * transition()
     *
     * Transition to a new set of walk parameters from the current set of walk
     * parameters.
     *
     * @param forwardSpeed The forward (positive) and backward (negative) speed
     * from -1.0 to 1.0.
     * @param sideSpeed The right step speed (positive) and left step speed
     * (negative) from -1.0 to 1.0.
     * @param turnSpeed Clockwise rotation speed (positive) and anti-clockwise
     * rotation speed (negative) from -1.0 to 1.0.
     **/
    void transition(double forwardSpeed, double sideSpeed, double turnSpeed);

    /**
     * clear()
     *
     * Clear the current planned walk actions.
     **/
    void clear();

    /**
     * isWalking()
     *
     * Check whether the walk is currently stopped.
     *
     * @return True if walking, otherwise false.
     **/
    bool isWalking();
};
