#include "CurieIMU.h"
int ax, ay, az;         // accelerometer values
int gx, gy, gz;         // gyrometer values

void setup(){
  Serial.begin(9600); // initialize Serial communication
  CurieIMU.begin();
  delay(5000); // Allow the user to set everything down
  CurieIMU.autoCalibrateGyroOffset();
  CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 0);
}

String jsonEncodeValue(String key, float keyVal){
  return "\"" + key + "\":" + String(keyVal) + "";
}

String assembleJson(String keysAndVals){
  return "{" + keysAndVals + "}";
}

void loop(){
  // read raw accel/gyro measurements from device
  CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz);

  // display JSON formatted accel/gyro x/y/z values
  String keyVals = jsonEncodeValue("ax", ax) + ",";
  keyVals += jsonEncodeValue("ay", ay) + ",";
  keyVals += jsonEncodeValue("az", az) + ",";
  keyVals += jsonEncodeValue("gx", gx) + ",";
  keyVals += jsonEncodeValue("gy", gy) + ",";
  keyVals += jsonEncodeValue("gz", gz);
  if(Serial){
    Serial.println(assembleJson(keyVals));
  }
  delay(100);
}
