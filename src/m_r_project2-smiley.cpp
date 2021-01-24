/*
 * PIR sensor tester
 */
#include <Arduino.h>
#include <Servo.h>

Servo servo;

int ledPin = 2;                 // choose the pin for the LED
int inputPin = 4;               // D2 - choose the input pin (for PIR sensor)
int servoPin = 5;               // D5
int pirState = LOW;             // we start, assuming no motion detected
int val      = 0;               // variable for reading the pin status
 
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  servo.attach(servoPin); 
  servo.write(0);
  delay(1000);

  Serial.begin(9600);
}
 
void loop(){
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
        digitalWrite(ledPin, LOW);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
    /*  Serial.println("Motion detected!");
      servo.write(0);
      delay(1000);
      servo.write(90);
      delay(1000);
      servo.write(45);
      delay(1000); */

      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, HIGH); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
