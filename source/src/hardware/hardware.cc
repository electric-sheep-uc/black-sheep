#include "hardware.hh"

#include "../log.hh"
#include "driver/gpio/gpio.cc"
#include "driver/i2c/gyro.cc"
#include "driver/serial/smartcontroller.cc"
//#include "motor/fs6535m.cc"
//#include "motor/mg995.cc"
#include "motor/sm30.cc"

Hardware::Hardware(){
  numMotors = *Main::config->getInt("motor.num-motors").get();
  motors = (Motor**)malloc(numMotors * sizeof(Motor*));
  running = true;
  LOG("Initializing IMU");
  if(*Main::config->getInt("gyro.active").get() > 0){
    gyro = new Gyro();
  }else{
    gyro = NULL;
  }
  LOG("Initializing GPIO buttons");
  /* Setup buttons correctly */
  GPIO::init();
  playButton  = new GPIO("playButton",  (GPIO::PIN)27, GPIO::VOLTAGE::V5, GPIO::CAPABILITY::IN);
  relaxButton = new GPIO("relaxButton", (GPIO::PIN)28, GPIO::VOLTAGE::V5, GPIO::CAPABILITY::IN);
  LOG("Initializing PWM controller");
  #if RPI == 1
    /* Setup PWM servo controller */
//    if(*Main::config->getInt("motor.pwm.active").get() > 0){
      pwm = new PCA9685Servo();
//      pwm->SetLeftUs(*Main::config->getInt("motor.pwm.fs6535m.pulse-low").get());
//      pwm->SetRightUs(*Main::config->getInt("motor.pwm.fs6535m.pulse-high").get());
//    }else{
//      pwm = NULL;
//    }
  #else
  pwm = NULL;
  #endif
  /* Setup smart controller communications */
  if(*Main::config->getInt("motor.smart.active").get() > 0){
    LOGM("Open port on -> ", Main::config->getString("motor.smart.interface-a").c_str());
    sca = new SmartController(
      Main::config->getString("motor.smart.interface-a").c_str()
    );
    sca->openPort();
    if(!sca->isActive()){
      running = false;
      WARN("Failed to open port");
    }
    sca->startComms();
    if(!sca->isActive()){
      running = false;
      WARN("Failed to start communication");
    }
//    LOGM("Open port on -> ", Main::config->getString("motor.smart.interface-b").c_str());
//    scb = new SmartController(
//      Main::config->getString("motor.smart.interface-b").c_str()
//    );
//    scb->openPort();
//    if(!scb->isActive()){
//      running = false;
//      WARN("Failed to open port");
//    }
//    scb->startComms();
//    if(!scb->isActive()){
//      running = false;
 //     WARN("Failed to start communication");
 //   }
  }else{
    sca = NULL;
//    scb = NULL;
  }
  /* Setup motors */
  motors[0]  = new SM30(Motor::TYPE::MG995, Motor::POSITION::NECK_PITCH,           "neck-pitch"          );
  motors[1]  = new SM30(Motor::TYPE::MG995, Motor::POSITION::NECK_YAW,             "neck-yaw"            );
  motors[2]  = new SM30(Motor::TYPE::MG995, Motor::POSITION::SHOULDER_PITCH_LEFT,  "shoulder-pitch-left" );
  motors[3]  = new SM30(Motor::TYPE::MG995, Motor::POSITION::SHOULDER_PITCH_RIGHT, "shoulder-pitch-right");
  motors[4]  = new SM30(Motor::TYPE::MG995, Motor::POSITION::SHOULDER_ROLL_LEFT,   "shoulder-roll-left"  );
  motors[5]  = new SM30(Motor::TYPE::MG995, Motor::POSITION::SHOULDER_ROLL_RIGHT,  "shoulder-roll-right" );
  motors[6]  = new SM30(Motor::TYPE::MG995, Motor::POSITION::ELBOW_PITCH_LEFT,     "elbow-pitch-left"    );
  motors[7]  = new SM30(Motor::TYPE::MG995, Motor::POSITION::ELBOW_PITCH_RIGHT,    "elbow-pitch-right"   );
  motors[8]  = new SM30(Motor::TYPE::SM30,  Motor::POSITION::HIP_YAW_LEFT,         "hip-yaw-left"        );
  motors[9]  = new SM30(Motor::TYPE::SM30,  Motor::POSITION::HIP_YAW_RIGHT,        "hip-yaw-right"       );
  motors[10] = new SM30(Motor::TYPE::SM30,  Motor::POSITION::HIP_ROLL_LEFT,        "hip-roll-left"       );
  motors[11] = new SM30(Motor::TYPE::SM30,  Motor::POSITION::HIP_ROLL_RIGHT,       "hip-roll-right"      );
  motors[12] = new SM30(Motor::TYPE::SM30,  Motor::POSITION::HIP_PITCH_LEFT,       "hip-pitch-left"      );
  motors[13] = new SM30(Motor::TYPE::SM30,  Motor::POSITION::HIP_PITCH_RIGHT,      "hip-pitch-right"     );
  motors[14] = new SM30(Motor::TYPE::SM30,  Motor::POSITION::KNEE_PITCH_LEFT,      "knee-pitch-left"     );
  motors[15] = new SM30(Motor::TYPE::SM30,  Motor::POSITION::KNEE_PITCH_RIGHT,     "knee-pitch-right"    );
  motors[16] = new SM30(Motor::TYPE::SM30,  Motor::POSITION::ANKLE_PITCH_LEFT,     "ankle-pitch-left"    );
  motors[17] = new SM30(Motor::TYPE::SM30,  Motor::POSITION::ANKLE_PITCH_RIGHT,    "ankle-pitch-right"   );
  motors[18] = new SM30(Motor::TYPE::SM30,  Motor::POSITION::ANKLE_ROLL_LEFT,      "ankle-roll-left"     );
  motors[19] = new SM30(Motor::TYPE::SM30,  Motor::POSITION::ANKLE_ROLL_RIGHT,     "ankle-roll-right"    );
  headMask = 0;
  armMask = 0;
  legMask = 0;
  for(int x = 0; x < numMotors; x++){
    motors[x]->init();
    /* Create masks based on motor type */
    int i = 1 << x;
    switch(motors[x]->getMotorType()){
      case Motor::TYPE::MG995:
        headMask |= i;
        break;
      case Motor::TYPE::FS6535M:
        armMask |= i;
        break;
      case Motor::TYPE::SM30:
        legMask |= i;
        SmartController::Packet pkt;
        unsigned char param[3];
        /* Send the motor position command */
        pkt.param = param;
        pkt.id = motors[x]->getKinematicPosition();
        pkt.cmd = SmartController::CMD::WRITE_DATA;
        pkt.numParam = 2;
        pkt.param[0] = SmartController::ADD_TABLE::MAX_INPUT_VOLTAGE;
        pkt.param[1] = 0xFF; // 25.5V ish
        pkt.response = true;
        if(sca != NULL){
          pkt = sca->writePacket(pkt);
        }
        /* Send the motor position command */
//        pkt.param = param;
//        pkt.id = motors[x]->getKinematicPosition();
//        pkt.cmd = SmartController::CMD::WRITE_DATA;
//        pkt.numParam = 2;
//        pkt.param[0] = SmartController::ADD_TABLE::MAX_INPUT_VOLTAGE;
//        pkt.param[1] = 0xFF; // 25.5V ish
//        pkt.response = false;
//        if(scb != NULL){
//          pkt = scb->writePacket(pkt);
//        }
        break;
      default:
        WARN("Motor type not implemented.");
        break;
    }
  }
}

Hardware::~Hardware(){
  free(motors);
  close();
}

void Hardware::update(int* pose){
  /* Let this method spin if we have to */
  if(isRunning() && pose != NULL){
    /* Service gyro */
    if(gyro != NULL){
      gyro->update();
    }
    /* Service motors */
    for(int x = 0; x < numMotors; x++){
      /* Update motors based on pose */
      switch(motors[x]->getMotorType()){
        case Motor::TYPE::SM30:
          SmartController::Packet pkt;
          unsigned char param[3];
          /* Send the motor position command */
          pkt.param = param;
          pkt.id = motors[x]->getKinematicPosition();
          pkt.cmd = SmartController::CMD::WRITE_DATA;
          pkt.numParam = 3;
          pkt.param[0] = SmartController::ADD_TABLE::TARGET_POSITION_LOW;
          pkt.param[1] = (pose[x] >> 0) & 0xFF;
          pkt.param[2] = (pose[x] >> 8) & 0xFF;
          pkt.response = true;
          if(sca != NULL){
            pkt = sca->writePacket(pkt);
          }
          /* Send the motor position command */
//          pkt.param = param;
//          pkt.id = motors[x]->getKinematicPosition();
//          pkt.cmd = SmartController::CMD::WRITE_DATA;
//          pkt.numParam = 3;
//          pkt.param[0] = SmartController::ADD_TABLE::TARGET_POSITION_LOW;
//          pkt.param[1] = (pose[x] >> 0) & 0xFF;
//          pkt.param[2] = (pose[x] >> 8) & 0xFF;
//          pkt.response = false;
//          if(scb != NULL){
//            pkt = scb->writePacket(pkt);
//          }
          /* Read the motor temperature */
//          pkt.param = param;
//          pkt.id = motors[x]->getKinematicPosition();
//          pkt.cmd = SmartController::CMD::READ_DATA;
//          pkt.numParam = 1;
//          pkt.param[0] = SmartController::ADD_TABLE::CURRENT_TEMPERATURE;
//          pkt.response = true;
//          if(sc != NULL){
//            pkt = sc->writePacket(pkt);
//            ((SM30*)motors[x])->setTempDeg(pkt.param[0]);
//          }
          break;
        case Motor::TYPE::MG995:
        case Motor::TYPE::FS6535M:
//          #if RPI == 1
//            if(pwm != NULL){
//              pwm->SetAngle(motors[x]->getKinematicPosition(), pose[x]);
//            }
//          #endif
          break;
        default:
          WARN("Motor type not implemented.");
          break;
      }
    }
  }
}

void Hardware::close(){
  LOG("Closing port...");
  if(sca != NULL){
    sca->closePort();
  }
  if(scb != NULL){
    scb->closePort();
  }
  running = false;
}

Motor** Hardware::getMotors(){
  return motors;
}

Gyro* Hardware::getGyro(){
  return gyro;
}

GPIO* Hardware::getPlayButton(){
  return playButton;
}

GPIO* Hardware::getRelaxButton(){
  return relaxButton;
}

long Hardware::getHeadMask(){
  return headMask;
}

long Hardware::getArmsMask(){
  return armMask;
}

long Hardware::getLegsMask(){
  return legMask;
}
