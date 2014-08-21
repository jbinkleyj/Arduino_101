/*

http://www.dfrobot.com/index.php?route=product/product&product_id=383#.UIp7tYZlGXI

*/


#include <Wire.h>

#define DEVICE (0x53)    //ADXL345 device address
#define TO_READ (6)        //num of bytes we are going to read each time (two bytes for each axis)

byte buff[TO_READ] ;    //6 bytes buffer for saving data read from the device
char str[512];                      //string buffer to transform data before sending it to the serial port

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  //Serial.begin(57600);  // start serial for output
  Serial.begin(115200);
  Serial.print("\r\nDelaying for 2 seconds... ");
//Turning on the ADXL345
writeTo(DEVICE, 0x2D, 0);     
writeTo(DEVICE, 0x2D, 16);
writeTo(DEVICE, 0x2D, 8);
}

void loop()
{
//int regAddress = 0x32;    //first axis-acceleration-data register on the ADXL345
int regAddress = 0x53;
int x, y, z;

readFrom(DEVICE, regAddress, TO_READ, buff); //read the acceleration data from the ADXL345

  //each axis reading comes in 10 bit resolution, ie 2 bytes.  Least Significat Byte first!!
  //thus we are converting both bytes in to one int
x = (((int)buff[1]) << 8) | buff[0]; 
y = (((int)buff[3])<< 8) | buff[2];
z = (((int)buff[5]) << 8) | buff[4];

//we send the x y z values as a string to the serial port
sprintf(str, "\r\nx,y,x = %d %d %d", x, y, z); 
Serial.print(str);
//Serial.print(10, BYTE);

//It appears that delay is needed in order not to clog the port
delay(50);
}

//---------------- Functions
//Writes val to address register on device
void writeTo(int device, byte address, byte val) {
  Wire.beginTransmission(device); //start transmission to device
  //Wire.send(address);        // send register address
  //Wire.send(val);        // send value to write
	Wire.write(address);             // send register address
	Wire.write(val);    
  Wire.endTransmission(); //end transmission
}

//reads num bytes starting from address register on device in to buff array
void readFrom(int device, byte address, int num, byte buff[]) {
Wire.beginTransmission(device); //start transmission to device
//Wire.send(address);        //sends address to read from
	Wire.write(address);             // sends address to read from
Wire.endTransmission(); //end transmission

Wire.beginTransmission(device); //start transmission to device
Wire.requestFrom(device, num);    // request 6 bytes from device

int i = 0;
while(Wire.available())    //device may send less than requested (abnormal)
{
  //buff[i] = Wire.receive(); // receive a byte
  buff[i] = Wire.read();    // receive a byte
  i++;
}
Wire.endTransmission(); //end transmission
}
