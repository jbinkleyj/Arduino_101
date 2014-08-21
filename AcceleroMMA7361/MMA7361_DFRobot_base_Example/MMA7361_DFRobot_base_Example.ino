//Arduino Sample Code
//Developed by Yuki from DFRobot.com
//Last Modified 02/08/2012
//Version 1.0 or lower
 /*
 *
 * http://www.dfrobot.com/wiki/index.php/Triple_Axis_Accelerometer_MMA7361_%28SKU:_DFR0143%29
 * http://itp.nyu.edu/physcomp/sensors/Reports/MMA7260Q
 * www.dfrobot.com/image/data/DFR0068/MMA7260QT.pdf
 * www.sparkfun.com/datasheets/Accelerometers/MMA7260Q-Rev1.pdf
 *
 *
 */
 
 
void setup()
{
  Serial.begin(57600); 
}
int analog_x,analog_y,analog_z;
float vol_x,vol_y,vol_z;
 
void loop()
{
 analog_x=analogRead(0);
 analog_y=analogRead(1);
  analog_z=analogRead(2);
  vol_x=analog_x*5.0/1024;//convert analog_x-->voltage value(v)
  vol_y=analog_y*5.0/1024;
  vol_z=analog_z*5.0/1024;
    Serial.print("x:");
  Serial.print(vol_x);
  Serial.print(" y:");
  Serial.print(vol_y);
  Serial.print(" z:");
  Serial.println(vol_z);
  delay(200);
}
