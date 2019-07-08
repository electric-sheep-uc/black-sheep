#include "striker.hh"

Striker::Striker(Behaviour* b){
  behave = b;
}

Striker::~Striker(){
  /* Do nothing */
}

bool Striker::update(){
  Main::mot->walk(1.0, 0.0, 0.0); // TODO: Remove hack.
  WARN("Walking");
  return true;

  /* TODO: Find ball. */

  /* TODO: Walk towards ball and locate goal. */

  /* TODO: When at ball, locate goal. */

  /* TODO: If ball close and we know where we are, kick towards enemy goal. */

  /* TODO: If ball close and we are lost, kick away from goals. */

  /* We shouldn't ever reach here */
  return false;
}
