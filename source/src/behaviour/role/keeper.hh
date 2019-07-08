#pragma once

#include "role.hh"

#include "../behaviour.hh"

/**
 * keeper.hh
 *
 * The keeper behaviour.
 **/
class Keeper : public Role{
  private:
    Behaviour* behave;

  public:
    /**
     * Keeper()
     *
     * Initialize the class.
     *
     * @param b The behaviour instance.
     **/
    Keeper(Behaviour* b);

    /**
     * ~Keeper()
     *
     * Free up memory associated with the class.
     **/
    ~Keeper();

    bool update();
};
