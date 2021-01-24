/*
 * PIR sensor tester
 */
#include <Arduino.h>
#include <Servo.h>

Servo servo;

//int ledPin = 2;                 // choose the pin for the LED
int pirPin = 14;               // D5 (GPIO14) or D2 (GPIO4) - choose the input pin (for PIR sensor)
int servoPin = 5;               // D1 GPIO5
int pirState = LOW;             // we start, assuming no motion detected
int pirval   = 0;               // variable for reading the pin status
 
void setup() {
  //pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(pirPin, INPUT);     // declare sensor as input
  servo.attach(servoPin); 
  servo.write(90);
  delay(1000);
  servo.detach();

  Serial.begin(9600);
}
 
void loop(){
  pirval = digitalRead(pirPin);  // read input value
  if (pirval == HIGH) {            // check if the input is HIGH
   // digitalWrite(ledPin, LOW);  // turn LED ON
   if (pirState == LOW) {
     // just turned on
     Serial.println("Motion detected!");
     servo.attach(servoPin); 
     while (pirval == HIGH) {
       servo.write(0);
       delay(1000);
       servo.write(180);
       delay(1200);
       pirval = digitalRead(pirPin);
     }            

     pirState = HIGH;
   }
  } else {
   // digitalWrite(ledPin, HIGH); // turn LED OFF
    if (pirState == HIGH) {
      // we have just turned off
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      servo.write(90);
      delay(1000);
      servo.detach();
      pirState = LOW;
    }
  }
}
