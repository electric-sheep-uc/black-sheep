#include "mg995.hh"

#include "../../main.hh"
#include "../../log.hh"
#include "../../utils/clock.hh"

void MG995::init(){
  /* Initialize program specific motor values */
  switch(getKinematicPosition()){
    case Motor::POSITION::NECK_PITCH :
      offset = *Main::config->getInt("motor.offsets.shoulder-pitch-left").get();
      break;
    case Motor::POSITION::NECK_YAW :
      offset = *Main::config->getInt("motor.offsets.shoulder-pitch-left").get();
      break;
    default :
      /* A not too harmful default value (we hope) */
      offset = 90;
      WARN("Unknown motor type");
      break;
  }
  /* Initialize internal variables */
  offset = RAW2RAD(offset);
  setTargetPosition(0, false);
  setCurrentPosition(0, CLOCK::CURRENT_TIME_MILLIS(), false);
}

void MG995::setTargetPosition(double r, bool ofst){
  if(ofst){
    targetPosition = r - offset;
  }else{
    targetPosition = r;
  }
}

double MG995::getTargetPosition(bool ofst){
  if(ofst){
    return targetPosition + offset;
  }else{
    return targetPosition;
  }
}

void MG995::setCurrentPosition(double r, long long t, bool ofst){
  if(ofst){
    currentPosition = r - offset;
  }else{
    currentPosition = r;
  }
  currentPositionTimestamp = t;
}

double MG995::getCurrentPosition(bool ofst){
  if(ofst){
    return currentPosition + offset;
  }else{
    return currentPosition;
  }
}

long long MG995::getCurrentPositionTimestamp(){
  return currentPositionTimestamp;
}
