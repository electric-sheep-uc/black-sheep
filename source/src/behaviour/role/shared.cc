#include "shared.hh"

#include "../../network/GameController/include/RoboCupGameControlData.h"
/* NOTE: Game controller data structure defines tonnes of global constants. */
#undef NONE

#include "../../hardware/motor/sm30.hh"

Shared::Shared(Behaviour* b){
  buttonDebounce = *Main::config->getInt("button.debounce-ms").get();
  numMotors = *Main::config->getInt("motor.num-motors").get();
  sm30MaxTemp = *Main::config->getInt("motor.smart.max-temp").get();
  teamID = *Main::config->getInt("player.id-team").get();
  playerID = *Main::config->getInt("player.id-robot").get();
  behave = b;
  mode = MODE_BUTTON::READY;
  modeLast = CLOCK::CURRENT_TIME_MILLIS();
  relax = false;
  relaxLast = CLOCK::CURRENT_TIME_MILLIS();
}

Shared::~Shared(){
  /* Do nothing */
}

bool Shared::update(){
  /* Breakdown game controller state */
  RoboCupGameControlData gc = Main::gs->getGameState();
  TeamInfo ti = gc.teams[0];
  for(int x = 0; x < 2; x++){
    if(gc.teams[x].teamNumber == teamID){
      ti = gc.teams[x];
    }
  }
  RobotInfo ri = ti.players[playerID - 1];
  /* Get access to hardware sensors */
  Motion* mot = Main::mot;
  Hardware* hw = mot->getHardware();
  Motor** motors = hw->getMotors();
  Gyro* gyro = hw->getGyro();
  /* Figure out current mode button */
  GPIO* modeButton = hw->getPlayButton();
  if(
    modeButton != NULL            &&
    modeButton->getDigitalInput() &&
    CLOCK::CURRENT_TIME_MILLIS() - modeLast >= buttonDebounce
  ){
    LOG("mode button");//TODO
    ++mode;
    mode = mode % MODE_BUTTON::LENGTH;
    modeLast = CLOCK::CURRENT_TIME_MILLIS();
  }
  /* Figure out current relax button */
  GPIO* relaxButton = hw->getRelaxButton();
  if(
    relaxButton != NULL            &&
    relaxButton->getDigitalInput() &&
    CLOCK::CURRENT_TIME_MILLIS() - relaxLast >= buttonDebounce
  ){
    LOG("relax button");//TODO
    relax = !relax;
    relaxLast = CLOCK::CURRENT_TIME_MILLIS();
  }
  /* If button mode ready + not in penalty, use game controller, otherwise use button mode */
  bool penalty = ri.penalty != PENALTY_NONE;
  bool ready =   (mode == MODE_BUTTON::READY && !penalty) ? (gc.state == STATE_READY)   : (mode == MODE_BUTTON::READY);
  bool set =     (mode == MODE_BUTTON::READY && !penalty) ? (gc.state == STATE_SET)     : (mode == MODE_BUTTON::SET);
  bool playing = (mode == MODE_BUTTON::READY && !penalty) ? (gc.state == STATE_PLAYING) : (mode == MODE_BUTTON::PLAYING);

//  /* Detect if motors are overheating */
//  for(int x = 0; x < numMotors; x++){
//    /* Check if we can read temperature and if it is too high */
//    if(
//      motors[x]->getMotorType() == Motor::TYPE::SM30 &&
//      ((SM30*)motors[x])->getTempDeg() > sm30MaxTemp
//    ){
//      WARNM("Motors off, motor overheated -> ", motors[x]->getMotorName());
//      /* Turn off motors */
//      return true;
//    }else{
//      /* TODO: -- Remove this debug code. -- */
//      if(motors[x]->getMotorType() == Motor::TYPE::SM30){
//        LOGM("Motor name -> ", motors[x]->getMotorName().c_str());
//        LOGI("Motor temp -> ", ((SM30*)motors[x])->getTempDeg());
//      }
//      /* TODO: -- Remove this debug code. -- */
//    }
//  }

  /* Detect if we are in a game */
  if(!ready && !set && !playing){
    /* TODO: We should stop doing what we are doing. */
    /* TODO: Sit down. */
    return true;
  }

  /* Detect set state */
  if(ready){
    /* TODO: Find localized position if possible. */
    return true;
  }

  /* Detect ready state */
  if(set){
    /* TODO: Stand still. */
    return true;
  }

//  /* Detect fallen state */
//  if(gyro != NULL && gyro->isFalling()){
//    WARN("FALLING");//TODO
//    if(Main::mot->getCurrentMotionName() != "get-up-from-back" &&
//       Main::mot->getCurrentMotionName() != "get-up-from-front"){
//      if(gyro->fallenFront()){
//        Main::mot->action("get-up-from-front");
//      }else{
//        Main::mot->action("get-up-from-back");
//      }
//      return true;
//    }
//  }

  /* It looks as if we are playing, perform role specific behaviour */
  return false;
}
