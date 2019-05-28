#ifndef __PARKINGASSISTANCETASK__
#define __PARKINGASSISTANCETASK__

#include "Task.h"
#include "SharedContext.h"
#include "ProximitySensor.h"
#include "LightExt.h"
#include "Button.h"
#include "config.h"

class ParkingAssistanceTask: public Task {

public:

  ParkingAssistanceTask(SharedContext* pContext, ProximitySensor* sensor, LightExt* light1, LightExt* light2, Button* touch);
  void init(int period);  
  void tick();
  void setCarStopped();

private:
  ProximitySensor* sensor;
  LightExt* light1;
  LightExt* light2;
  SharedContext* pContext;
  Button* touch;
  volatile bool carStopped = false;
  int currentIntensityLED1 = 0;
  int currentIntensityLED2 = 0;
  float currDist = 0;
  float previousDist;
  enum {WAIT_FOR_CAR, CAR_MOVING,STOP, TOO_FAR} state;
};
#endif
