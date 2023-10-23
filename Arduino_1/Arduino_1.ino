#include <SoftwareSerial.h>
#include <Servo.h>
#define SERVO_PIN 9
#define BUSH_BUTTON 5

Servo myservo;  // create servo object to control a servo

int val;    // variable to read the value from the analog pin
int buttonState;
SoftwareSerial UART(2, 3); // RX, TX

void setup() {
  pinMode(BUSH_BUTTON, INPUT_PULLUP);
  myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
  UART.begin(9600);
}

void loop() {

  buttonState = digitalRead(BUSH_BUTTON);
  delay(1);
  if (buttonState == HIGH) {
    UART.write('1');
  }
  else if (buttonState == LOW) {
    UART.write('0');
  }

  if (UART.available()) {
    val = UART.read();
    myservo.write(val);
    delay(100);

  }
}
