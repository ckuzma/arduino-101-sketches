#include<Wire.h>

const int MPU_addr=0x68;  // I2C address for ITG-MTU
int ax, ay, az, temp, gx, gy, gz;

void setup(){
 Serial.begin(9600);
 Wire.begin();
 Wire.beginTransmission(MPU_addr);
 Wire.write(0x6B);
 Wire.write(0);
 Wire.endTransmission(true);
}

String jsonEncodeValue(String key, float keyVal){
 return "\"" + key + "\":" + String(keyVal) + "";
}

String assembleJson(String keysAndVals){
 return "{" + keysAndVals + "}";
}

void loop(){
 Wire.beginTransmission(MPU_addr);
 Wire.write(0x3B);
 Wire.endTransmission(false);
 Wire.requestFrom(MPU_addr, 14, true);
 ax = Wire.read()<<8|Wire.read();
 ay = Wire.read()<<8|Wire.read();
 az = Wire.read()<<8|Wire.read();
 temp = Wire.read()<<8|Wire.read();
 gx = Wire.read()<<8|Wire.read();
 gy = Wire.read()<<8|Wire.read();
 gz = Wire.read()<<8|Wire.read();
 // temp = temp/340.00+36.53; // Convert temp data to celsius - NOT BEING USED
 String keyVals = jsonEncodeValue("ax", ax) + ",";
 keyVals += jsonEncodeValue("ay", ay) + ",";
 keyVals += jsonEncodeValue("az", az) + ",";
 keyVals += jsonEncodeValue("gx", gx) + ",";
 keyVals += jsonEncodeValue("gy", gy) + ",";
 keyVals += jsonEncodeValue("gz", gz);
 Serial.println(assembleJson(keyVals));
 delay(100);
}
