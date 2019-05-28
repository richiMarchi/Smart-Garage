#include "Scheduler.h"
#include "ParkingAssistanceTask.h"
#include "GarageDoorTask.h"
#include "SharedContext.h"
#include "Sonar.h"
#include "Pir.h"
#include "MsgService.h"
#include "CommandReaderTask.h"
#include "LedExt.h"
#include "ButtonImpl.h"
#include "config.h"

#define CALIBRATION_TIME_SEC 10

Scheduler sched;

void setup(){
  
  sched.init(100);

  Sonar* sonar = new Sonar(SONAR_ECHO_PIN,SONAR_TRIG_PIN);
  LedExt* l1 = new LedExt(L1_PIN);
  Pir* pir = new Pir(PIR_PIN);
  LedExt* l2 = new LedExt(L2_PIN);
  LedExt* l3 = new LedExt(L3_PIN);
  Button* forceClose = new ButtonImpl(T1_PIN);
  Button* touch = new ButtonImpl(T2_PIN);

  SharedContext* pContext = new SharedContext(sonar);  
  
  MsgService.init();
 
  GarageDoorTask* garage = new GarageDoorTask(pContext,pir,l1, forceClose);
  garage->init(100);
  sched.addTask(garage);

  ParkingAssistanceTask* park = new ParkingAssistanceTask(pContext, sonar, l2, l3, touch);
  park->init(100);
  sched.addTask(park);

  CommandReaderTask* reader = new CommandReaderTask(pContext, garage, park);
  reader->init(100);
  sched.addTask(reader);
  
  for(int i = 0; i < CALIBRATION_TIME_SEC; i++){
    Serial.print(".");
    delay(1000);
  }
  
  delay(50);
}

void loop(){
  sched.run();
}
