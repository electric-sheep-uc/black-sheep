#include "scheduler.hh"

#include "../log.hh"

Scheduler::Scheduler(){
  numMotors = *Main::config->getInt("motor.num-motors").get();
  pose = (int*)malloc(numMotors * sizeof(int));
  /* TODO: Auto-find motions on start-up. */
  motions.push_back(new Config("scripts/zero.json", false));
  motions.push_back(new Config("scripts/stand.json", false));
  motions.push_back(new Config("scripts/left-right-walk.json", false));
  motions.push_back(new Config("scripts/right-left-walk.json", false));
  motions.push_back(new Config("scripts/get-up-from-back.json", false));
  motions.push_back(new Config("scripts/get-up-from-front.json", false));
}

Scheduler::~Scheduler(){
  free(pose);
}

int* Scheduler::getPose(Motor** motors){
  /* Get a snapshot of the current time and task */
  long long nowClock = CLOCK::CURRENT_TIME_MILLIS();
  /* Service the task list */
  service(nowClock);
  /* Make sure there is something to process */
  if(tasks.size() <= 0){
    return NULL;
  }
  Scheduler::Task task = tasks[0];
  long long now = nowClock - task.start;
  /* Calculate where in the script we are */
  int phaseTimeOffset = 0;
  int phaseDuration = 0;
  int phase = 0;
  int numPhases = task.script->getLength("phase");
  for(int x = 0; x < numPhases; x++){
    phase = x;
    phaseDuration = *task.script->getInt("phase." + std::to_string(phase) + ".duration").get();
    /* Keep searching until we find a phase we are greater than */
    if(now < phaseTimeOffset + phaseDuration){
      break;
    }else{
      phaseTimeOffset += phaseDuration;
    }
  }
  /* Calculate where the motor should be */
  now -= phaseTimeOffset;
  /* Iterate over the motors */
  for(int x = 0; x < numMotors; x++){
    double aPrev = motors[x]->getCurrentPosition(false);
    long long prev = motors[x]->getCurrentPositionTimestamp() - task.start - phaseTimeOffset;
    /* Make sure calculation is not divide by zero */
    if(phaseDuration == prev){
      ++phaseDuration;
    }
    double aEnd = RAW2RAD(*task.script->getInt("phase." + std::to_string(phase) + ".values." + motors[x]->getMotorName()).get());
    double aNow = ((aEnd - aPrev) * ((double)(now - prev) / (phaseDuration - prev))) + aPrev;
    motors[x]->setCurrentPosition(aNow, nowClock, false);
    motors[x]->setTargetPosition(aNow, false);
    pose[x] = RAD2RAW(motors[x]->getTargetPosition(true));
  }
  return pose;
}

void Scheduler::pushBack(std::string taskName){
  Scheduler::Task t;
  /* NOTE: Add time just encase this is the first task. */
  t.start = CLOCK::CURRENT_TIME_MILLIS();
  /* Add the correct motion file */
  for(unsigned int x = 0; x < motions.size(); x++){
    if(motions[x]->getString("name") == taskName){
      t.script = motions[x];
      /* Stop searching on first match */
      break;
    }
  }
  tasks.push_back(t);
  LOGM("Added new task to stack -> ", taskName.c_str());
}

void Scheduler::clear(){
  /* Remove all but the currently running task */
  while(tasks.size() > 1){
    tasks.pop_back();
  }
}

std::string Scheduler::getCurrentTask(){
  if(tasks.size() > 0){
    return tasks[0].script->getString("name");
  }else{
    return "none";
  }
}

void Scheduler::service(long long relTime){
  /* Make sure there is something to service */
  if(tasks.size() <= 0){
    return;
  }
  Scheduler::Task task = tasks[0];
  long long now = relTime - task.start;
  /* Calculate where in the script we are */
  int totalDuration = 0;
  int numPhases = task.script->getLength("phase");
  for(int x = 0; x < numPhases; x++){
    totalDuration += *task.script->getInt("phase." + std::to_string(x) + ".duration").get();
  }
  if(now >= totalDuration){
    LOGM("Dequeuing task from stack -> ", task.script->getString("name").c_str());
    tasks.erase(tasks.begin());
    /* Set the start time on the next task */
    if(tasks.size() > 0){
      tasks[0].start = CLOCK::CURRENT_TIME_MILLIS();
    }
  }
}
