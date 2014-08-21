/*
//http://www.instructables.com/id/Arduino-Controlled-Motion-Sensor/

 Arduino Controlled Passive Infrared Motion Sensor
 
 LemonSlice7 - Instructables.com
 
 */

int calibrationTime = 30;        

boolean sensorActive = false;
boolean previousSensorState = false;

int pirPin = 4;    //the digital pin connected to the PIR sensor's output
int ledPin = 5;


// setup phase
void setup(){
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  //give the sensor some time to calibrate
  Serial.println("Sensor Calibration in Progress");
  Serial.println("------------------------------");
  for(int i = 0; i < calibrationTime; i++){
    Serial.print(".");
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
  }
  Serial.println("");
  Serial.println("Sensor Calibration Completed");
  Serial.println("Sensor Reading Active");
  delay(50);
  sensorActive = false;
  previousSensorState = false;
}

// loop sequence
void loop()
{
  // takes the pin value and saves it to the sensorActive boolean value
  if(digitalRead(pirPin) == HIGH)
  {
    sensorActive = true;
    digitalWrite(ledPin, HIGH);
  }
  if(digitalRead(pirPin) == LOW)
  {
    sensorActive = false;
    digitalWrite(ledPin, LOW);
  }
  
  // performs action if the state of the sensor changes
  // since this is a loop, here is now it works:
  // if the sensor pin goes HIGH (on) after it being LOW (off), the sensorActive value changes from the previousSensorState value.
  // it then turns on the LED. when the pin goes LOW (off) it will do the same thing but opposite values.
  // it also prints status to serial. it will print the time of triggering by providing the number of seconds that have passed since the program started.
  if(sensorActive != previousSensorState)
  {
    if(sensorActive == true)
    {
      previousSensorState = sensorActive;
      Serial.println("---");
      Serial.print("Motion Detected At: ");
      Serial.print(millis()/1000);
      Serial.println(" Seconds"); 
      delay(50);
    }
    if(sensorActive == false)
    {
      previousSensorState = sensorActive;
      Serial.println("---");
      Serial.print("Motion Stopped At: ");
      Serial.print(millis()/1000);
      Serial.println(" Seconds"); 
      delay(50);
    }
  }
}



