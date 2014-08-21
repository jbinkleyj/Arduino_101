/*

 http://allaboutee.com/2011/11/17/how-to-control-anything-with-your-android-phone-from-the-internet/
 
 
  how-to-control-anything
  
  HowTo_Control_Anything
 */

int ledPin=13;
int state=0;
int data=0;

void setup()
{
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,state);
  Serial.begin(115200);
  Serial.println("\r\nArduino_101 SingleServoExampleV2.pde....  Delaying for 2 seconds... ");
}

void loop()
{
  
  if(Serial.available()>0)
  {
    Serial.println(data);
    state=!state;
    data=Serial.read();
    switch(data)
    {
    case 177:
      digitalWrite(ledPin,state);
      break;
    }
  }
}

