    //
    //http://forum.pololu.com/viewtopic.php?p=25125#p25124
    #define enablePin 5
    #define stepPin 6
    #define dirPin 7
    const int buttonPin = 12;
    int buttonState; // variable for reading the pushbutton status
    int j;
    int i;

    void setup()
    {
      pinMode(enablePin, OUTPUT);
      digitalWrite(enablePin, HIGH);

      // initialize the pushbutton pin as an input:
      pinMode(buttonPin, INPUT);

      Serial.begin(9600);
      Serial.println("Starting Stepper Exerciser.");

      pinMode(stepPin, OUTPUT);
      pinMode(dirPin, OUTPUT);
      digitalWrite(dirPin, HIGH);
    }

    void loop()
    {
    buttonState = digitalRead(buttonPin);
         if (buttonState && i<=1)
        {
         delay(15);
         digitalWrite(enablePin, LOW);
         
         Serial.println("Button Pressed");
         digitalWrite(stepPin, LOW);
         delay(250);
         i=2;
         Serial.println("i ");
         Serial.println(i);
        } 
       else if (buttonState && i>1)
             {
              delay(15);
              digitalWrite(enablePin, LOW);
              Serial.println("Button Pressed Again");
              digitalWrite(stepPin, HIGH);
              delay(250);
              i=1;
              Serial.println("i2 ");
              Serial.println(i);
         
              Serial.println("j ");
              Serial.println(j);
              j++;
                 if (j > 4)
                  {j = 1;}
        }     
      }
