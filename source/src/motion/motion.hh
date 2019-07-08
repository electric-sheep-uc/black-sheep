#pragma once

#include "../hardware/hardware.hh"
#include "scheduler.hh"
#include "walking.hh"

/**
 * motion.hh
 *
 * Handle high level motion requests from the main thread, including scheduling
 * for scripted motions and walking. Actions are requested and the correct
 * schedules are created in response.
 **/
class Motion{
  private:
    enum MOTION{
      NONE,
      SCRIPT,
      WALKING
    };

    MOTION currentMotion;
    MOTION futureMotion;
    int numMotors;
    int* pose;
    Hardware* hw;
    Scheduler* headSchedule;
    Scheduler* armsSchedule;
    Scheduler* fullSchedule;
    Walking* walking;

  public:
    /**
     * Motion()
     *
     * Initialize the motion handling.
     **/
    Motion();

    /**
     * ~Motion()
     *
     * Free up any initialized memory.
     **/
    ~Motion();

    /**
     * update()
     *
     * Service the hardware.
     **/
    void update();

    /**
     * walk()
     *
     * Queue target walking and queue acceleration/de-acceleration walk actions
     * appropriately. This considers the current walk to plan actions towards
     * the target walk speed.
     *
     * @param forwardSpeed The forward (positive) and backward (negative) speed
     * from -1.0 to 1.0.
     * @param sideSpeed The right step speed (positive) and left step speed
     * (negative) from -1.0 to 1.0.
     * @param turnSpeed Clockwise rotation speed (positive) and anti-clockwise
     * rotation speed (negative) from -1.0 to 1.0.
     **/
    void walk(double forwardSpeed, double sideSpeed, double turnSpeed);

    /**
     * walkAction()
     *
     * Run a specific action on the queue whilst performing a walk for a
     * specific region. If the region is not well defined, a printed warning is
     * given and the command is ignored.
     *
     * @param name A bit mask of the regions to be addressed.
     * @param region The region to perform the specific action in.
     **/
    void walkAction(std::string name, long region);

    /**
     * action()
     *
     * Run a specific action on the queue. Note that this is different from
     * walking.
     *
     * @param name A bit mask of the regions to be addressed.
     **/
    void action(std::string name);

    /**
     * stop()
     *
     * Stop the current actions completely by safely stopping the current
     * actions, even if that requires continuing one or more actions to do so.
     *
     * @return True if stopped, otherwise false.
     **/
    bool stop();

    /**
     * getCurrentMotionName()
     *
     * Get the current motion name. If we are currently walking, simply return
     * "walk". If none then NULL, indicating that there is currently nothing
     * running.
     *
     * @return The current state of the motion engine.
     **/
    std::string getCurrentMotionName();

    /**
     * getPoseDump()
     *
     * Create a JSON representation of the current pose.
     *
     * @return The current pose dump.
     **/
    std::string getPoseDump();

    /**
     * getHardware()
     *
     * Get access to the hardware. NOTE: Please don't use this unless you know
     * what you are doing.
     *
     * @return Access to the hardware.
     **/
    Hardware* getHardware();
};
