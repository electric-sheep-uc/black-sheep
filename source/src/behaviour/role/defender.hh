#pragma once

#include "role.hh"

#include "../behaviour.hh"

/**
 * defender.hh
 *
 * The defender behaviour.
 **/
class Defender : public Role{
  private:
    Behaviour* behave;

  public:
    /**
     * Defender()
     *
     * Initialize the class.
     *
     * @param b The behaviour instance.
     **/
    Defender(Behaviour* b);

    /**
     * ~Defender()
     *
     * Free up memory associated with the class.
     **/
    ~Defender();

    bool update();
};
