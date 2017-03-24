#include "CurieIMU.h"

void setup() {
  /* Set up the built-in LED */
//  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  
  
  /* Initialise the IMU */
  CurieIMU.begin();
  CurieIMU.attachInterrupt(eventCallback);

  /* Enable Shock Detection */
//  CurieIMU.setDetectionThreshold(CURIE_IMU_SHOCK, 1050); // 1.050g = 1050mg
  CurieIMU.setDetectionThreshold(CURIE_IMU_SHOCK, 1005); // 1003, 1004, 1007, 1005
//  CurieIMU.setDetectionDuration(CURIE_IMU_SHOCK, 75);   // 75ms
  CurieIMU.setDetectionDuration(CURIE_IMU_SHOCK, 1); // 50, 200, 2000, 200000, 1
  CurieIMU.interrupts(CURIE_IMU_SHOCK);
}

void loop() {
  // We don't need to put anything in the main loop...
}

static void eventCallback(void) {
  if (CurieIMU.getInterruptStatus(CURIE_IMU_SHOCK)) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    delay(50);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }
}

