#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>      

#define POT_PIN A0
#define LED_PIN 12

int val;
char buttonState;

struct can_frame buttonMsg;
struct can_frame servoMsg;

 
MCP2515 mcp2515(10);

void setup()
{ 
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);                //Begins Serial Communication at 9600 baudrate
  SPI.begin();

  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS, MCP_8MHZ); //Sets CAN at speed 125KBPS and Clock 8MHz
  mcp2515.setNormalMode();
  }

void loop()
{

if (mcp2515.readMessage(&buttonMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)
  {
    buttonState = buttonMsg.data[0];
    digitalWrite(LED_PIN, buttonState);
  }

  val = analogRead(POT_PIN);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);      // scale it to use it with the servo (value between 0 and 180)
  
  servoMsg.can_id  = 0x037;           //CAN id as 0x037
  servoMsg.can_dlc = 8;               //CAN data length as 8
  servoMsg.data[0] = val;
  servoMsg.data[1] = 0x00;            //Update temperature value in [1]
  servoMsg.data[2] = 0x00;            
  servoMsg.data[3] = 0x00;
  servoMsg.data[4] = 0x00;
  servoMsg.data[5] = 0x00;
  servoMsg.data[6] = 0x00;
  servoMsg.data[7] = 0x00;
 
  mcp2515.sendMessage(&servoMsg);     //Sends the CAN message
  delay(100);                           
}
