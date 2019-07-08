#pragma once

/**
 * role.hh
 *
 * Interface for role representation.
 **/
class Role{
  public:
    /**
     * update()
     *
     * Update the current action(s) based on the current sense(s).
     *
     * @return Actions that have been setup for the player to take. Note that
     * there can be multiple combined actions as the torso may do more than one
     * action at a time, for example: look for ball and mover towards area. The
     * number of actions expected are three and by returning NULL for any means
     * "do the default".
     *
     * @return True if update performed, otherwise false.
     **/
    virtual bool update() = 0;
};
