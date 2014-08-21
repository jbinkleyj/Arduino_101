// remote-control servos through serial port
// responds to commands pSSSmPPPg where SSS is index to servoPins array, PPP is position to move to
// e.g. p1m135g moves servo 1 to position 135
// You can type these commands in the serial terminal to test, or send them from another program.

// returns pSSSmPPPOK on serial, just for debugging really

// Based on http://www.arduino.cc/playground/Learning/SingleServoExample

#include <Servo.h>

// the number of servos in use
//#define SERVO_COUNT 10
#define SERVO_COUNT 1
// the Arduino digital pins the servos are attached to
//const byte servoPins[SERVO_COUNT] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4};
const byte servoPins[SERVO_COUNT] = {13};
Servo servos[SERVO_COUNT];

void setup() {
  for (int i=0; i<SERVO_COUNT; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(90); // arbitrary start position
  }

  Serial.begin(115200);
  Serial.println("Ready");

}

#define STATE_NONE 0
#define STATE_PINNUMBER 1
#define STATE_POSITION 2

static int pinNumber = 0;
static int position = 0;
static int readState = STATE_NONE;


void loop() {

  if ( Serial.available()) {
    char ch = Serial.read();

    switch(ch) {
      Serial.print("ch:");Serial.println(ch);
      case '0'...'9':
        switch(readState) {
          case STATE_NONE:
            break;
          case STATE_PINNUMBER:
            pinNumber = pinNumber * 10 + (ch -'0');
            break;
          case STATE_POSITION:
            position = position * 10 + (ch -'0');
            break;
        }
        break;
      case 'g': 
        Serial.print("g:Position:");Serial.println(position);
        servos[pinNumber].write(position);
        pinNumber = 0;
        position = 0;
        readState = STATE_NONE;
        Serial.print("p");
        Serial.print(pinNumber);
        Serial.print("m");
        Serial.print(position, DEC);
        Serial.print("OK");
        break;
      case 'p':
        
        readState = STATE_PINNUMBER;
        Serial.print("p:STATE_PINNUMBER:");Serial.println(readState );
        break;
      case 'm':
      
        readState = STATE_POSITION;
        Serial.print("m:STATE_PINNUMBER:");Serial.println(readState );
        break;
    }
  }
} 



