#pragma once

#ifndef mitecom
  #define mitecom
  #include "mitecom/mitecom-network.cpp"
  #include "mitecom/mitecom-handler.cpp"
#endif

#include <limits.h>

/**
 * teamstate.hh
 *
 * Handle processing of network based team state.
 **/
class TeamState{
  private:
    bool running;
    bool serviceBusy;
    unsigned int localPort;
    unsigned int remotePort;
    unsigned int robotID;
    unsigned int teamID;
    int lostMateDelay;
    int broadcastDelay;
    long long broadcastTimeout;
    int socket;
    char buffer[SHRT_MAX];
    MixedTeamMates teamMates;
    MixedTeamMate robot;

  public:
    /**
     * TeamState()
     *
     * Initialize the team state and all associated variables.
     **/
    TeamState();

    /**
     * ~TeamState()
     *
     * De-initialize the team state and associated memory.
     **/
    ~TeamState();

    /**
     * service()
     *
     * Service the network and process received data.
     **/
    void service();

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
     * close()
     *
     * Close the server and associated resources.
     **/
    void close();
};
