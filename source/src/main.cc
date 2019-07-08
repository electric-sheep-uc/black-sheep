#include "main.hh"

#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <string>
#include <thread>
#include <unistd.h>

#include "behaviour/behaviour.cc"
#include "config/config.cc"
#include "hardware/driver/camera/camera.cc"
#include "localization/localization.cc"
#include "log.hh"
#include "motion/motion.cc"
#include "network/gamestate.cc"
#include "network/teamstate.cc"
#include "utils/timing.cc"
#include "version.hh"
#include "vision/lut/colour.hh"
#include "vision/vision.cc"
#include "www/webserver.cc"

Config* Main::config;
Localization* Main::loc;
Motion* Main::mot;
GameState* Main::gs;
TeamState* Main::ts;
Timing* Main::time;
Vision* Main::vis;

/**
 * main()
 *
 * Main entry point into the program, responsible for parsing the command line
 * arguments and starting the program correctly.
 *
 * @param argc Number of arguments.
 * @param argv An array of arguments.
 * @return The exit status of the program.
 **/
#ifndef TEST
int main(int argc, char** argv){
  Main::config = new Config("template.json", true);
  /* NOTE: Enable if using LUT colour space conversion. */
#if ENABLE_COLOUR_LUT == TRUE
  Colour::init();
#endif
  Main::printWelcome();
  /* Pull out program arguments */
  bool run = true;
  for(int x = 1; x < argc; x++){
    bool matched = false;
    if(argv[x] == std::string("-h") || argv[x] == std::string("--help")){
      x = Main::help(argv, argc, x);
      matched = true;
      run = false;
    }
    if(argv[x] == std::string("-m") || argv[x] == std::string("--motor")){
      x = Main::motor(argv, argc, x);
      matched = true;
      run = false;
    }
    if(!matched){
      WARNM("Argument not understood: ", argv[x]);
      WARN("Please refer to `--help`.");
      run = false;
    }
  }
  /* After processing arguments, should be still run main code? */
  if(run){
    Main::loc = new Localization();
    Main::mot = new Motion();
    Main::gs = new GameState();
    Main::ts = new TeamState();
    Main::time = new Timing();
    Main::vis = new Vision();
    /* Run main threads */
    std::thread mainThread(Main::mainThread);
    std::thread hwThread(Main::hwThread);
    std::thread wwwThread(Main::wwwThread);
    std::thread gameThread(Main::gameThread);
    std::thread teamThread(Main::teamThread);
    /* Wait for them to finish */
    mainThread.join();
    LOG("Main thread finished.");
    hwThread.join();
    LOG("Hardware thread finished.");
    wwwThread.join();
    LOG("Server thread finished.");
    gameThread.join();
    LOG("Game thread finished.");
    teamThread.join();
    LOG("Team thread finished.");
  }else{
    LOG("Not running program due to parameters given.");
  }
  return EXIT_SUCCESS;
}
#endif

void Main::printWelcome(){
  printf(
    "\033[1;32m%s\033[0m by \033[0;36m%s\033[0m\n",
    config->getString("app.name").c_str(),
    config->getString("app.author").c_str()
  );
  printf("\033[1;35mBuilt:\033[0m %s @ %s\n", __DATE__, __TIME__);
  printf("\033[1;35mCommit:\033[0m %s\n", GitHash());
}

int Main::help(char** argv, int argc, int x){
  printf("./robot [OPT]\n");
  printf("\n");
  printf("  OPTions\n");
  printf("\n");
  printf("    -h  --help     Display this help\n");
  printf("    -m  --motor    Directly control motor\n");
  printf("                     <HEX> Motor ID\n");
  printf("                     <INT> Number of parameters\n");
  printf("                     <HEX> Command\n");
  printf("                     <HEX> [HEX] Parameters\n");
  printf("                     <BOL> Wait for response?\n");
  printf("\n");
  printf("  Values\n");
  printf("\n");
  printf("    INT  32 bit integer (i.e, 79, 0, -2078)\n");
  printf("    HEX  Double digit hex (i.e. A0, 00, 67)\n");
  printf("    BOL  Boolean value (i.e. 1 = true, 0 = false)\n");
  return x;
}

int Main::motor(char** argv, int argc, int x){
  ++x;
  /* Check at least minimum number of arguments */
  if(argc - x < 4){
    WARNI("Minimum arguments is 4, found ", argc - x);
    return argc;
  }
  /* Convert arguments */
  int tmp;
  std::stringstream ss;
  SmartController::Packet pkt;
  ss << std::hex << argv[x++];
  ss >> pkt.id;
  ss.clear();
  ss << argv[x++];
  ss >> pkt.numParam;
  ss.clear();
  /* TODO: Check whether we have enough arguments left for params. */
  ss << std::hex << argv[x++];
  ss >> tmp;
  pkt.cmd = (SmartController::CMD)tmp;
  ss.clear();
  unsigned char param[*config->getInt("motor.smart.max-return-data").get()];
  for(int i = 0; i < pkt.numParam; i++){
    ss << std::hex << argv[x++];
    ss >> tmp;
    param[i] = (unsigned char)tmp;
    ss.clear();
  }
  pkt.param = param;
  ss << argv[x++];
  ss >> tmp;
  pkt.response = tmp > 0;
  ss.clear();
  /* Start controller */
  SmartController* sc = new SmartController(
    config->getString("motor.smart.interface-a").c_str()
  );
  sc->openPort();
  if(!sc->isActive()){
    WARN("Failed to open port");
  }
  sc->startComms();
  if(!sc->isActive()){
    WARN("Failed to start communication");
  }
  /* Send packet how it was requested */
  if(pkt.response){
    /* Send packet */
    pkt = sc->writePacket(pkt);
    /* Print packet */
    LOGB("ID         -> ", pkt.id);
    LOGB("Num params -> ", pkt.numParam);
    LOGB("Status     -> ", pkt.cmd);
    for(int i = 0; i < pkt.numParam; i++){
      LOGB("Param      -> ", pkt.param[i]);
    }
  }else{
    /* Send packet */
    sc->writePacket(pkt, true);
    LOG("Packet sense, not waiting for response");
  }
  /* Stop controller */
  sc->closePort();
  return x;
}

void Main::mainThread(){
  Camera* cam = new Camera();
  if(cam->isRunning()){
    cam->update();
  }
  std::thread* visThread = NULL;
  while(cam->isRunning()){
    Main::time->eventStart("vision", "cam-update");
    cam->update();
    Main::time->eventEnd("vision", "cam-update");
    Main::time->eventStart("vision", "vis-preprocess");
    Main::vis->preprocess(cam->getImage());
    Main::time->eventEnd("vision", "vis-preprocess");
    Main::time->eventStart("vision", "vis-process");
    if(visThread != NULL){
      visThread->join();
      delete(visThread);
    }else{
      WARN("Unable to create vision thread.");
    }
    visThread = new(nothrow) std::thread(Main::visThread);
    Main::time->eventEnd("vision", "vis-process");
    Main::time->loopTick("vision");
  }
  cam->close();
}

void Main::visThread(){
  Main::vis->process();
}

void Main::hwThread(){
  Behaviour* behave = new Behaviour();
  mot->action("zero");
  for(;;){
    Main::time->eventStart("hardware", "behaviour-update");
    behave->update();
    Main::time->eventEnd("hardware", "behaviour-update");
    Main::time->eventStart("hardware", "motion-update");
    mot->update();
    Main::time->eventEnd("hardware", "motion-update");
    Main::time->eventStart("hardware", "locate-update");
    loc->update();
    Main::time->eventEnd("hardware", "locate-update");
    Main::time->eventStart("hardware", "config-update");
    config->update();
    Main::time->eventEnd("hardware", "config-update");
    Main::time->loopTick("hardware");
  }
}

void Main::wwwThread(){
  if(*config->getInt("www.active").get() > 0){
    WebServer* www = new WebServer();
    www->run();
  }
}

void Main::gameThread(){
  int sleep = *config->getInt("game-controller.thread-sleep-ms").get();
  sleep *= 1000;
  while(gs->isRunning()){
    if(*config->getInt("game-controller.active").get() > 0){
      gs->service();
      if(!gs->isBusy()){
        usleep(sleep);
      }
    }else{
      usleep(sleep);
    }
  }
  gs->close();
}

void Main::teamThread(){
  int sleep = *config->getInt("mitecom.thread-sleep-ms").get();
  sleep *= 1000;
  while(ts->isRunning()){
    if(*config->getInt("mitecom.active").get() > 0){
      ts->service();
      if(!ts->isBusy()){
        usleep(sleep);
      }
    }else{
      usleep(sleep);
    }
  }
  ts->close();
}
