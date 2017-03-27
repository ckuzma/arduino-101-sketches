#include "CurieIMU.h"

/* Global variable for deciding between double-tap and foostep detection */
bool doubleTap = true;

/* Global variables for double-tap timing */
bool inTap = false;
bool turnedOn = false;
int tapStart = 0;
int tapMax = 1000; // Maximum time between taps
int tapMin = 400; // Minimum time between taps

void setup() {
  /* USB serial debugging */
  Serial.begin(115200);
  
  /* Set up the LED strip */
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  
  
  /* Initialise the Curie IMU */
  CurieIMU.begin();
  CurieIMU.attachInterrupt(eventCallback);

  /* Shock detection parameters */
  if(doubleTap) {
    CurieIMU.setDetectionThreshold(CURIE_IMU_SHOCK, 1015);
    CurieIMU.setDetectionDuration(CURIE_IMU_SHOCK, 50);
    CurieIMU.interrupts(CURIE_IMU_SHOCK);
  }
  else {
    CurieIMU.setDetectionThreshold(CURIE_IMU_SHOCK, 1050); // 1.050g = 1050mg
    CurieIMU.setDetectionDuration(CURIE_IMU_SHOCK, 75);   // 75ms
  }
}

void loop() {
  // Code to clear out in-tap state
  if(inTap && millis() - tapStart > tapMax) {
    Serial.print("time out cancelled.\n");
    inTap = false;
  }
}

void lightsOn() {
  // Voltage level converter isn't working, so we set these to LOW/Ground
  // and wire the 5V LED strip's positive lead to the 5v pin on the 101
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}

void lightsOff() {
  // See comment in the lightsOn() function for info on why HIGH is off
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
}

static void eventCallback(void) {
  if (CurieIMU.getInterruptStatus(CURIE_IMU_SHOCK)) {
    if(doubleTap) {
      if(!inTap) {
        Serial.print("1st tap...");
        inTap = true;
        tapStart = millis();
      }
      if(inTap && millis() - tapStart >= tapMin) {
        Serial.print("and 2nd!\n");
        if(!turnedOn) {
          Serial.println("Lights on.");
          lightsOn();
          turnedOn = true;
          inTap = false;
        }
        else {
          Serial.println("Lights off.");
          lightsOff();
          turnedOn = false;
          inTap = false;
        }
      }
      else {
        Serial.print("-too fast-");
      }
    }
    else {
      lightsOn();
      delay(100);
      lightsOff();
    }
  }
}

