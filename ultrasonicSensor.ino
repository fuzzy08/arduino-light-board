#include <Timer.h>
#include <Event.h>

//#include <Time.h>
//#include <TimeLib.h>

    /*
    * This was based on Dejan  Nedelkovski's project and modified by Zachary Quinn:
    * 
    * 
    * 
    * Ultrasonic Sensor HC-SR04 and Arduino Tutorial
    *
    * Initial project made by Dejan Nedelkovski,
    * www.HowToMechatronics.com
    *
*/

    /*
    This is code for an arduino motion sensor that activates a common-cathode LED strip. 
    The program has been tuned for the sensor to activiate in a hallway when someone walks by. 
    The program will first lash red, green, and blue lights, then stay on for a few seconds.
    The cooldown variable is used to prevent constant triggering events.
    Future additions could include a counter, user-adjusted LED coloring, and a sound playing after it gets triggered.
    
    
    
    */
    // defines pins numbers
    const int runTime = 10;
    const int coolDown = 50; //50 is about 3 seconds with runTime of 20
    const int trigPin = 11;
    const int echoPin = 12;
    const int bluePin = 6;
    const int greenPin = 5;
    const int redPin = 9;
    int accumulator = 0;
    bool triggered = false;
    // defines variables
    long duration;
    int distance;
    int trigLen = 80;
   
    float mean;
    Timer t;
    void setup() {
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    pinMode(bluePin, OUTPUT); // sets the ledPin as Output
    Serial.begin(9600); // Starts the serial communication
   
    }
    void loop() {
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delay(runTime);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delay(runTime);
    digitalWrite(trigPin, LOW);
//    digitalWrite(ledPin, HIGH);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance



    
    distance= duration*0.034/2;
     

     if ((distance < trigLen) && (triggered == false))
    {
      triggered = true;
      accumulator = coolDown;
      flash(5);

      analogWrite(bluePin, 250);
      analogWrite(greenPin, 250);
      analogWrite(redPin, 250);
      
      
      
      Serial.println("triggered!!!!!!");
      
      
    } else if (accumulator > 0) {
      
      accumulator--;  
      
      Serial.print("cooldown\n");
    
    } else if ((distance < trigLen)) {
      accumulator = coolDown;
        
    } else {
      analogWrite(bluePin, 0);
      analogWrite(greenPin, 0);
      analogWrite(redPin, 0);
      Serial.println("accumulator cleared.");
      triggered = false;
//      accumulator--;
    }
    Serial.println(accumulator);
  
    Serial.print("Distance: ");
    Serial.println(distance);
    }


    void flash(int times) {
      for(int i = 0; i < times; i++) {
      analogWrite(bluePin, 150);
      analogWrite(greenPin, 0);
      analogWrite(redPin, 0);
      delay(150);
      analogWrite(bluePin, 0);
      analogWrite(greenPin, 150);
      analogWrite(redPin, 0);
      delay(150);
      analogWrite(bluePin, 0);
      analogWrite(greenPin, 0);
      analogWrite(redPin, 150);
      delay(150);
      }
    }

