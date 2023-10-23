#include <SoftwareSerial.h>
#include <Servo.h>
#define SERVO_PIN 9
#define BUSH_BUTTON 5

Servo myservo;  // create servo object to control a servo

int val;    // variable to read the value from the analog pin
int buttonState;

struct can_frame buttonMsg;
struct can_frame servoMsg;

MCP2515 mcp2515(10);


void setup() {
  pinMode(BUSH_BUTTON, INPUT_PULLUP);
  myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
  
  Serial.begin(9600);
  SPI.begin(); 

  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS, MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();
}

void loop() {

if (mcp2515.readMessage(&servoMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)
  {
    val = servoMsg.data[0];
    myservo.write(val); 
  }

  buttonState = digitalRead(BUSH_BUTTON);
  delay(1);

  buttonMsg.can_id  = 0x036;           //CAN id as 0x036
  buttonMsg.can_dlc = 8;               //CAN data length as 8
  buttonMsg.data[0] = buttonState;
  buttonMsg.data[1] = 0x00;           
  buttonMsg.data[2] = 0x00;            
  buttonMsg.data[3] = 0x00;
  buttonMsg.data[4] = 0x00;
  buttonMsg.data[5] = 0x00;
  buttonMsg.data[6] = 0x00;
  buttonMsg.data[7] = 0x00;
 
  mcp2515.sendMessage(&buttonMsg);     //Sends the CAN message
  delay(100);
}
