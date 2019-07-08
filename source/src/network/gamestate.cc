#include "gamestate.hh"

#include "../main.hh"
#include "../log.hh"
#include "../utils/clock.hh"

GameState::GameState(){
  running = true;
  serviceBusy = false;
  localPort = *Main::config->getInt("game-controller.port-local").get();
  remotePort = *Main::config->getInt("game-controller.port-remote").get();
  robotID = *Main::config->getInt("player.id-robot").get();
  teamID = *Main::config->getInt("player.id-team").get();
  lostControllerDelay = *Main::config->getInt("game-controller.lost-controller-ms").get();
  broadcastDelay = *Main::config->getInt("game-controller.broadcast-ms").get();
  broadcastTimeout = CLOCK::CURRENT_TIME_MILLIS() + broadcastDelay;
  /* Start the socket */
  socket = mitecom_open(localPort);
  /* Make sure it was actually opened */
  if(socket < 0){
    WARNI("Unable to open socket on port ", localPort);
    running = false;
  }
}

GameState::~GameState(){
  /* Close if we haven't already */
  if(running){
    close();
  }
}

void GameState::service(){
  serviceBusy = false;
  /* Try to get some data */
  int msgLen = mitecom_receive(socket, buffer, SHRT_MAX);
  /* If we have something, process it */
  if(msgLen > 0){
    /* Process game controller messages */
    gc = parseIncoming(buffer, msgLen);
    if(gc.header[0] != 0 && gc.packetNumber != gameState.packetNumber){
      memcpy((void*)&gameState, (void*)&gc, sizeof(RoboCupGameControlData));
    }
    /* Tell the server loop there might be more */
    serviceBusy = true;
  }
  /* Check if we need to broadcast */
  if(broadcastTimeout <= CLOCK::CURRENT_TIME_MILLIS()){
    LOG("Broadcasting current state to game controller");
    retData.header[0] = GAMECONTROLLER_RETURN_STRUCT_HEADER[0];
    retData.header[1] = GAMECONTROLLER_RETURN_STRUCT_HEADER[1];
    retData.header[2] = GAMECONTROLLER_RETURN_STRUCT_HEADER[2];
    retData.header[3] = GAMECONTROLLER_RETURN_STRUCT_HEADER[3];
    retData.version = GAMECONTROLLER_RETURN_STRUCT_VERSION;
    retData.team = teamID;
    retData.player = robotID;
    /* TODO: Return correct current state. */
    retData.message = GAMECONTROLLER_RETURN_MSG_ALIVE;
    mitecom_broadcast(socket, remotePort, &retData, sizeof(RoboCupGameControlReturnData));
    /* Reset timeout */
    broadcastTimeout = CLOCK::CURRENT_TIME_MILLIS() + broadcastDelay;
  }
}

RoboCupGameControlData GameState::parseIncoming(
  const void* messageData,
  uint32_t messageLength
){
  const RoboCupGameControlData *message = (const RoboCupGameControlData*)messageData;
  /* Check magic bytes in header */
  if(
    GAMECONTROLLER_STRUCT_HEADER[0] != message->header[0] ||
    GAMECONTROLLER_STRUCT_HEADER[1] != message->header[1] ||
    GAMECONTROLLER_STRUCT_HEADER[2] != message->header[2] ||
    GAMECONTROLLER_STRUCT_HEADER[3] != message->header[3]
  ){
    WARN("Magic value mismatch in received message");
    data.header[0] = 0;
    return data;
  }
  if(GAMECONTROLLER_STRUCT_VERSION != message->version){
    WARN("Unsupported protocol received");
    data.header[0] = 0;
    return data;
  }
  /* Check that we got the full message */
  if(messageLength != sizeof(RoboCupGameControlData)){
    WARN("Mismatched message length");
    data.header[0] = 0;
    return data;
  }
  return data;
}

bool GameState::isRunning(){
  return running;
}

bool GameState::isBusy(){
  return running && serviceBusy;
}

RoboCupGameControlData GameState::getGameState(){
  memcpy((void*)&gameStateClone, (void*)&gameState, sizeof(RoboCupGameControlData));
  return gameStateClone;
}

void GameState::close(){
  running = false;
}
