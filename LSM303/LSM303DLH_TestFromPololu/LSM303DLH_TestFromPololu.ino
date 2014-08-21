      // works!! with $GPGGA sentences directly connected to
    // Skylab gps, but not if "LSM303 Compass" entry is added jaf 1/16/12

   // #include <nmea.h>
    #include <SoftwareSerial.h>
   // #include <LiquidCrystal.h>
    #include <Wire.h>
    #include <LSM303.h>

    SoftwareSerial gpsin(2, 3);

   // NMEA gps(ALL);    // GPS data connection to all sentence types

    // select the pins used on the LCD panel
    //LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

    LSM303 compass; //this single entry kills output 1/16/12 jaf

    void setup() {
      Wire.begin();
      gpsin.begin(9600);
     // lcd.begin(16,2);
    //  lcd.setCursor(0,0);
    //  lcd.print(F("GPS & HEADING"));
    print("GPS & HEADING");
      delay(5000);

    }

    String boola;
    String _latdeg;
    String _latmin;
    String _londeg;
    String _lonmin;

    void loop() {
      if (gpsin.available() > 0 ) {
        // read incoming character from GPS and feed it to NMEA type object
        if (gps.decode(gpsin.read())) {
          // full sentence received
          if (strncmp(gps.sentence(),"$GPGGA", 6) == 0) {
          boola=(gps.sentence());
          _latdeg = (boola.substring(18,20));
          _latmin = (boola.substring(20,27));
          _londeg = (boola.substring(31,33));
          _lonmin = (boola.substring(33,40));
          lcd.clear();
          lcd.setCursor (0,0);
          lcd.print (F("Lat: "));
          lcd.print (_latdeg);
          lcd.print (F(" "));
          lcd.print (_latmin);
          lcd.setCursor (0,1);
          lcd.print (F("Lon: "));
          lcd.print (_londeg);
          lcd.print (F(" "));
          lcd.print (_lonmin);   
          }
        }
      }
    }  
