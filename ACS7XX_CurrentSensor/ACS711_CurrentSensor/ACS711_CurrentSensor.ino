//http://www.hacktronics.com/Tutorials/arduino-current-sensor.html

/*
http://www.lucadentella.it/en/2011/11/29/sensore-di-corrente-con-arduino/
http://www.lucadentella.it/en/2011/11/29/sensore-di-corrente-con-arduino/
http://arduino.cc/forum/index.php?action=printpage;topic=65954.0

https://forum.sparkfun.com/viewtopic.php?f=7&t=20587

http://openenergymonitor.org/emon/buildingblocks/ct-sensors-interface


http://arduino.cc/forum/index.php/topic,125952.0.html
http://openenergymonitor.org/emon/buildingblocks/arduino-sketch-current-only
http://www.instructables.com/id/Real-time-Web-Based-Household-Power-Usage-Monitor/
http://www.instructables.com/id/Web-Based-Water-Metering-with-ioBridge/

http://www.instructables.com/id/2-Carabiner-split-core-AC-transducer/

http://compendiumarcana.com/kaw/
http://www.efergy.us/
http://www.allegromicro.com/


https://github.com/adafruit
http://www.ladyada.net/make/tweetawatt/
http://code.google.com/p/tweetawatt/
http://www.adafruit.com/blog/category/tweetawatt/
http://www.ladyada.net/make/tweetawatt/graph.html
http://www.ladyada.net/make/tweetawatt/download.html
http://www.ladyada.net/media/wattcher/appengineauth.py

http://www.ladyada.net/make/tweetawatt/download.html
http://www.ladyada.net/media/wattcher/wattcher-maingraph.py
http://www.ladyada.net/media/wattcher/wattcher-5minreport.py
http://www.ladyada.net/media/wattcher/wattcher-wattgraph.py
http://www.ladyada.net/media/wattcher/wattcher-final.py
http://googleblog.blogspot.com/2011/06/update-on-google-health-and-google.html
http://www.ladyada.net/media/wattcher/xbee.py

https://developers.google.com/appengine/
https://developers.google.com/appengine/docs/python/gettingstarted/

http://en.wikipedia.org/wiki/Root_mean_square#Average_electrical_power
http://sourceforge.net/projects/pyserial/files/pyserial/2.4/
http://sourceforge.net/projects/pywin32/files/pywin32/Build%20200/
http://pypi.python.org/pypi/simplejson

http://hackedgadgets.com/2009/01/27/power-monitoring-using-a-hacked-kill-a-watt/

At this point, the code is getting waaay to big to paste here so grab "wattcher.py Mains graph" from the download page!




http://www.miloslick.com/Download.html

http://www.miloslick.com/EnergyLogger.html
http://www.google.com/powermeter/about/index.html
https://cosm.com/



https://www.sparkfun.com/products/11005?
http://dzlsevilgeniuslair.blogspot.it/2012/05/arduino-do-touche-dance.html
http://arduino.cc/blog/2011/10/10/speed-vest-for-night-cycling/

http://lekernel.net/blog/2011/09/interactive-visuals-workshop-with-milkymist-one-and-arduino/
http://www.thinkgeek.com/gadgets/travelpower/?icpg=gy_7acf
http://www.thinkgeek.com/product/7657/
http://www.amazon.com/P3-International-P4400-Electricity-Monitor/dp/B00009MDBU

*/

#include <LiquidCrystal.h>

/* This sketch describes how to connect a ACS715 Current Sense Carrier
(http://www.hacktronics.com/Sensors/Current-Sensor-30-to-30-Amp/flypage.tpl.html) to the Arduino,
and read current flowing through the sensor.

*/

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

/*

Vcc on carrier board to Arduino +5v
GND on carrier board to Arduino GND
OUT on carrier board to Arduino A0

Insert the power lugs into the loads positive lead circuit,
arrow on carrier board points to load, other lug connects to
power supply positive

Voltage Divider

11.66 from + to A4
4.62k from A4 to Gnd
Ratio 2.5238

*/
int batMonPin = A4;    // input pin for the voltage divider
int batVal = 0;       // variable for the A/D value
float pinVoltage = 0; // variable to hold the calculated voltage
float batteryVoltage = 0;

int analogInPin = A0;  // Analog input pin that the carrier board OUT is connected to
int sensorValue = 0;        // value read from the carrier board
int outputValue = 0;        // output in milliamps
unsigned long msec = 0;
float time = 0.0;
int sample = 0;
float totalCharge = 0.0;
float averageAmps = 0.0;
float ampSeconds = 0.0;
float ampHours = 0.0;
float wattHours = 0.0;
float amps = 0.0;

int R1 = 11660; // Resistance of R1 in ohms
int R2 = 4620; // Resistance of R2 in ohms

float ratio = 0;  // Calculated from R1 / R2

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  lcd.begin(20, 4);
}

void loop() {
 
int sampleBVal = 0;
int avgBVal = 0; 
int sampleAmpVal = 0;
int avgSAV = 0;
 
for (int x = 0; x < 10; x++){ // run through loop 10x

  // read the analog in value:
  sensorValue = analogRead(analogInPin);  
  sampleAmpVal = sampleAmpVal + sensorValue; // add samples together

  batVal = analogRead(batMonPin);    // read the voltage on the divider
  sampleBVal = sampleBVal + batVal; // add samples together
 
  delay (10); // let ADC settle before next sample
}

avgSAV = sampleAmpVal / 10;

  // convert to milli amps
  outputValue = (((long)avgSAV * 5000 / 1024) - 500 ) * 1000 / 133; 
 
/* sensor outputs about 100 at rest.
Analog read produces a value of 0-1023, equating to 0v to 5v.
"((long)sensorValue * 5000 / 1024)" is the voltage on the sensor's output in millivolts.
There's a 500mv offset to subtract.
The unit produces 133mv per amp of current, so
divide by 0.133 to convert mv to ma
         
*/

avgBVal = sampleBVal / 10; //divide by 10 (number of samples) to get a steady reading

  pinVoltage = avgBVal * 0.00610;       //  Calculate the voltage on the A/D pin
                                /*  A reading of 1 for the A/D = 0.0048mV
                                    if we multiply the A/D reading by 0.00488 then
                                    we get the voltage on the pin. 
                                  
                                    NOTE! .00488 is ideal. I had to adjust
                                    to .00610 to match fluke meter.
                                   
                                    Also, depending on wiring and
                                    where voltage is being read, under
                                    heavy loads voltage displayed can be
                                    well under voltage at supply. monitor
                                    at load or supply and decide.
*/

  ratio = (float)R1 / (float)R2;
  batteryVoltage = pinVoltage * ratio;    //  Use the ratio calculated for the voltage divider
                                          //  to calculate the battery voltage
                                         
                                           
  amps = (float) outputValue / 1000;
  float watts = amps * batteryVoltage;
   
  Serial.print("Volts = " );                      
  Serial.print(batteryVoltage);     
  Serial.print("\t Current (amps) = ");     
  Serial.print(amps); 
  Serial.print("\t Power (Watts) = ");  
  Serial.print(watts);  
 
   
  sample = sample + 1;
 
  msec = millis();
 
  time = (float) msec / 1000.0;
 
  totalCharge = totalCharge + amps;
 
  averageAmps = totalCharge / sample;

  ampSeconds = averageAmps*time;
 
  ampHours = ampSeconds/3600;
 
  wattHours = batteryVoltage * ampHours;
 
  Serial.print("\t Time (hours) = ");
  Serial.print(time/3600);
 
  Serial.print("\t Amp Hours (ah) = ");
  Serial.print(ampHours);
  Serial.print("\t Watt Hours (wh) = ");
  Serial.println(wattHours);
 
    lcd.setCursor(0,0);
    lcd.print(batteryVoltage);
    lcd.print(" V ");
    lcd.print(amps);
    lcd.print(" A ");
 
  lcd.setCursor(0,1);
  lcd.print(watts);
  lcd.print(" W ");
  lcd.print(time/3600);
  lcd.print(" H ");
 
  lcd.setCursor(0,2);
  lcd.print(ampHours);
  lcd.print(" Ah ");
  lcd.print(wattHours);
  lcd.print(" Wh ");
 
  lcd.setCursor(0,3);
  lcd.print(ratio, 5);
  lcd.print("   ");
  lcd.print(avgBVal);
 
  // wait 10 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(10);                    
 
  
}
