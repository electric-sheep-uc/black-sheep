#pragma once

#include "role.hh"

#include "../behaviour.hh"

/**
 * shared.hh
 *
 * The shared behaviour.
 **/
class Shared : public Role{
  private:
    enum MODE_BUTTON{
      READY = 0,
      SET = 1,
      PLAYING = 2,
      PENALIZE = 3,
      LENGTH = 4
    };

    int buttonDebounce;
    int numMotors;
    int sm30MaxTemp;
    int teamID;
    int playerID;

    Behaviour* behave;
    int mode;
    long long modeLast;
    bool relax;
    long long relaxLast;

  public:
    /**
     * Shared()
     *
     * Initialize the class.
     *
     * @param b The behaviour instance.
     **/
    Shared(Behaviour* b);

    /**
     * ~Shared()
     *
     * Free up memory associated with the class.
     **/
    ~Shared();

    bool update();
};
