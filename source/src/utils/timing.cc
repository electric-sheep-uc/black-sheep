#include "timing.hh"

Timing::Timing(){
  window = *Main::config->getInt("timing.window").get();
  timing = new Config();
  timing->setObject("start", std::to_string(CLOCK::CURRENT_TIME_MILLIS()));
}

Timing::~Timing(){
  /* Do nothing */
}

void Timing::eventStart(std::string loop, std::string event){
  long long start = CLOCK::CURRENT_TIME_MILLIS();
  timing->setObject(loop + "." + event + "." + "start", std::to_string(start));
}

void Timing::eventEnd(std::string loop, std::string event){
  long long end = CLOCK::CURRENT_TIME_MILLIS();
  long long start = end;
  start = *timing->getLong(loop + "." + event + "." + "start").get();
  long long diff = end - start;
  long long avg = diff;
  avg = *timing->getLong(loop + "." + event + "." + "avg").get();
  avg = ((avg * (window - 1)) + diff) / window;
  timing->setObject(loop + "." + event + "." + "end", std::to_string(end));
  timing->setObject(loop + "." + event + "." + "diff", std::to_string(diff));
  timing->setObject(loop + "." + event + "." + "avg", std::to_string(avg));
}

void Timing::loopTick(std::string loop){
  window = *Main::config->getInt("timing.window").get();
  long long end = CLOCK::CURRENT_TIME_MILLIS();
  long long start = end;
  start = *timing->getLong(loop + "." + "_end").get();
  long long diff = end - start;
  long long avg = diff;
  avg = *timing->getLong(loop + "." + "_avg").get();
  avg = ((avg * (window - 1)) + diff) / window;
  timing->setObject(loop + "." + "_start", std::to_string(start));
  timing->setObject(loop + "." + "_end", std::to_string(end));
  timing->setObject(loop + "." + "_diff", std::to_string(diff));
  timing->setObject(loop + "." + "_avg", std::to_string(avg));
}

std::string Timing::getData(){
  return timing->getDump();
}
