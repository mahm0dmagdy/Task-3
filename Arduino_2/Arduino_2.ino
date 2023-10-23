#include <SoftwareSerial.h>
#define POT_PIN A0
#define LED_PIN 12

int val;
char buttonState;

SoftwareSerial UART(2, 3); // RX, TX

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  UART.begin(9600);
}

void loop()
{

  if (UART.available()) {
    buttonState = UART.read();

    if (buttonState == '1' ) {
      digitalWrite(LED_PIN, HIGH);
    }
    else if (buttonState == '0' )
    {
      digitalWrite(LED_PIN, LOW);
    }

  }
  val = analogRead(POT_PIN);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);      // scale it to use it with the servo (value between 0 and 180)
  UART.write(val);
  delay(100);                            // waits for the servo to get there

}
