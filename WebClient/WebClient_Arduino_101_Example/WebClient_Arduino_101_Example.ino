/*
  Web client
 
 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 18 Dec 2009
 modified 9 Apr 2012
 by David A. Mellis
 
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//IPAddress server(173,194,33,104); // Google
IPAddress server(192,168,1,91); 
// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;


boolean firstTime = true;
boolean connectStatus = false;

boolean connetTo () {

  unsigned long t = millis();
  Serial.print("2 second tick: millis()=");
  Serial.println(t);
  
  
   if (client.connect(server, 80)) {

    // Make a HTTP request:
    
    Serial.println("\r\n sendgin GET /search?q=arduino HTTP/1.0--");
    client.print("GET /search?q=arduino HTTP/1.0--");
    client.println(t);
    client.println();
    return true;
  }   else {
    // kf you didn't get a connection to the server:
    Serial.println("\r\nconnection failed");
    return false;
  }
  
}

void setup() {
//  boolean firstTime = true;
  
 // Open serial communications and wait for port to open:
//  Serial.begin(9600);
  Serial.begin(115200);
  Serial.print("\r\nArduino_101-WebClient_Arduino_101_Example Delaying for 2 seconds... ");
  delay(2000);
  //   while (!Serial) {
  //  ; // wait for serial port to connect. Needed for Leonardo only
  //}

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.print("\r\nconnecting to:");
  Serial.println(server);
 // connectStatus = connetTo();
  
  // if you get a connection, report back via serial:

}


void getPage () {
    while (client.available()) {

     if (firstTime) {
      Serial.println("\r\nconnected to ");
      Serial.println(server);
     // Serial.println("\r\nclient.available.");
      firstTime = false;
    }
    // 
    char c = client.read();
   // Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.print("\r\ndisconnecting.");
    client.stop();

    // do nothing forevermore:
  //  for(;;)
  //    ;
  }
}
void loop()
{
    
  // if there are incoming bytes available 
  // from the server, read them and print them:
  delay(2000);
  connectStatus = connetTo();  
  if (connectStatus) {
    Serial.print("\r\nGot Results.");
    delay(2000);
    getPage ();
    
    
  } else {
    Serial.print("\r\nconnectStatus is false.");
  }
  client.stop();
}

