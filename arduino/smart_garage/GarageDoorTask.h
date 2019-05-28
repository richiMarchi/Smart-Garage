#ifndef __GARAGEDOORTASK__
#define __GARAGEDOORTASK__

#include "Task.h"
#include "SharedContext.h"
#include "PresenceSensor.h"
#include "LightExt.h"
#include "Button.h"

class GarageDoorTask: public Task {

public:

  GarageDoorTask(SharedContext* pContext, PresenceSensor* sensor, LightExt* light, Button* forceClose);
  void init(int period);  
  void tick();
  void openDoor();

private:
  PresenceSensor* detector;
  LightExt* light;
  SharedContext* pContext;
  volatile bool cmdOpen = false;
  int count = 0;
  int currentIntensity = 0;
  Button* forceClose;
  enum { WAIT_FOR_OPEN, OPENING_DOOR, DOOR_OPEN, CAR_IN, CLOSING_DOOR} state;
};

#endif
