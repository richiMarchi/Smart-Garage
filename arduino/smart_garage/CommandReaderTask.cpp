#include "CommandReaderTask.h"


CommandReaderTask::CommandReaderTask(SharedContext *pContext, GarageDoorTask* garage, ParkingAssistanceTask* park) {
  this->pContext = pContext;
  this->garage = garage;
  this->park = park;
}

void CommandReaderTask::init(int period) {
  Task::init(period);
}

void CommandReaderTask::tick() {
  if (MsgService.isMsgAvailable()) {
    //digitalWrite(10,HIGH);
    Msg* msg = MsgService.receiveMsg();
    
    if(msg->getContent() == "a"){
      //digitalWrite(10,HIGH);
      garage->openDoor();
      }
    if (msg->getContent() == "s") {
      park->setCarStopped();
    }
  }
}

