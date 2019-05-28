#ifndef __SHAREDCONTEXT__
#define __SHAREDCONTEXT__

#include "ProximitySensor.h"

class SharedContext {
public:
  SharedContext(ProximitySensor *proxSens);
  bool isDoorClosed();
  void setDoorClosed(bool value);
  bool isDistanceOK();
  void setCarAssistance(bool value);
  bool isCarAssistanceOn();
  
private:
  bool closed = true;
  ProximitySensor* proxSens;
  volatile bool carAssistance = false;
 };

#endif
