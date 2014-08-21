//http://forum.pololu.com/viewtopic.php?f=15&t=4592
//A4988 Dev Board

/*

 
 
 
 
 Then use one of these commands:
 ChangeDirection
 EnableStepper
 DisableStepper
 stepPinM1gOn
 stepPinM1gOff
 FullStep
 HalfStep
 QuarterStep
 EighthStep
 SixteenthStep
 
 
 I am uploading a new Arduino sketch which allows you to also control the stepPinM1g speed of the motor through the terminal for quick turnaround.
 Now you can do:
 stepPinM1gOff
 EighthStep
 StepsInHz=1500
 stepPinM1gOn
 
 And quickly see what your motor can handle.
 
 I am also uploading the Eagle files and the BOM.
 
 I am still selling the board for those who are interested.
 
 Attachments
 
 DevBoardBom.csv
 Bill Of Materials
 (1.42 KiB) Downloaded 115 times
 
 PololuStepperDriverDevBoardRev1.zip
 Eagle Files
 (40.52 KiB) Downloaded 208 times
 
 StepperDriverDevBoardShellRev2.zip
 New Arduino Sketch
 (2.09 KiB) Downloaded 211 times
 
 http://forum.pololu.com/download/file.php?id=838
 http://forum.pololu.com/download/file.php?id=837
 http://forum.pololu.com/download/file.php?id=836
 
 
 */
#include "LCD4Bit_mod.h" 
//create object to control an LCD.  
//number of lines in display=1
LCD4Bit_mod lcd = LCD4Bit_mod(2); 

char msgs[5][15] = {
  "Right Key OK ", 
  "Up Key OK    ", 
  "Down Key OK  ", 
  "Left Key OK  ", 
  "Select Key OK" };
int  adc_key_val[5] ={
  30, 150, 360, 535, 760 };
int NUM_KEYS = 5;
int adc_key_in;
int key=-1;
int oldkey=-1;




#define stepPinM1 3 
#define dirPinM1 2 
#define stepPinM1 3 
#define dirPinM1 2 
#define enablePinM1 7
#define MicroStep1Pin 6
#define MicroStep2Pin 5
#define MicroStep3Pin 4


#define LEDPin 13



#define numMsInOneSec 1000
#define numMicroSecInOneMs 1000
#define stepPulseWidthInMicroSec 2
#define setupTimeInMicroSec 1
//#define timeBetweenStepsInMicroSec (1 * numMicroSecInOneMs)

#define inputBufferSize 128
String hzStartString = "StepsInHz=";
int  serialCharIn;             
char serialInString_old[inputBufferSize];  
String serialInString;  
//int  serialInIndex  = 0;

unsigned long timeBetweenInputPollsInMicroSec = ( (unsigned long)(numMsInOneSec /4) * numMicroSecInOneMs ); // 250 = 1/4th of a second
unsigned long timeBetweenStepsInMicroSec = (1 * numMicroSecInOneMs);

unsigned long loopCheck = 0;

boolean lineReady = false;
boolean successfullyParsed = false;
boolean currentDirection = false;
boolean shouldStep = true;

boolean speedChanged = true;

void setCurrentDirection(boolean dir)
{
  Serial.println("setCurrentDirection starting...:");
  if(dir == false)
  {
    digitalWrite(dirPinM1, LOW);
  } 
  else {
    digitalWrite(dirPinM1, HIGH);
  }
  currentDirection = dir;
  delayMicroseconds(setupTimeInMicroSec);
}

void changeDirection()
{
  Serial.println("changeDirection starting...:");
  setCurrentDirection(!currentDirection);
}

void enableStepper(int isEnabled)
{
  Serial.print("enableStepper starting...:");
  Serial.println(isEnabled);
  if(isEnabled)
  {
    digitalWrite(enablePinM1, LOW); // enable HIGH = stepper driver OFF
  } 
  else {
    digitalWrite(enablePinM1, HIGH); // enable HIGH = stepper driver OFF
  }
  // wait a few microseconds for the enable to take effect 
  // (That isn't in the spec sheet I just added it for sanity.) 
  delayMicroseconds(2);
}

void takeSingleStep()
{
  // Serial.println("takeSingleStep starting...:");
  digitalWrite(stepPinM1, LOW);
  delayMicroseconds(stepPulseWidthInMicroSec); 
  digitalWrite(stepPinM1, HIGH); 
  delayMicroseconds(stepPulseWidthInMicroSec); 
  digitalWrite(stepPinM1, LOW);
}

void setFullStep()
{
  Serial.println("setFullStep  starting...:");
  digitalWrite(MicroStep1Pin, LOW);
  digitalWrite(MicroStep2Pin, LOW);
  digitalWrite(MicroStep3Pin, LOW);
  delayMicroseconds(setupTimeInMicroSec);
}

void setHalfStep()
{
  Serial.println("setHalfStep  starting...:");
  digitalWrite(MicroStep1Pin, HIGH);
  digitalWrite(MicroStep2Pin, LOW);
  digitalWrite(MicroStep3Pin, LOW);
  delayMicroseconds(setupTimeInMicroSec);
}

void setQuarterStep()
{
  Serial.println("setQuarterStep  starting...:");
  digitalWrite(MicroStep1Pin, LOW);
  digitalWrite(MicroStep2Pin, HIGH);
  digitalWrite(MicroStep3Pin, LOW);
  delayMicroseconds(setupTimeInMicroSec);  
}

void setEighthStep()
{
  Serial.println("setEighthStep  starting...:");
  digitalWrite(MicroStep1Pin, HIGH);
  digitalWrite(MicroStep2Pin, HIGH);
  digitalWrite(MicroStep3Pin, LOW);
  delayMicroseconds(setupTimeInMicroSec);  
}

void setSixteenthStep()
{
  Serial.println("setSixteenthStep  starting...:");
  digitalWrite(MicroStep1Pin, HIGH);
  digitalWrite(MicroStep2Pin, HIGH);
  digitalWrite(MicroStep3Pin, HIGH);
  delayMicroseconds(setupTimeInMicroSec);  
}


/*
void readSerialString_old () 
 {
 //Serial.println("readSerialString  starting...:");
 int serialCharacter;   
 if(Serial.available()) 
 { 
 while (Serial.available())
 { 
 serialCharacter = Serial.read();
 Serial.print("readSerialString  serialCharacter :");
 Serial.println(serialCharacter );
 if(serialInIndex == inputBufferSize-1)
 {
 serialInString_old[serialInIndex] = '\0';
 // we just keep setting the last character in our buffer and just loose characters
 } else {          
 serialInString_old[serialInIndex] = serialCharacter;
 serialInIndex++;
 Serial.print("Read so far:");
 Serial.println(serialInString_old);
 }
 
 if ((serialCharacter == '\n') || (serialCharacter == '\r'))
 {
 Serial.println("EOL found");
 lineReady = true;
 }
 }
 }
 }  
 */

void readSerialString  () {
  if(Serial.available())  { 

    serialInString = Serial.readStringUntil('\n');
    lineReady = true;
  }
}


void serialResponseString() {
  Serial.println("serialResponseString  starting...:");
  if( lineReady )
  {
    //if(successfullyParsed == true)
    //{
    //  Serial.print("String successfully parsed: ");
    //} else {
    //  Serial.print("String unsuccessfully parsed: ");
    //}
    Serial.print("serialResponseString text:(");
    Serial.print(serialInString);     
    //serialInIndex = 0;
    lineReady = false;
    Serial.println(")");
  }
}

bool makeChangesBasedOnSerial()
{
  boolean output = true;

  Serial.println("");
  Serial.print("makeChangesBasedOnSerial  starting...:");

  String tempString = serialInString;
  Serial.print("tempString:");
  Serial.println(tempString);

  if(tempString == "ChangeDirection")
  {
    changeDirection();
  } 
  else if (tempString.startsWith("EnableStepper")) {
    enableStepper(true);
  } 
  else if (tempString.startsWith("DisableStepper")) {
    enableStepper(false);
  } 
  else if (tempString.startsWith("FullStep")) {
    setFullStep();
  } 
  else if (tempString.startsWith("HalfStep")) {
    setHalfStep();
  } 
  else if (tempString.startsWith("QuarterStep")) {
    setQuarterStep();
  } 
  else if (tempString.startsWith("EighthStep")) {
    setEighthStep();
  } 
  else if (tempString.startsWith("SixteenthStep")) {
    setSixteenthStep();
  } 
  else if (tempString.startsWith("stepPinM1gOn")) {
    shouldStep = true;
  } 
  else if (tempString.startsWith("stepPinM1gOff")) {
    shouldStep = false ; 
  }

  else if (tempString.startsWith("s")) {
    String stepsstr ="1" ;
    char stepsCharArray[inputBufferSize];
    int i = 0;
    long steps = 1;
    if ( tempString.length() > 1) {
      stepsstr = tempString.substring(1, tempString.length()  );
      stepsstr.toCharArray(stepsCharArray, inputBufferSize);
      steps = atol(stepsCharArray);
    }
    Serial.print("steps:");
    Serial.print(stepsstr); 

    for (i=0; i <  steps ; i++){  
      takeSingleStep();
      Serial.print("step:");Serial.println(i);
      delay (10);
    }
  }
  else if (tempString.startsWith( hzStartString )  ) { //&& tempString.endsWith("\n")
    // must be less than 1,000,000
    String hzstr = tempString.substring(hzStartString.length(), tempString.length()  );
    char hzCharArray[inputBufferSize];
    hzstr.toCharArray(hzCharArray, inputBufferSize);
    Serial.print("makeChangesBasedOnSerial hzstr:");
    Serial.print(hzstr);
    long parsed = atol(hzCharArray);
    Serial.print("makeChangesBasedOnSerial parsed:");
    Serial.println(parsed);

    if(parsed != 0 && parsed < (numMicroSecInOneMs*numMsInOneSec) )
    {
      timeBetweenStepsInMicroSec = ((unsigned long)numMicroSecInOneMs*numMsInOneSec) / (unsigned long) parsed;
      speedChanged = true;
      Serial.print("C");
    } 
    else {
      output = false;
    }
  } 
  else {
    Serial.print("makeChangesBasedOnSerial CommandNotFound:");
    Serial.println(tempString);
    output = false;
  }
  return output;
}


void setup() 
{
  Serial.begin(115200);
  Serial.print("StepperDriverDevBoardShellRev21 starting...:");
  //delay(2000);
  // We set the enable pin to be an output 
  pinMode(enablePinM1, OUTPUT); // then we set it HIGH so that the board is disabled until we 
  pinMode(stepPinM1, OUTPUT); 
  pinMode(dirPinM1, OUTPUT);

  pinMode(MicroStep1Pin, OUTPUT);
  pinMode(MicroStep2Pin, OUTPUT);
  pinMode(MicroStep3Pin, OUTPUT);



digitalWrite(13, HIGH);  



  // get into a known state. 
  enableStepper(false);
  // we set the direction pin in an arbitrary direction.
  setCurrentDirection(false);
  // setFullStep();
  setSixteenthStep();

  enableStepper(true);
  // we set the direction pin in an arbitrary direction. 
  setCurrentDirection(true);

  Serial.println("Then use one of these commands:");
  Serial.println("  - ChangeDirection");
  Serial.println("  - EnableStepper");
  Serial.println("  - DisableStepper");
  Serial.println("  - stepPinM1gOn");
  Serial.println("  - stepPinM1gOff");
  Serial.println("  - FullStep");
  Serial.println("  - HalfStep");
  Serial.println("  - QuarterStep");
  Serial.println("  - EighthStep");
  Serial.println("  - SixteenthStep  ");
  Serial.println(" ");
  Serial.println("Example, you can do: ");
  Serial.println("  - stepPinM1gOff ");
  Serial.println("  - EighthStep ");
  Serial.println("  - StepsInHz=1500 ");
  Serial.println("  - stepPinM1gOn   ");
}

long loopCount = 0;

void loop() 
{ 
  int j; 
  loopCount++;
  if (!(loopCount % 100000 )) {
    Serial.print("#loop count:");
    Serial.println(loopCount);
  }
  //Serial.println(".");
  readSerialString();
  if( lineReady )
  {
    // ensure string is null terminated    
    //  serialInString_old[serialInIndex] = '\0';
    //  serialInIndex++;

    successfullyParsed = makeChangesBasedOnSerial();
    serialResponseString();
  }
  /*
  if(shouldStep)
   {
   if(speedChanged)
   {
   loopCheck = (timeBetweenInputPollsInMicroSec/timeBetweenStepsInMicroSec);
   Serial.print("loopCheck:");
   Serial.println(loopCheck);
   speedChanged = false;
   }
   
   for(j=0; j<loopCheck; j++) 
   { 
   takeSingleStep();
   // delay(2000);
   // Serial.print("s");
   delayMicroseconds(timeBetweenStepsInMicroSec);
   }
   //Serial.println("s"); 
   }
   */
}





