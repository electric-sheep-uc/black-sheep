#pragma once

#include "../main.hh"
#include "../hardware/motor/motor.hh"
#include "../utils/clock.hh"

/**
 * scheduler.hh
 *
 * This class handles the hardware scheduling and future planning.
 **/
class Scheduler{
  private:
    struct Task{
      long long start;
      Config* script;
    };

    int numMotors;
    int* pose;
    std::vector<Config*> motions;
    std::vector<Task> tasks;

  public:
    /**
     * Scheduler()
     *
     * Initialize the scheduling handler by loading all used scripts in advance
     * into RAM.
     **/
    Scheduler();

    /**
     * ~Scheduler()
     *
     * Destructor for the class.
     **/
    ~Scheduler();

    /**
     * getPose()
     *
     * Update the motor positions relative to the current time.
     *
     * @param motors The current motor information.
     * @param The calculated pose for the current time.
     **/
    int* getPose(Motor** motors);

    /**
     * pushBack()
     *
     * Add a task to the back of the current task list.
     *
     * @param taskName The task to be added.
     **/
    void pushBack(std::string taskName);

    /**
     * clear()
     *
     * Remove all tasks, except the current running task.
     **/
    void clear();

    /**
     * getCurrentTask()
     *
     * Query what the currently running task is.
     *
     * @return The name of the currently running motion, otherwise "none".
     **/
    std::string getCurrentTask();

  private:
    /**
     * service()
     *
     * Service the task list so that it's up to date.
     *
     * @param relTime Service the task list relative to the time we plan to act
     * on.
     **/
    void service(long long relTime);
};
