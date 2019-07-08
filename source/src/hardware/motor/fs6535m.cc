#include "fs6535m.hh"

#include "../../main.hh"
#include "../../log.hh"
#include "../../utils/clock.hh"

void FS6535M::init(){
  /* Initialize program specific motor values */
  switch(getKinematicPosition()){
    case Motor::POSITION::SHOULDER_PITCH_LEFT :
      offset = *Main::config->getInt("motor.offsets.shoulder-pitch-left").get();
      break;
    case Motor::POSITION::SHOULDER_PITCH_RIGHT :
      offset = *Main::config->getInt("motor.offsets.shoulder-pitch-right").get();
      break;
    case Motor::POSITION::SHOULDER_ROLL_LEFT :
      offset = *Main::config->getInt("motor.offsets.shoulder-roll-left").get();
      break;
    case Motor::POSITION::SHOULDER_ROLL_RIGHT :
      offset = *Main::config->getInt("motor.offsets.shoulder-roll-right").get();
      break;
    case Motor::POSITION::ELBOW_PITCH_LEFT :
      offset = *Main::config->getInt("motor.offsets.elbow-pitch-left").get();
      break;
    case Motor::POSITION::ELBOW_PITCH_RIGHT :
      offset = *Main::config->getInt("motor.offsets.elbow-pitch-right").get();
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

void FS6535M::setTargetPosition(double r, bool ofst){
  if(ofst){
    targetPosition = r - offset;
  }else{
    targetPosition = r;
  }
}

double FS6535M::getTargetPosition(bool ofst){
  if(ofst){
    return targetPosition + offset;
  }else{
    return targetPosition;
  }
}

void FS6535M::setCurrentPosition(double r, long long t, bool ofst){
  if(ofst){
    currentPosition = r - offset;
  }else{
    currentPosition = r;
  }
  currentPositionTimestamp = t;
}

double FS6535M::getCurrentPosition(bool ofst){
  if(ofst){
    return currentPosition + offset;
  }else{
    return currentPosition;
  }
}

long long FS6535M::getCurrentPositionTimestamp(){
  return currentPositionTimestamp;
}
