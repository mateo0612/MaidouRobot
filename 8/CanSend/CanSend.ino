#include <SPI.h>
#include <mcp2515_can.h>

const int spiCSPin = 10;
int ledHIGH    = 1;
int ledLOW     = 0;
int echoPin =7;
int trigPin =6;
long duration; 
int distance;


mcp2515_can  CAN(spiCSPin);

void setup()
{
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_500KBPS))
    {
        Serial.println("CAN BUS init Failed");
        delay(100);
    }
    Serial.println("CAN BUS Shield Init OK!");

    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 
  
}

unsigned char stmp[8] = {ledHIGH, 1, 2, 3, ledLOW, 5, 6, 7};
    
void loop()
{   
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; 
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  stmp[7] = distance;
  
  CAN.sendMsgBuf(0x55, 0, 8, stmp);
  delay(1000);
}
