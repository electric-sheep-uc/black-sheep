#pragma once

#include "role.hh"

#include "../behaviour.hh"

/**
 * striker.hh
 *
 * The striker behaviour.
 **/
class Striker : public Role{
  private:
    Behaviour* behave;

  public:
    /**
     * Striker()
     *
     * Initialize the class.
     *
     * @param b The behaviour instance.
     **/
    Striker(Behaviour* b);

    /**
     * ~Striker()
     *
     * Free up memory associated with the class.
     **/
    ~Striker();

    bool update();
};
