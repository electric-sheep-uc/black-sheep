#pragma once

#include "role.hh"

#include "../behaviour.hh"

/**
 * fielder.hh
 *
 * The fielder behaviour.
 **/
class Fielder : public Role{
  private:
    Behaviour* behave;

  public:
    /**
     * Fielder()
     *
     * Initialize the class.
     *
     * @param b The behaviour instance.
     **/
    Fielder(Behaviour* b);

    /**
     * ~Fielder()
     *
     * Free up memory associated with the class.
     **/
    ~Fielder();

    bool update();
};
