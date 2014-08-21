//example use of LCD4Bit_mod library

#include "LCD4Bit_mod.h"
//create object to control an LCD.  
//number of lines in display=1

LCD4Bit_mod lcd = LCD4Bit_mod(2);


//Key message

#define MAX_BUFFER_SIZE 50
String info[2] = {
  "#Arduino_101 UNO_R3_LCD4Bit_modExample", "# Delaying for 2 seconds... "};

char charBuf[MAX_BUFFER_SIZE];

char line[MAX_BUFFER_SIZE];
int NUM_KEYS = 5;


String readLine(String line, byte size) {

  byte length = 0;
  char c;
  int inputStringLength;
  if (Serial.available()) {
    line=Serial.readStringUntil('\n');
    inputStringLength = line.length();
    Serial.print("#inputStringLength:");
    Serial.print(inputStringLength);
    Serial.print(":msg(");
    Serial.print(line);
    Serial.println(")");    
  }
  return line;
}

byte printStringOnLCD(LCD4Bit_mod lcd , String line) {
  Serial.println("#printStringOnLCD starting..");
  byte length = line.length();
  int i = 0;
  if (length > 0 ) {
    char charBuf[MAX_BUFFER_SIZE];
    line.toCharArray(charBuf, MAX_BUFFER_SIZE) ;

    for (i = 0; i < length; i++) {
      lcd.print(charBuf[i]);
    }
  //  Serial.print("#printStringOnLCD:Wrote to LCD:");
  //  Serial.println(line);
  } 
  else {
    Serial.println("#printStringOnLCD length less than one...");
  }
  return length;
}


boolean started=false;

void setup() {
  Serial.begin(115200);
  Serial.println(info[0]);

  Serial.println(info[1]);

  pinMode(13, OUTPUT); //we'll use the debug LED to output a heartbeat
  lcd.init();

  lcd.clear();
  // lcd.printIn(info);
  printStringOnLCD(lcd, info[0]); 

  printStringOnLCD(lcd, info[1]); 

  lcd.clear();
  lcd.printIn("KEYPAD + Serial:");
  started=true;
  Serial.println("#Setup is done...");
  Serial.println("OK");
}



int loopCount = 0;
int c = 0;

void loop() {

  loopCount++;
  //  Serial.println("OK");
  if (!(loopCount % 10000 )) {
    Serial.print("#loop count:");
    Serial.println(loopCount);
  }
  byte length;
  byte error;
  uint16_t time = millis();
  String lineBuffer;

  lineBuffer = readLine(lineBuffer, MAX_BUFFER_SIZE);
    lcd.cursorTo(1, 0); //line=2, x=0
    lcd.printIn("Serial Input:     "); 
  if ( lineBuffer.length() > 0) {
    // length = writeLine(line, MAX_BUFFER_SIZE);
   // lcd.clear();

    lcd.cursorTo(2, 0); //line=2, x=0
    printStringOnLCD(lcd, lineBuffer+"   "); 
    Serial.print("#Processed:");
    Serial.println(lineBuffer );
   // Serial.println("\n" );
    delay(50);
    Serial.println("OK");

  }  


}











