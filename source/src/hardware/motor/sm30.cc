#include "sm30.hh"

#include "../../main.hh"
#include "../../log.hh"
#include "../../utils/clock.hh"

void SM30::init(){
  /* Initialize program specific motor values */
  switch(getKinematicPosition()){
    case Motor::POSITION::HIP_YAW_LEFT :
      offset = *Main::config->getInt("motor.offsets.hip-yaw-left").get();
      break;
    case Motor::POSITION::HIP_YAW_RIGHT :
      offset = *Main::config->getInt("motor.offsets.hip-yaw-right").get();
      break;
    case Motor::POSITION::HIP_ROLL_LEFT :
      offset = *Main::config->getInt("motor.offsets.hip-roll-left").get();
      break;
    case Motor::POSITION::HIP_ROLL_RIGHT :
      offset = *Main::config->getInt("motor.offsets.hip-roll-right").get();
      break;
    case Motor::POSITION::HIP_PITCH_LEFT :
      offset = *Main::config->getInt("motor.offsets.hip-pitch-left").get();
      break;
    case Motor::POSITION::HIP_PITCH_RIGHT :
      offset = *Main::config->getInt("motor.offsets.hip-pitch-right").get();
      break;
    case Motor::POSITION::KNEE_PITCH_LEFT :
      offset = *Main::config->getInt("motor.offsets.knee-pitch-left").get();
      break;
    case Motor::POSITION::KNEE_PITCH_RIGHT :
      offset = *Main::config->getInt("motor.offsets.knee-pitch-right").get();
      break;
    case Motor::POSITION::ANKLE_PITCH_LEFT :
      offset = *Main::config->getInt("motor.offsets.ankle-pitch-left").get();
      break;
    case Motor::POSITION::ANKLE_PITCH_RIGHT :
      offset = *Main::config->getInt("motor.offsets.ankle-pitch-right").get();
      break;
    case Motor::POSITION::ANKLE_ROLL_LEFT :
      offset = *Main::config->getInt("motor.offsets.ankle-roll-left").get();
      break;
    case Motor::POSITION::ANKLE_ROLL_RIGHT :
      offset = *Main::config->getInt("motor.offsets.ankle-roll-right").get();
      break;
    default :
      /* A not too harmful default value (we hope) */
      offset = 2048;
      WARN("Unknown motor type");
      break;
  }
  /* Initialize internal variables */
  offset = RAW2RAD(offset);
  setTargetPosition(0, false);
  setCurrentPosition(0, CLOCK::CURRENT_TIME_MILLIS(), false);
  temperature = -1;
}

void SM30::setTargetPosition(double r, bool ofst){
  if(ofst){
    targetPosition = r - offset;
  }else{
    targetPosition = r;
  }
}

double SM30::getTargetPosition(bool ofst){
  if(ofst){
    return targetPosition + offset;
  }else{
    return targetPosition;
  }
}

void SM30::setCurrentPosition(double r, long long t, bool ofst){
  if(ofst){
    currentPosition = r - offset;
  }else{
    currentPosition = r;
  }
  currentPositionTimestamp = t;
}

double SM30::getCurrentPosition(bool ofst){
  if(ofst){
    return currentPosition + offset;
  }else{
    return currentPosition;
  }
}

long long SM30::getCurrentPositionTimestamp(){
  return currentPositionTimestamp;
}

void SM30::setTempDeg(int temp){
  temperature = temp;
}

int SM30::getTempDeg(){
  return temperature;
}
