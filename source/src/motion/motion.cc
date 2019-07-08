#include "motion.hh"

#include "../hardware/hardware.cc"
#include "scheduler.cc"
#include "walking.cc"

Motion::Motion(){
  /* Track state of legs */
  currentMotion = MOTION::SCRIPT;
  futureMotion = MOTION::SCRIPT;
  numMotors = *Main::config->getInt("motor.num-motors").get();
  pose = (int*)malloc(numMotors * sizeof(int));
  /* Initialize hardware (first as its slow) */
  hw = new Hardware();
  /* Initialize the motion scheduler */
  fullSchedule = new Scheduler();
  /* Initialize the walk engine */
  headSchedule = new Scheduler();
  armsSchedule = new Scheduler();
  walking = new Walking();
}

Motion::~Motion(){
  free(pose);
}

void Motion::update(){
  /* Service current motion and switch to future motion if needed */
  if(currentMotion != futureMotion){
    bool stopped = false;
    /* Get current progress on stopping */
    switch(currentMotion){
      case Motion::MOTION::NONE :
        /* Is already stopped by default */
        stopped = true;
        break;
      case Motion::MOTION::WALKING :
        /* Request that the walk stops and any added scripts */
        walking->clear();
        headSchedule->clear();
        armsSchedule->clear();
        /* Check whether we are still walking */
        stopped = !headSchedule->getCurrentTask().empty() &
                  !armsSchedule->getCurrentTask().empty() &
                  !walking->isWalking();
        break;
      case Motion::MOTION::SCRIPT :
        /* Tell it to stop regardless because we have been asked to switch */
        fullSchedule->clear();
        /* If there's no queued task, we have stopped */
        stopped = !fullSchedule->getCurrentTask().empty();
        break;
      default:
        WARN("Unimplemented motion option.");
        break;
    }
    /* Go to next motion if the currently running motion is stopped */
    if(stopped){
      currentMotion = futureMotion;
    }
  }
  /* Switch source of pose based on walk or script running */
  int* hPose = NULL;
  int* aPose = NULL;
  int* lPose = NULL;
  int* fPose = NULL;
  switch(currentMotion){
    case Motion::MOTION::NONE :
      /* Keep current target pose */
      return;
    case Motion::MOTION::WALKING :
      hPose = headSchedule->getPose(hw->getMotors());
      aPose = armsSchedule->getPose(hw->getMotors());
      lPose = walking->getPose(hw->getMotors());
      /* If badness happened, go back to a safe default */
      if(lPose == NULL){
        WARN("Emergency walk stop, transitioning into zero script to prevent damage");
        currentMotion = Motion::MOTION::SCRIPT;
        futureMotion = Motion::MOTION::SCRIPT;
        action("zero");
        break;
      }
      for(int x = 0; x < numMotors; x++){
        int i = 1 << x;
        if(hPose != NULL && (i & hw->getHeadMask()) > 0){
          pose[x] = hPose[x];
        }
        if(aPose != NULL && (i & hw->getArmsMask()) > 0){
          pose[x] = aPose[x];
        }
        if(lPose != NULL && (i & hw->getLegsMask()) > 0){
          pose[x] = lPose[x];
        }
      }
      break;
    case Motion::MOTION::SCRIPT :
      fPose = fullSchedule->getPose(hw->getMotors());
      for(int x = 0; x < numMotors; x++){
        if(fPose != NULL){
          pose[x] = fPose[x];
        }
      }
      break;
    default:
      WARN("Unimplemented motion option.");
      return;
  }
  /* Perform the desired update on the hardware */
  hw->update(pose);
}

void Motion::walk(double forwardSpeed, double sideSpeed, double turnSpeed){
  /* Prepare the current walk schedule for desired walk parameters */
  walking->transition(forwardSpeed, sideSpeed, turnSpeed);
  /* Make sure that we run it */
  futureMotion = Motion::MOTION::WALKING;
}

void Motion::walkAction(std::string name, long region){
  /* Make sure this is a valid request */
  if(currentMotion == Motion::MOTION::WALKING){
    /* Handle well known cases */
    if((region & hw->getHeadMask()) == hw->getHeadMask()){
      headSchedule->pushBack(name);
    }
    if((region & hw->getArmsMask()) == hw->getArmsMask()){
      armsSchedule->pushBack(name);
    }
  }else{
    WARN("Invalid request to act & walk when not walking, soft ignore");
  }
}

void Motion::action(std::string name){
  /* Schedule the requested action */
  fullSchedule->pushBack(name);
  /* Make sure that we run it */
  futureMotion = Motion::MOTION::SCRIPT;
}

bool Motion::stop(){
  /* Make the update function transition us into a stopped state */
  futureMotion = Motion::MOTION::NONE;
  /* Send back our current state of stopping */
  return currentMotion == Motion::MOTION::NONE;
}

std::string Motion::getCurrentMotionName(){
  switch(currentMotion){
    case Motion::MOTION::NONE:
      return "none";
    case Motion::MOTION::WALKING:
      return headSchedule->getCurrentTask() + "+" +
             armsSchedule->getCurrentTask() + "+" +
             "walking";
    case Motion::MOTION::SCRIPT:
      return fullSchedule->getCurrentTask();
    default:
      return "unknown";
  }
}

std::string Motion::getPoseDump(){
  std::string buff = "{";
  for(int x = 0; x < numMotors; x++){
    buff +=
      "\"" + hw->getMotors()[x]->getMotorName() + "\":" +
      "\"" + std::to_string(hw->getMotors()[x]->getCurrentPosition(false)) + "\"";
    if(x < numMotors - 1){
      buff += ",";
    }
  }
  return buff + "}";
}

Hardware* Motion::getHardware(){
  return hw;
}
