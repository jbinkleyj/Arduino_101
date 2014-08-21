    // -http://forum.pololu.com/viewtopic.php?f=15&t=4592
    /*
    
---------------------------------------------------------------------------------------    
Bendage,
Now that mine works, I feel more qualified to speak to your problem. My GUESS 
is that your A4988 is overheating and stopping until it cools, then restarting. This 
would cause it to drop out sometimes and not other times. That pattern overlays 
on your forward and backward motion to act in the way that you see.

Another indication is your 1.7A - without a heatsink the A4988 can't 
continue to do that much current. The validity of your measurement 
depends upon your method of measuring, so I suspect 1.7A is LOW. The 
fix: turn the pot counterclockwise until the motor doesn't turn at all, 
then back just until it turns smoothly again.

 
---------------------------------------------------------------------------------------
Hi, cfinney.
The answer to your question depends on your stepper motor. You do not want 
to go above the rated current for your motor. Also, you cannot exceed 
about 1A per coil with the A4988 unless you cool it. If power is not a 
concern, you probably want to maximize your current given these two 
constraints. Otherwise, you will have to experiment to find the 
ideal current for your application.   


---------------------------------------------------------------------------------------
Postby jed » Wed Apr 11, 2012 10:27 am
The ideal current is the least that gets the job done, up to the maximum 
that your motor can take OR the maximum heat you can tolerate being 
generated. It depends upon your stepper, your power supply, the speed 
of your steps, and the torque your pump needs. Torque goes down as the 
current goes down, or as the number of steps/second go up.

For example, from looking at the spec sheet for your motor you see it is 
rated for a 1A current. That is a maximum and the motor will get quite 
hot if you go there. That is also near the limit of the A4988, depending 
upon cooling. There will probably be a chart that shows torque vs speed with 
different lines for different currents. This will give you a feel for the 
relationships for your stepper.

Test it and see if 1/2A is enough to turn your pump. Turn down the current 
more until you find it doesn't move your pump. You won't hurt the motor 
by "stalling" it this way. Now turn up the current until the motor runs 
smoothly and quietly. Remember, you can only read the current with a meter 
when it isn't stepping. If you need the full 1A continuously, you probably 
will have a heat problem.

Don't forget to disable the stepper when you don't need to move 
it (unless you need holding torque). This will limit the power used and
heat generated. A stepper will consume all the power you give it just to 
hold itself in place, if you let it or if you want it to hold.

jed
     
 
---------------------------------------------------------------------------------------
http://forum.pololu.com/viewtopic.php?f=15&t=4453
Ardiuno UNO and a4983 with regulator and stepper motor

---------------------------------------------------------------------------------------
http://forum.pololu.com/viewtopic.php?f=15&t=3428
A4983 and A4988 Getting Started Guide

---------------------------------------------------------------------------------------    
    */
    
    
    #define stepPin 2
    #define dirPin 3
    #define enablePin 4

    void setup()
    {
      pinMode(enablePin, OUTPUT);
      digitalWrite(enablePin, HIGH);
     
      Serial.begin(9600);
      Serial.println("Starting stepper exerciser.");
      pinMode(stepPin, OUTPUT);
      pinMode(dirPin, OUTPUT);
    }
    void loop()
    {
      int j;
      digitalWrite(enablePin, LOW);
      delayMicroseconds(2);
      digitalWrite(dirPin, HIGH);
     
      for(j=0; j<=200; j++)
      {
        digitalWrite(stepPin, LOW);
        delayMicroseconds(2);
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000);
      }
     
      digitalWrite(enablePin, LOW);
      delayMicroseconds(2);
      digitalWrite(dirPin, LOW);
     
      for(j=0; j<=200; j++)
      {
        digitalWrite(stepPin, LOW);
        delayMicroseconds(2);
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000);
      }
    }

