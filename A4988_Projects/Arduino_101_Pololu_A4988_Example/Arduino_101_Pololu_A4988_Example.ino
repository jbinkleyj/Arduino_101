//http://arduino.cc/forum/index.php?topic=122547.0





void setup() { 
  pinMode(9, OUTPUT);       // Motor Dir
  pinMode(10, OUTPUT);     // Motor Step
  pinMode(11, OUTPUT);     // Motor On - Off
  digitalWrite(11, LOW);     // Motor Off = LOW
}

void loop() {
  Pololu_A4988_Example();
}

void Pololu_A4988_Example(){
         
  digitalWrite(11, HIGH);   // Motor On
  delay(500);                   // delay for Controller startup
  digitalWrite(9, LOW);     // Turn right
   
  for(double i = 0; i < 100000; i++) {     //100000 steps in one direction
    digitalWrite(10, HIGH);
    delay(1);
    digitalWrite(10, LOW);
    delay(1);
  }
  digitalWrite(11, LOW);    // Motor Off
 
  delay(5000);
   
  digitalWrite(11, HIGH);    // Motor On
  delay(500);                    // delay for Controller startup
  digitalWrite(9, HIGH);     // Turn left

  for(double i = 0; i < 100000; i++) {   //100000 steps in one direction
    digitalWrite(10, HIGH);
    delay(1);
    digitalWrite(10, LOW);
    delay(1);
  }
  digitalWrite(11, LOW);    // Motor Off
 
  delay(5000);
} 
