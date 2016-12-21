#include "CurieIMU.h"

/* The global delay time for taps */
long delayTime = 1000;

/* These are used to measure taps */
bool inTap = false;
long tapStart;
long tapEnd;

void setup(){
  /* Set up the built-in LED */
  pinMode(LED_BUILTIN, OUTPUT);
  
  /* Initialise the IMU */
  CurieIMU.begin();
  CurieIMU.attachInterrupt(eventCallback);

  /* Enable Shock Detection */
  CurieIMU.setDetectionThreshold(CURIE_IMU_SHOCK, 1050); // 1.050g = 1050mg
  CurieIMU.setDetectionDuration(CURIE_IMU_SHOCK, 75);   // 75ms
  CurieIMU.interrupts(CURIE_IMU_SHOCK);
}

void loop(){
  blinker();
}

void blinker(){
  /* Flash on */
  digitalWrite(LED_BUILTIN, HIGH);
  pause(delayTime);

  /* Flash off */
  digitalWrite(LED_BUILTIN, LOW);
  pause(delayTime);
}

void pause(long pauseTime){
  unsigned long pauseStart = millis();
  while (millis() < pauseStart + pauseTime);
}

static void eventCallback(void){
  if (CurieIMU.getInterruptStatus(CURIE_IMU_SHOCK)) {
    /* Flash the LED */
    digitalWrite(LED_BUILTIN, HIGH);
    pause(50);
    digitalWrite(LED_BUILTIN, LOW);

    /* Measure the tap length */
    if (inTap == false){
      tapStart = millis();
      inTap = true;
    }
    else{
      tapEnd = millis();
      delayTime = tapEnd - tapStart;
      inTap = false;
    }
  }
}

