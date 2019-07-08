#pragma once

#include "role/role.hh"

/**
 * behaviour.hh
 *
 * Handle the agents behaviour based on the many system sensors and decide what
 * action needs to be taken.
 **/
class Behaviour{
  private:
    int robotID;
    int teamID;
    Role* shared;
    Role* role;

  public:
    /**
     * Behaviour()
     *
     * Initialize the current behaviour and setup any related variables to
     * called on later.
     **/
    Behaviour();

    /**
     * ~Behaviour()
     *
     * Release any associated memory.
     **/
    ~Behaviour();

    /**
     * update()
     *
     * Allow the current behaviour to be updated based on the most recent
     * available information and to then decide on an appropriate action.
     **/
    void update();
};
