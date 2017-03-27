#include "CurieIMU.h"

/* --- Adjustable variables BELOW this line --- */
const int tapsToRemember  = 5; // Number of taps to store, which are averaged out
long delayTime            = 1000; // Initial setup delay for flashing, in milliseconds
int shockThreshold        = 1050; // (DEFAULT: 1050mg) Calibrate to installation
int shockDuration         = 200; // (DEFAULT: 200ms) Calibrate to installation
float oldBeatWeight       = 0.45; // Weight assigned to existing beat
float newBeatWeight       = 0.55; // Weight assigned to new beat
/* --- Adjustable variables ABOVE this line --- */

/* Below are variables used to measure time between taps */
bool inTap = false;
long tapStart;
long tapEnd;
long recentTaps[tapsToRemember];
int currentTap = 0;
int lightTimer = 0;

void setup(){
  /* Start serial for debugging */
  Serial.begin(9600);
  
  /* Set up the built-in LED */
  pinMode(LED_BUILTIN, OUTPUT);

  /* Fill the taps array */
  for (int x=0; x < tapsToRemember; x++){
    recentTaps[x] = delayTime;
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
  digitalWrite(LED_BUILTIN, LOW);
  if(lightTimer == 0) {
    lightTimer = millis();
  }
  if(millis() - lightTimer >= delayTime) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    lightTimer = 0;
  }
}

void calculateDelay(long newDelay){
  /* Add new delay measure to recent taps array */
  recentTaps[currentTap] = newDelay;

  /* Add all of the recent taps together */
  long tapAverage = 0;
  for (int x=0; x < tapsToRemember; x++){
    tapAverage += recentTaps[x];
  }

  /* Divide the recent taps to get their average */
  tapAverage = tapAverage / tapsToRemember;

  /* Give existing and new beats weights, add together */
  delayTime = (oldBeatWeight * delayTime) + (newBeatWeight * tapAverage);
  Serial.println("Delay is now: " + String(delayTime));

  /* Increment selector for adding next measurement to recent taps */
  currentTap++; // Increment the index selector
  if (currentTap == tapsToRemember){
    currentTap = 0;
  }
}

static void eventCallback(void){
  if (CurieIMU.getInterruptStatus(CURIE_IMU_SHOCK)) {
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

