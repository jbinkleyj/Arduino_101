/*

CompassReading


http://jeffsinventions.com/?p=922
http://jeffsinventions.com/?p=577

http://www.movable-type.co.uk/scripts/latlong.html


From movable-types:
Formula: 	θ = atan2( sin(Δλ).cos(φ2), cos(φ1).sin(φ2) − sin(φ1).cos(φ2).cos(Δλ) )
JavaScript: 	

var y = Math.sin(dLon) * Math.cos(lat2);
var x = Math.cos(lat1)*Math.sin(lat2) -
        Math.sin(lat1)*Math.cos(lat2)*Math.cos(dLon);
var brng = Math.atan2(y, x).toDeg();

Excel: 	=ATAN2(COS(lat1)*SIN(lat2)-SIN(lat1)*COS(lat2)*COS(lon2-lon1),
       SIN(lon2-lon1)*COS(lat2))
*note that Excel reverses the arguments 




*/
/*
Adapted from the following code:

Compass reading
https://github.com/pololu/LSM303

*/

#include <Wire.h>
#include <LSM303.h>

LSM303 compass;

void setup() {
    Serial.begin(115200);
  Serial.println("#Arduino_101 LSM303 CompassReading....  Delaying for 0.2 seconds...");
  Wire.begin();
  compass.init();
  compass.enableDefault();
  
  // Calibration values. Use the Calibrate example program to get the values for
  // your compass.
  compass.m_min.x = -539; compass.m_min.y = -629; compass.m_min.z = -630;
  compass.m_max.x = +543; compass.m_max.y = +436; compass.m_max.z = 916;
}

void loop() {
  compass.read();
  int heading = compass.heading((LSM303::vector){0,-1,0});
  Serial.print("Heading:  ");
  Serial.print(heading);
  Serial.println(" degrees");
  delay(100);
}

