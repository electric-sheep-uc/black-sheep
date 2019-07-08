#include "behaviour.hh"

#include "role/shared.cc"
#include "role/defender.cc"
#include "role/fielder.cc"
#include "role/keeper.cc"
#include "role/striker.cc"

Behaviour::Behaviour(){
  /* Get variables from configuration */
  robotID = *Main::config->getInt("player.id-robot").get();
  teamID = *Main::config->getInt("player.id-team").get();
  /* Figure out role for player */
  shared = new Shared(this);
  switch(robotID){
    case 1 :
      LOG("Setting Keeper role");
      role = new Keeper(this);
      break;
    case 2 :
      LOG("Setting Defender role");
      role = new Defender(this);
      break;
    case 3 :
      LOG("Setting Fielder role");
      role = new Fielder(this);
      break;
    case 4 :
      LOG("Setting Fielder role");
      role = new Fielder(this);
      break;
    case 5 :
      LOG("Setting Striker role");
      role = new Striker(this);
      break;
    default :
      WARN("Unknown robot ID, setting to striker");
      role = new Striker(this);
      break;
  }
}

Behaviour::~Behaviour(){
  /* Do nothing */
}

void Behaviour::update(){
  /* Check for shared behaviour */
  bool set = shared->update();
  if(!set){
    /* Check for specific role behaviour */
    role->update();
  }
  /* Make sure something happened */
  if(!set){
    WARN("Uncaught behaviour, undesired effects may occur");
  }
}
