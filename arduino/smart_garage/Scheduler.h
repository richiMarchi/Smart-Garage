#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Timer.h"
#include "Task.h"
#include "Runnable.h"
#include "config.h"

class Scheduler: public Runnable {
  
  int basePeriod;
  int nTasks;
  Task* taskList[MAX_TASKS];  
  Timer* timer;

public:  
  void init(int basePeriod);  
  virtual bool addTask(Task* task);
  virtual void run();
private:
  void sleep();
};

#endif

