#include "CurieIMU.h"

void setup() {
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

void loop() {
  // We don't need to put anything in the main loop...
}

static void eventCallback(void) {
  if (CurieIMU.getInterruptStatus(CURIE_IMU_SHOCK)) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
  }
}

