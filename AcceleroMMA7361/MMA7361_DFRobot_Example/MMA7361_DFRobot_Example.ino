//Arduino Sample Code
//Developed by Yuki from DFRobot.com
//Modified by Michael from DFRobot.com
//Last Modified 02/15/2012
//Version 1.0 or lower
/*
 *
 * http://www.dfrobot.com/wiki/index.php/Triple_Axis_Accelerometer_MMA7361_%28SKU:_DFR0143%29
 * http://itp.nyu.edu/physcomp/sensors/Reports/MMA7260Q
 * www.dfrobot.com/image/data/DFR0068/MMA7260QT.pdf
 * www.sparkfun.com/datasheets/Accelerometers/MMA7260Q-Rev1.pdf
 * http://www.dfrobot.com/wiki/index.php/Hardware-Mechanical
 * http://code.google.com/p/mma7361-library/
 */
 
void setup()
{
  Serial.begin(57600); 
}
int analog_x,analog_y,analog_z;
float vol_x,vol_y,vol_z;
float add_x,add_y,add_z;
float g_x,g_y,g_z;
float degree_x,degree_y,degree_z;
void loop()
{
 analog_x=analogRead(0);
 analog_y=analogRead(1);
  analog_z=analogRead(2);
  vol_x=analog_x*5.0/1024;//convert analog_x-->voltage value(v)
  vol_y=analog_y*5.0/1024;
  vol_z=analog_z*5.0/1024;
 //range x: 0.83 - 2.41    1.62
 //      y: 0.96 - 2.53    1.74
 //      z: 0.72 - 2.23    1.48
  add_x=vol_x-1.62;//calculate the added x axis voltage value
  add_y=vol_y-1.74;
  add_z=vol_z-1.48;
  g_x=add_x/0.8;//calculate the gram value
  g_y=add_y/0.8;
  g_z=add_z/0.8;
   
  if(g_x<=1&&g_x>=-1) //We use this condition to prevent the overflow of asin(x).( If x>1 or x<-1, asin(x)=0)
  {
  degree_x=asin(g_x)*180.0/PI;//calculate the degree value
  degree_y=asin(g_y)*180.0/PI;
  degree_z=asin(g_z)*180.0/PI;
  }
  //fix the overflow condition
  if(g_x>1) 
  degree_x=90;
    if(g_x<-1)
  degree_x=-90;
    if(g_y>1)
  degree_y=90;
    if(g_y<-1)
  degree_y=-90;
    if(g_z>1)
  degree_z=90;
    if(g_z<-1)
  degree_z=-90;
 //#########################
 //print
  Serial.print("x:");
  Serial.print(degree_x);
  Serial.print(" y:");
  Serial.print(degree_y);
  Serial.print(" z:");
  Serial.println(degree_z);
  delay(200);
   
}
