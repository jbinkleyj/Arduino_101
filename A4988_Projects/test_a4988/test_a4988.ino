///////////////////////////////////////////////////////////
// Stepper Motor skecth for use with the EasyDriver v4.2 //
///////////////////////////////////////////////////////////
// http://danthompsonsblog.blogspot.com/2010/05/easydriver-42-tutorial.html
// Dan Thompson 2010
//
// Use this code at your own risk.
//
// For all the product details visit http://www.schmalzhaus.com/EasyDriver/
// For the full tutorial visit http://danthompsonsblog.blogspot.com/


////// ED_v4  Step Mode Chart //////
//                                //
//   MS1 MS2 Resolution           //
//   L   L   Full step (2 phase)  //
//   H   L   Half step            //
//   L   H   Quarter step         //
//   H   H   Eighth step          //
//                                //
////////////////////////////////////

int DIR = 3;          // PIN  3 = DIR
int STEP = 2;        // PIN  2 = STEP
    #define enablePin 5
    #define stepPin 6
    #define dirPin 7
//int MS1 = 13;        // PIN 13 = MS
//int MS2 = 9;         // PIN  9 = MS2
//int SLEEP = 12;      // PIN 12 = SLP


void setup() {
   Serial.begin(115200);
  Serial.print("EasyDriver_From_DanThompson starting...:");
  delay(2000);
  
  pinMode(DIR, OUTPUT);   // set pin 3 to output
  pinMode(STEP, OUTPUT);  // set pin 2 to output
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH);
 
  digitalWrite(dirPin, HIGH);  
 // pinMode(MS1, OUTPUT);   // set pin 13 to output
 // pinMode(MS2, OUTPUT);   // set pin 9 to output
 // pinMode(SLEEP, OUTPUT); // set pin 12 to output
}



void loop()
{
 
 
     // digitalWrite(STEP, LOW);              // This LOW to HIGH change is what creates the..
      digitalWrite(STEP, HIGH);             // .."Rising Edge" so the easydriver knows to when to step.
     // delayMicroseconds(1600/modeType);     // This delay time determines the speed of the stepper motor. 
 
    delay(500);
  }
 



//



//


