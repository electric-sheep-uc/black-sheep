#include "walking.hh"

#include "../main.hh"
#include "../log.hh"
#include "../utils/clock.hh"

Walking::Walking(){
  /* Initialize walk engine with body and engine parameters */
  params.distHipToKnee = *Main::config->getDouble("walk.params.dist-hip-to-knee").get();
  params.distKneeToAnkle = *Main::config->getDouble("walk.params.dist-knee-to-ankle").get();
  params.distAnkleToGround = *Main::config->getDouble("walk.params.dist-ankle-to-ground").get();
  params.distFeetLateral = *Main::config->getDouble("walk.params.dist-feet-lateral").get();
  params.freq = *Main::config->getDouble("walk.params.freq").get();
  params.enabledGain = 0.0;
  params.supportPhaseRatio = *Main::config->getDouble("walk.params.support-phase-ratio").get();
  params.footYOffset = *Main::config->getDouble("walk.params.foot-y-offset").get();
  maxStepGain = *Main::config->getDouble("walk.params.step-gain").get();
  params.stepGain = 0.0;
  params.riseGain = *Main::config->getDouble("walk.params.rise-gain").get();
  maxTurnGain = *Main::config->getDouble("walk.params.turn-gain").get();
  params.turnGain = 0.0;
  maxLateralGain = *Main::config->getDouble("walk.params.lateral-gain").get();
  params.lateralGain = 0.0;
  params.trunkZOffset = *Main::config->getDouble("walk.params.trunk-z-offset").get();
  params.swingGain = *Main::config->getDouble("walk.params.swing-gain").get();
  params.swingRollGain = *Main::config->getDouble("walk.params.swing-roll-gain").get();
  params.swingPhase = *Main::config->getDouble("walk.params.swing-phase").get();
  params.stepUpVel = *Main::config->getDouble("walk.params.step-up-vel").get();
  params.stepDownVel = *Main::config->getDouble("walk.params.step-down-vel").get();
  params.riseUpVel = *Main::config->getDouble("walk.params.rise-up-vel").get();
  params.riseDownVel = *Main::config->getDouble("walk.params.rise-down-vel").get();
  params.swingPause = *Main::config->getDouble("walk.params.swing-pause").get();
  params.swingVel = *Main::config->getDouble("walk.params.swing-vel").get();
  params.trunkXOffset = *Main::config->getDouble("walk.params.trunk-x-offset").get();
  params.trunkYOffset = *Main::config->getDouble("walk.params.trunk-y-offset").get();
  params.trunkPitch = *Main::config->getDouble("walk.params.trunk-pitch").get();
  params.trunkRoll = *Main::config->getDouble("walk.params.trunk-roll").get();
  params.extraLeftX = *Main::config->getDouble("walk.params.extra-left-x").get();
  params.extraLeftY = *Main::config->getDouble("walk.params.extra-left-y").get();
  params.extraLeftZ = *Main::config->getDouble("walk.params.extra-left-z").get();
  params.extraRightX = *Main::config->getDouble("walk.params.extra-right-x").get();
  params.extraRightY = *Main::config->getDouble("walk.params.extra-right-y").get();
  params.extraRightZ = *Main::config->getDouble("walk.params.extra-right-z").get();
  params.extraLeftYaw = *Main::config->getDouble("walk.params.extra-left-yaw").get();
  params.extraLeftPitch = *Main::config->getDouble("walk.params.extra-left-pitch").get();
  params.extraLeftRoll = *Main::config->getDouble("walk.params.extra-left-roll").get();
  params.extraRightYaw = *Main::config->getDouble("walk.params.extra-right-yaw").get();
  params.extraRightPitch = *Main::config->getDouble("walk.params.extra-right-pitch").get();
  params.extraRightRoll = *Main::config->getDouble("walk.params.extra-right-roll").get();
  /* Get ramping values */
  rampEnabledGain = *Main::config->getDouble("walk.ramp.enabled-gain").get();
  rampForwardGain = maxStepGain * *Main::config->getDouble("walk.ramp.forward-gain").get();
  rampSideGain = maxLateralGain * *Main::config->getDouble("walk.ramp.side-gain").get();
  rampTurnGain = maxTurnGain * *Main::config->getDouble("walk.ramp.turn-gain").get();
  /* Setup the pose memory space */
  numMotors = *Main::config->getInt("motor.num-motors").get();
  pose = (int*)malloc(numMotors * sizeof(int));
  /* Initialize target values */
  targetForwardGain = 0.0;
  targetSideGain = 0.0;
  targetTurnGain = 0.0;
  /* Setup time measurement */
  prevTimestamp = -1.0;
  phase = 0.0;
}

Walking::~Walking(){
  free(pose);
}

int* Walking::getPose(Motor** motors){
  /* Make sure we have some sensible time */
  if(prevTimestamp < 0){
    /* NOTE: Prevent a divide by zero crash with minus one. */
    prevTimestamp = CLOCK::CURRENT_TIME_MILLIS() - 1;
  }
  long long currentTimestamp = CLOCK::CURRENT_TIME_MILLIS();
  double deltaTime = (double)(currentTimestamp - prevTimestamp) / 1000.0;
  /* Modulate towards target */
  params.stepGain    += CLAMP(targetForwardGain - params.stepGain, -rampForwardGain, rampForwardGain);
  params.lateralGain += CLAMP(targetSideGain - params.lateralGain, -rampSideGain,    rampSideGain);
  params.turnGain    += CLAMP(targetTurnGain - params.turnGain,    -rampTurnGain,    rampTurnGain);
  /* Is the walk currently enabled? */
  if(params.stepGain != 0.0 || params.lateralGain != 0.0 || params.turnGain != 0.0){
    params.enabledGain = 1.0;
  }
  /* Get the current pose from the walk engine */
  bool success = Rhoban::IKWalk::walk(params, deltaTime, phase, outputs);
  if(!success){
    WARN("Inverse kinematics error, position could not be computed");
    return NULL;
  }else{
    /* TODO: We need an elegant way to handle arms and head. */
    pose[ 0] = 0;
    pose[ 1] = 0;
    pose[ 2] = 0;
    pose[ 3] = 0;
    pose[ 4] = 0;
    pose[ 5] = 0;
    pose[ 6] = 0;
    pose[ 7] = 0;
    pose[ 8] = RAD2RAW(outputs.right_hip_yaw);
    pose[ 9] = RAD2RAW(outputs.left_hip_yaw);
    pose[10] = RAD2RAW(outputs.right_hip_roll);
    pose[11] = RAD2RAW(outputs.left_hip_roll);
    pose[12] = RAD2RAW(outputs.right_hip_pitch);
    pose[13] = RAD2RAW(outputs.left_hip_pitch);
    pose[14] = RAD2RAW(outputs.right_knee);
    pose[15] = RAD2RAW(outputs.left_knee);
    pose[16] = RAD2RAW(outputs.right_ankle_pitch);
    pose[17] = RAD2RAW(outputs.left_ankle_pitch);
    pose[18] = RAD2RAW(outputs.right_ankle_roll / 2);
    pose[19] = RAD2RAW(outputs.left_ankle_roll / 2);
    for(int x = 0; x < numMotors; x++){
      motors[x]->setCurrentPosition(RAW2RAD(pose[x]), currentTimestamp, false);
      motors[x]->setTargetPosition(RAW2RAD(pose[x]), false);
      pose[x] = RAD2RAW(motors[x]->getTargetPosition(true));
    }
  }
  /* Setup previous time */
  prevTimestamp = currentTimestamp;
  return pose;
}

void Walking::transition(double forwardSpeed, double sideSpeed, double turnSpeed){
  /* Set new goals */
  targetForwardGain = forwardSpeed * maxStepGain;
  targetSideGain = sideSpeed * maxLateralGain;
  targetTurnGain = turnSpeed * maxTurnGain;
}

void Walking::clear(){
  /* Slow enabled gain down */
  /* NOTE: The pose processing will fight us until we come to a stand still. */
  params.enabledGain -= rampEnabledGain;
  /* Don't dip below zero */
  if(params.enabledGain <= 0.0){
    params.enabledGain = 0.0;
  }
  /* Set target of zero movement */
  transition(0.0, 0.0, 0.0);
  /* Reset important values */
  if(!isWalking()){
    prevTimestamp = -1.0;
    phase = 0.0;
  }
}

bool Walking::isWalking(){
  /* If we still have enabled gain, we are still walking */
  return params.enabledGain != 0.0 ||
         params.stepGain    != 0.0 ||
         params.lateralGain != 0.0 ||
         params.turnGain    != 0.0;
}
