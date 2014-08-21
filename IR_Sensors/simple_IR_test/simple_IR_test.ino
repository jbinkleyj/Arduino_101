#define IRPIN 4        // Pin to receive IR


void setup(){
   
 Serial.begin(115200);
   
}
 
 
void loop(){
  
  Serial.print("Digital Signal:");
  Serial.println(analogRead(IRPIN));
  delay(50);
   
}
