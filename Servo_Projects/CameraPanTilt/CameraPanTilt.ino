/ * Source Vendramin by Federico 03/03/2011

http://selfelectro.altervista.org/index.php/arduino/62-camera-con-brandeggio-e-joystick.html
http://www.instructables.com/id/Pan-Tilt-camera-with-Arduino-and-Joystick/


https://www.zipfelmaus.com/arduino-pantilt-system/      NICE

www.zipfelmaus.com/wp-content/uploads/2010/10/pan_tilt_arduino_code_101010.zip
www.zipfelmaus.com/wp-content/uploads/2010/10/pan_tilt_schaeffeag_100704.zip
http://www.lynxmotion.com/p-287-lynx-b-pan-and-tilt-kit-black-anodized.aspx

Combining the 255 images to one video is easy, when you use the freeware tool Virtualdub – Link: www.virtualdub.org. It’s free and extremely easy.

http://www.virtualdub.org/

https://www.zipfelmaus.com/blog/hack-a-canon-camera-and-controll-it-with-an-arduino/


* /

#include                                     // include the library Servo.h required for this program

Servo Pan;                                    // Declare the two servants Pan and Tilt
Servo Tilt;
int   potP = 2;                               // pin reading potentiometers
int   potT = 3;
int   valP;                                   // variable for reading potentiometers
int   valT;
int   P = 90;                                 // Variable for writing position
int   T = 90;

void setup ()
{
  Pan.attach (9);                              // assign pin 9 and 10 as an output signal to control the servos
  Tilt.attach (10);
}

void loop ()                                   // Execute cycle times finally
{
 
  valP = analogRead(potP);                     // reads the value of POTP and assigns it to Valp. A value between 0 and 1023
  valT = analogRead(potT);

  valP = map(valP, 0, 1023, 0, 180);           // Update Valp with relative value scale between 0 and 180
  valT = map(valT, 0, 1023, 0, 180);           // The position of the servo varies between 0 and 180

 

  if ((valP > 95) & (P < 180)) P++;            // If it finds a positive shift increases P
  if ((valP 0)) P--;                           // Conversely, if the displacement and opposite decrease P
  Pan.write(P);                                // At this point communicates to the slave the new position to be reached

  if ((valT > 95) & (T < 180)) T++;            //same thing with T
  if ((valT 0)) T--;

  Tilt.write(T); 
  delay (10); // delay to allow the servo to reach the position
}
