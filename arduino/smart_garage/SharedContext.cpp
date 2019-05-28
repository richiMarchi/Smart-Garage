#include "SharedContext.h"
#include "config.h"

SharedContext::SharedContext(ProximitySensor *proxSens){
  this->closed = true;
  this->proxSens = proxSens;
  this->carAssistance = false;  
}

 bool SharedContext::isDoorClosed(){
   return this->closed;
  }
 void SharedContext::setDoorClosed(bool value){
   this->closed = value;
    }
  bool SharedContext::isDistanceOK(){
    return (this->proxSens->getDistance() <= DIST_CLOSE);
    }
  void SharedContext::setCarAssistance(bool value){
    this->carAssistance = value;
    }
  bool SharedContext::isCarAssistanceOn(){
    return this->carAssistance;
    }




