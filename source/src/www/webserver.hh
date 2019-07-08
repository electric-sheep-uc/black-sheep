#pragma once

#include "../vision/vision.hh"

/**
 * webserver.hh
 *
 * A basic web server for the purpose of allowing debug and configuration
 * changes to the agent.
 **/
class WebServer{
  private:
    int port;

  public:
    /**
     * WebServer()
     *
     * Initialize the server variables and pre-load as much as possible into
     * RAM.
     *
     * @param vision The vision processing object.
     **/
    WebServer();

    /**
     * ~WebServer()
     *
     * Free up any and all allocated resources.
     **/
    ~WebServer();

    /**
     * run()
     *
     * Run the blocking web server in an infinite loop.
     **/
    void run();
};
