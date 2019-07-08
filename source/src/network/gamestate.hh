#pragma once

#ifndef mitecom
  #define mitecom
  #include "mitecom/mitecom-network.cpp"
  #include "mitecom/mitecom-handler.cpp"
#endif
#include "GameController/include/RoboCupGameControlData.h"

#include <limits.h>

/**
 * gamestate.hh
 *
 * Handle processing of network based game state.
 **/
class GameState{
  private:
    bool running;
    bool serviceBusy;
    unsigned int localPort;
    unsigned int remotePort;
    unsigned int robotID;
    unsigned int teamID;
    int lostControllerDelay;
    int broadcastDelay;
    long long broadcastTimeout;
    int socket;
    char buffer[SHRT_MAX];
    RoboCupGameControlData gameState;
    RoboCupGameControlData data;
    RoboCupGameControlData gc;
    RoboCupGameControlReturnData retData;
    RoboCupGameControlData gameStateClone;

  public:
    /**
     * GameState()
     *
     * Initialize the game state and all associated variables.
     **/
    GameState();

    /**
     * ~GameState()
     *
     * De-initialize the game state and associated memory.
     **/
    ~GameState();

    /**
     * service()
     *
     * Service the network and process received data.
     **/
    void service();

    /**
     * parseIncoming()
     *
     * Simple parser for game controller messages that creates a valid
     * structure for use.
     *
     * @param messageData The message data received via the network.
     * @param messageLength The length of the message received on the network.
     * @return A valid game controller state, otherwise NULL.
     **/
    RoboCupGameControlData parseIncoming(
      const void* messageData,
      uint32_t messageLength
    );

    /**
     * isRunning()
     *
     * Check whether the server is still running.
     *
     * @return True if server is running, otherwise false.
     **/
    bool isRunning();

    /**
     * isBusy()
     *
     * Check whether the server is busy actively processing requests.
     *
     * @return True if server is busy, otherwise false.
     **/
    bool isBusy();

    /**
     * getGameState()
     *
     * Get clone of current game state.
     *
     * @return The current game state.
     **/
    RoboCupGameControlData getGameState();

    /**
     * close()
     *
     * Close the server and associated resources.
     **/
    void close();
};
