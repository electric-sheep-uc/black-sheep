#include "teamstate.hh"

#include "../main.hh"
#include "../log.hh"
#include "../utils/clock.hh"

TeamState::TeamState(){
  running = true;
  serviceBusy = false;
  localPort = *Main::config->getInt("mitecom.port-local").get();
  remotePort = *Main::config->getInt("mitecom.port-remote").get();
  robotID = *Main::config->getInt("player.id-robot").get();
  teamID = *Main::config->getInt("player.id-team").get();
  lostMateDelay = *Main::config->getInt("mitecom.lost-mate-ms").get();
  broadcastDelay = *Main::config->getInt("mitecom.broadcast-ms").get();
  broadcastTimeout = CLOCK::CURRENT_TIME_MILLIS() + broadcastDelay;
  /* Start the socket */
  socket = mitecom_open(localPort);
  /* Make sure it was actually opened */
  if(socket < 0){
    WARNI("Unable to open socket on port ", localPort);
    running = false;
  }
}

TeamState::~TeamState(){
  /* Close if we haven't already */
  if(running){
    close();
  }
}

void TeamState::service(){
  serviceBusy = false;
  /* Try to get some data */
  int msgLen = mitecom_receive(socket, buffer, SHRT_MAX);
  /* If we have something, process it */
  if(msgLen > 0){
    MixedTeamMate teamMate = MixedTeamParser::parseIncoming(buffer, msgLen, teamID);
    /* Make sure we don't just hear ourself */
    if(teamMate.robotID && teamMate.robotID != robotID){
      LOGI("Received update from team mate ", teamMate.robotID);
      /* Log the fact we found somebody new */
      if(teamMates.find(teamMate.robotID) == teamMates.end()){
        LOGI("Adding team mate ", teamMate.robotID);
      }
      /* Store new data */
      teamMates[teamMate.robotID] = teamMate;
      teamMates[teamMate.robotID].lastUpdate = CLOCK::CURRENT_TIME_MILLIS();
    }
    /* Tell the server loop there might be more */
    serviceBusy = true;
  }
  /* Check if we need to broadcast */
  if(broadcastTimeout <= CLOCK::CURRENT_TIME_MILLIS()){
    LOG("Broadcasting current state to team");
    /* TODO: Populate list of our current information. */
    robot.robotID = robotID;
    robot.data[ROBOT_CURRENT_ROLE] = ROLE_OTHER;
    robot.data[ROBOT_ABSOLUTE_X] = 0;
    robot.data[ROBOT_ABSOLUTE_Y] = 0;
    robot.data[ROBOT_ABSOLUTE_ORIENTATION] = 0;
    robot.data[ROBOT_ABSOLUTE_BELIEF] = 0;
    /* Serialize and send */
    MixedTeamCommMessage* msgDataPtr = NULL;
    unsigned int msgLen = 0;
    msgDataPtr = MixedTeamParser::create(&msgLen, robot, teamID, robotID);
    mitecom_broadcast(socket, remotePort, msgDataPtr, msgLen);
    free(msgDataPtr);
    /* Get rid of old team mates */
    for(MixedTeamMates::iterator it = teamMates.begin(); it != teamMates.end();){
      if((it->second).lastUpdate + lostMateDelay < CLOCK::CURRENT_TIME_MILLIS()){
        LOGI("Team mate not responding, removing ", it->first);
        teamMates.erase(it++);
      }else{
        it++;
      }
    }
    /* Reset timeout */
    broadcastTimeout = CLOCK::CURRENT_TIME_MILLIS() + broadcastDelay;
  }
}

bool TeamState::isRunning(){
  return running;
}

bool TeamState::isBusy(){
  return running && serviceBusy;
}

void TeamState::close(){
  running = false;
}
