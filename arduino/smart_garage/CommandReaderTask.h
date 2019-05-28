#ifndef __COMMANDREADERTASK__
#define __COMMANDREADERTASK__

#include "ParkingAssistanceTask.h"
#include "Task.h"
#include "SharedContext.h"
#include "MsgService.h"
#include "GarageDoorTask.h"


class CommandReaderTask: public Task {

public:

  CommandReaderTask(SharedContext* pContext, GarageDoorTask* garage, ParkingAssistanceTask* park);
  void init(int period);  
  void tick();

private:
  SharedContext* pContext;
  GarageDoorTask* garage;
  ParkingAssistanceTask* park;
};



#endif
