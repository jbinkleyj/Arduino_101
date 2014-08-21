#include <Wire.h>
#include <LSM303.h>

LSM303 compass;

void setup() {
   
    Serial.begin(115200);
  Serial.println("#Arduino_101 LSM303 Examples Serial....  Delaying for 0.2 seconds...");
  Wire.begin();
  compass.init();
  compass.enableDefault();
}

void loop() {
  compass.read();

  Serial.print("A ");
  Serial.print("X: ");
  Serial.print((int)compass.a.x);
  Serial.print(" Y: ");
  Serial.print((int)compass.a.y);
  Serial.print(" Z: ");
  Serial.print((int)compass.a.z);

  Serial.print(" M ");  
  Serial.print("X: ");
  Serial.print((int)compass.m.x);
  Serial.print(" Y: ");
  Serial.print((int)compass.m.y);
  Serial.print(" Z: ");
  Serial.println((int)compass.m.z);
  
  delay(100);
}
