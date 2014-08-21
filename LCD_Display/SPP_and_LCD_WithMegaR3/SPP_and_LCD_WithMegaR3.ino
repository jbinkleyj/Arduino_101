/*
 Example sketch for the RFCOMM/SPP Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or 
 send me an e-mail:  kristianl@tkjelectronics.com
 */
//#define BOARD_MEGA_ADK
#include <SPP.h>
USB Usb;
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
//SPP SerialBT(&Btd); // This will set the name to the defaults: "Arduino" and the pin to "1234"
#ifdef BOARD_MEGA_ADK  
  SPP SerialBT(&Btd, "MegaADK","1234"); // You can also set the name and pin like so
  String usb_name = "MegaADK";
#else
 // SPP SerialBT(&Btd, "Mega","1234"); // You can also set the name and pin like so
 SPP SerialBT(&Btd, "Mega","1234"); // You can also set the name and pin like so
  String usb_name = "Mega";
#endif 
boolean firstMessage = true;
int dotCount = 0;
int loopCount = 0;
int status = 0;
//SPP SerialBT;
//BTD Btd;
void setup() {
  Serial.begin(115200);
  Serial.print(F("\r\nArduino_101-SPP_and_LCD_WithMegaR3 Delaying for 2 seconds... USB Name:"));
  Serial.print(usb_name);
  delay(2000);
//  Serial.print(F("\r\nBTD....."));
// Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
//Serial.print(F("\r\nBTD done, delaying for 2 seconds"));
//  delay(2000);
//  Serial.print(F("\r\nSerialBT....."));
//SPP SerialBT(&Btd); // This will set the name to the defaults: "Arduino" and the pin to "1234"
//SPP SerialBT(&Btd, "Lauszus's Arduino","0000"); // You can also set the name and pin like so
//Serial.print(F("\r\nBack from SerialBT, delaying for 2 seconds...."));
//   delay(2000);
 // Serial.print(F("\r\nBTD....."));
  Serial.print(F("\r\nStarting...."));
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start, delaying 2 seconds and retrying..."));
    delay( 2000 );
    Serial.print(F("\r\nUsb.Init()"));
    status = Usb.Init();
    Serial.print(status);
    Serial.print(F("\r\n"));
  //  while(1); //halt
  } else {
    Serial.print(F("\r\nSPP Bluetooth Library Started\r\n"));
  }
}
char c;
void PrintHex8(uint8_t *data, uint8_t length) // prints 8-bit data in hex with leading zeroes
{
        Serial.print("0x"); 
        for (int i=0; i<length; i++) { 
          if (data[i]<0x10) {Serial.print("0");} 
          Serial.print(data[i],HEX); 
          Serial.print(" "); 
        }
}

void PrintHex16(uint16_t *data, uint8_t length) // prints 16-bit data in hex with leading zeroes
{
        Serial.print("0x"); 
        for (int i=0; i<length; i++)
        { 
          uint8_t MSB=byte(data[i]>>8);
          uint8_t LSB=byte(data[i]);
          
          if (MSB<0x10) {Serial.print("0");} Serial.print(MSB,HEX); Serial.print(" "); 
          if (LSB<0x10) {Serial.print("0");} Serial.print(LSB,HEX); Serial.print(" "); 
        }
}
void loop() {
  
  Usb.Task();
   //int c = SerialBT.connected;
   //Serial.print(c);
   //Serial.print(SerialBT.available());
  if(SerialBT.connected) {
    
    if(firstMessage) {
      firstMessage = false;
      Serial.print(F("\r\nArduino Connected............................\r\n"));
      SerialBT.print(F("\r\nHello from Arduino\r\n")); // Send welcome message
    }
    if(Serial.available()) {
      SerialBT.print(Serial.read());
      
    } //else {
      //Serial.print(F("\r\nSerial not available 1\r\n"));
    //}
    if(SerialBT.available()){
      c = SerialBT.read();
     // Serial.write(c);
     // Serial.print("\r\n");
     //if (&c != "\r" && &c != "\n" ) {
     if (c != (char)0x13 && c != (char)0x10 ) {
       //Serial.print("0x"); 
       Serial.print(c); 
       //Serial.print("\n");
     } else {
        Serial.print("\r\n");
     } 
    // Serial.print("Val:  "); PrintHex8(c,1); Serial.print("\n"); 
    } //else {
      //Serial.print(F("\r\nSerial not available 2\r\n"));
    //}      
  } else {
    loopCount++;
    
    
    if (loopCount%100 ==0 ) { 
      Serial.print(F("."));
      dotCount++;
      Serial.print(F("."));
      if ( dotCount > 50 ) { 
        Serial.print(F("\r\n")); 
        dotCount = 0;
      } 
    }
    firstMessage = true;
  }
  delay(50);
}
