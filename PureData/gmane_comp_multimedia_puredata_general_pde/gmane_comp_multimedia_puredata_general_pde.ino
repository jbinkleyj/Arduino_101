// top //

#include <Wire.h>
#include <Servo.h>
#include <SimpleMessageSystem.h>


int sensorPin = 0;
int sensorValue = 0;
Servo servo1;


#define sensorAddress 0x70
#define readInches 0x50
#define readCentimeters 0x51
#define readMicroseconds 0x52
#define resultRegister 0x02


void setup()

{
  Wire.begin();
  Serial.begin(115200);
  Serial.println("#gmane_comp_multimedia_puredata_general_pde.pde....  Delaying for 2 seconds... ");
  delay(2000);  
}



void sendCommand (int address, int command) {
  Wire.beginTransmission(address);
  Wire.send(0x00);
  Wire.send(command);
  Wire.endTransmission();
}



void setRegister(int address, int thisRegister) {
  Wire.beginTransmission(address);
  Wire.send(thisRegister);
  Wire.endTransmission();
}

int readData(int address, int numBytes) {

  int result = 0;

  Wire.requestFrom(address, numBytes);

  while (Wire.available() < 2 );
  {

  }

  result = Wire.receive() * 256;
  result = result + Wire.receive();
  return result;
}


void loop()

{

  // SRF02 READING //
  sendCommand(sensorAddress, readInches);
  delay(70);

  setRegister(sensorAddress, resultRegister);
  int sensorReading = readData(sensorAddress, 2);

  Serial.println(sensorReading);
  delay (200);



  // GPD12 READING //

  sensorValue = analogRead(sensorPin);
  int range = (6787 / sensorValue);
  Serial.println(range);

  delay(200);

}


// bottom //

