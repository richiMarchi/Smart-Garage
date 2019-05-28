#include "ParkingAssistanceTask.h"
#include "Pir.h"
#include "LedExt.h"
#include "MsgService.h"

ParkingAssistanceTask::ParkingAssistanceTask(SharedContext *pContext, ProximitySensor *sensor, LightExt *light1, LightExt* light2, Button* touch) {
  this->light1 = light1;
  this->light2 = light2;
  this->sensor = sensor;
  this->pContext = pContext;
  this-> touch = touch;
  this->currDist = 0;
  this->previousDist = 0;
}

void ParkingAssistanceTask::init(int period) {
  Task::init(period);
  light1->switchOff();
  light2->switchOff();
  currentIntensityLED1 = 0;
  currentIntensityLED2 = 0;
  state = WAIT_FOR_CAR;
}

void ParkingAssistanceTask::setCarStopped() {
  carStopped = true;
}
void ParkingAssistanceTask::tick() {
  switch(state) {
    case WAIT_FOR_CAR:
        if(pContext->isCarAssistanceOn()) {
          state = CAR_MOVING;
        }
        break;
     case CAR_MOVING:
        currDist = sensor->getDistance();
        if(currDist >= 4){
          currDist = previousDist;
        }
        previousDist = currDist;
        MsgService.sendMsg("Distance: " + String(currDist));
        if (currDist >= DIST_CLOSE && currDist <= DIST_MAX) {
          if (!light1->isOn()) {
            light1->switchOn();
          }
          if (light2->isOn()){
            light2->switchOff();
            }
          currentIntensityLED1 = map((currDist*100), DIST_MAX*100/2, DIST_MAX * 100, 255, 1);
          light1->setIntensity(currentIntensityLED1);
        }
        else if(currDist > DIST_MIN && currDist < DIST_CLOSE){
          if (!light1->isOn()) {
            light1->switchOn();
          }
          if (!light2->isOn()) {
            light2->switchOn();
          }
          currentIntensityLED1 = 255;
          light1->setIntensity(currentIntensityLED1);
          currentIntensityLED2 = map((currDist*100), DIST_MIN*100, DIST_MAX*100/2 - 1, 255, 1);
          light2->setIntensity(currentIntensityLED2);
          }
        else if (currDist > DIST_MAX) {
          if (light1->isOn()) {
            light1->switchOff();
          }
          if (light2->isOn()){
            light2->switchOff();
            }
        }
        else if(currDist<=DIST_MIN){
          MsgService.sendMsg("OK CAN STOP");
          currentIntensityLED1 = 255;
          light1->setIntensity(currentIntensityLED1);
          currentIntensityLED2 = 255;
          light2->setIntensity(currentIntensityLED2);
          } 
        if(touch->isPressed() && currDist < DIST_MIN){
          MsgService.sendMsg("TOUCHING");
          }
        if(carStopped && pContext->isDistanceOK()){
          state = STOP;
          }
        else if(carStopped && !pContext->isDistanceOK()){
          carStopped = false;
          MsgService.sendMsg("TOO FAR");
          }
          break;
     case STOP:
        if (light1->isOn()) {
            light1->switchOff();
        }
        if (light2->isOn()) {
            light2->switchOff();
         }
        if(pContext->isDoorClosed()){
          pContext->setCarAssistance(false);
          carStopped = false;
          MsgService.sendMsg("OK");
          state = WAIT_FOR_CAR;
        }
        else if(pContext->isDistanceOK() && !pContext->isDoorClosed()){
            pContext->setCarAssistance(false);
            MsgService.sendMsg("OK");
            pContext->setDoorClosed(true);
            carStopped = false;
            state = WAIT_FOR_CAR;
        }
        break;
  }
}

