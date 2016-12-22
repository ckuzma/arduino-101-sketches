#include "CurieIMU.h"

/* --- Adjust variables BELOW this line --- */
const int tapsToRemember  = 10; // Number of taps to store, which are averaged out
long delayTime            = 1000; // Initial setup delay for flashing, in milliseconds
int shockThreshold        = 1050; // (DEFAULT: 1050mg)
int shockDuration         = 125; // (DEFAULT: 125ms)
/* --- Adjust variables ABOVE this line --- */

/* These are used to measure taps */
bool inTap = false;
long tapStart;
long tapEnd;
long taps[tapsToRemember];
int currentTap = 0;

void setup(){
  /* Start serial for debugging */
  Serial.begin(9600);
  
  /* Set up the built-in LED */
  pinMode(LED_BUILTIN, OUTPUT);

  /* Fill the taps array */
  for (int x=0; x < tapsToRemember; x++){
    taps[x] = delayTime;
  }
  
  /* Initialise the IMU */
  CurieIMU.begin();
  CurieIMU.attachInterrupt(eventCallback);

  /* Enable Shock Detection */
  CurieIMU.setDetectionThreshold(CURIE_IMU_SHOCK, shockThreshold);
  CurieIMU.setDetectionDuration(CURIE_IMU_SHOCK, shockDuration);
  CurieIMU.interrupts(CURIE_IMU_SHOCK);
}

void loop(){
  blinker();
}

void blinker(){
  /* Flash */
  digitalWrite(LED_BUILTIN, HIGH);
  pause(50);
  digitalWrite(LED_BUILTIN, LOW);

  /* Delay/Pause */
  pause(delayTime);
}

void pause(long pauseTime){
  unsigned long pauseStart = millis();
  while (millis() < pauseStart + pauseTime);
}

void calculateDelay(long newDelay){
  taps[currentTap] = newDelay;
  long tapAverage = 0;
  for (int x=0; x < tapsToRemember; x++){
    tapAverage += taps[x];
  }
  delayTime = tapAverage / tapsToRemember;
  Serial.println("Delay is now: " + String(delayTime));
  currentTap++; // Increment the index selector
  if (currentTap == tapsToRemember){
    currentTap = 0;
  }
}

static void eventCallback(void){
  if (CurieIMU.getInterruptStatus(CURIE_IMU_SHOCK)) {
    /* Flash the LED */
    digitalWrite(LED_BUILTIN, HIGH);
    pause(50);
    digitalWrite(LED_BUILTIN, LOW);

    /* Measure the tap length */
    if (inTap == false){
      Serial.print("Tap start...");
      tapStart = millis();
      inTap = true;
    }
    else{
      
      tapEnd = millis();
      Serial.print(" and end. (" + String(tapEnd - tapStart) + ")\n");
      calculateDelay(tapEnd - tapStart);
      inTap = false;
    }
  }
}

