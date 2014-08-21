

/*

http://forum.pololu.com/viewtopic.php?f=15&t=3428
A4983 and A4988 Getting Started Guide


*UPDATE* - I have created a board to make the learning process even easier. See here:
http://forum.pololu.com/viewtopic.php?f=15&t=4592

Attachments

    PololuPres_V3.pdf
        Step by step instructions on how to test and calibrate your motor driver. Version 3.
        (737.59 KiB) Downloaded 2328 times

    PoluluPres.pdf
        Step by step instructions on how to test and calibrate your motor driver.
        (734.02 KiB) Downloaded 1260 times

    StepperTester.pdf
        Stepper driver code to exercise the driver.
        (17.03 KiB) Downloaded 1630 times


http://forum.pololu.com/download/file.php?id=720&sid=488e0ce6c41815e2e9e3be9ff59dde15
http://forum.pololu.com/download/file.php?id=491&sid=488e0ce6c41815e2e9e3be9ff59dde15
http://forum.pololu.com/download/file.php?id=487&sid=488e0ce6c41815e2e9e3be9ff59dde15


http://forum.pololu.com/viewtopic.php?f=15&t=4627
A4988 Unresponsive Board


http://forum.pololu.com/viewtopic.php?f=15&t=4592
A4988 Dev Board


*/

#define stepPin 2
#define dirPin 3
#define enablePin 4
void setup()
{
  // We set the enable pin to be an output
  pinMode(enablePin, OUTPUT);
  // then we set it HIGH s

  digitalWrite(enablePin, HIGH);
  Serial.begin(9600);
  Serial.println("Starting stepper exerciser.");
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}
void loop()
{
  int j;
  // set the enablePin low so that we can now use our stepper driver.
  digitalWrite(enablePin, LOW);
  // wait a few microseconds for the enable to take effect
  // (That isn't in the spec sheet I just added it for sanity.)
  delayMicroseconds(2);
  // we set the direction pin in an arbitrary direction.
  digitalWrite(dirPin, HIGH);
  for(j=0; j<=10000; j++) {
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
  }
}



