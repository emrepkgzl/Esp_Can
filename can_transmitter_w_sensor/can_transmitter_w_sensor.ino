#define trigPin 4
#define echoPin 3//for hc-sr04

#include "stdio.h"
#include "stdint.h"

#include <SPI.h>          //Library for using SPI Communication 
#include <mcp2515.h>      //Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)

uint8_t byte_counter = 0;
uint8_t bit_counter = 0;
 
struct can_frame canMsg1;
 
MCP2515 mcp2515(10);

typedef union
{
  uint8_t byte;
  struct {
    uint8_t bit0 : 1;
    uint8_t bit1 : 1;
    uint8_t bit2 : 1;
    uint8_t bit3 : 1;
    uint8_t bit4 : 1;
    uint8_t bit5 : 1;
    uint8_t bit6 : 1;
    uint8_t bit7 : 1;
  }Bits;
}byte_ut;

typedef union
{
  uint16_t tp_value : 10;
}my_union;

byte_ut cbyte;
byte_ut cbyte2;
 
void setup()
{
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  while (!Serial);
  SPI.begin();               //Begins SPI communication
 
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS, MCP_8MHZ);//Sets CAN at speed 125KBPS
  mcp2515.setNormalMode();//Sets CAN at normal mode
}
 
 
void loop()
{
  my_union t;
  t.tp_value = analogRead(A0);
  t.tp_value = map(t.tp_value, 1023, 0, 0, 255);
  
  canMsg1.can_id  = 0x0F6;
  canMsg1.can_dlc = 8;

  add_to_msg(8, t.tp_value);
  add_to_msg(8, get_distance());
  add_to_msg(2, 0b10);
  t.tp_value = analogRead(A1);
  t.tp_value = map(t.tp_value, 1023, 0, 0, 255);
  add_to_msg(8, t.tp_value);
  add_to_msg(6, 0b111000);
  add_to_msg(8, 0b00000100);
  add_to_msg(8, 0b00000010);
  add_to_msg(8, 0b00000001);
  add_to_msg(8, 0b00000000);
}

////////////////////////////////hc-sr04 get_distance() function////////////////////////////////

long get_distance()
{
  long sure, mesafe;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  sure = pulseIn(echoPin, HIGH);
  mesafe = (sure/2) * 0.0343;
  return mesafe;
}

void add_to_msg(uint8_t digits, uint8_t value)
{
  cbyte2.byte = value;

  for(uint8_t bit_counter_2 = 0; bit_counter_2 < digits; bit_counter_2++)
  {
          if(bit_counter == 0)
        {
                switch(bit_counter_2)
                {
                  case 0: cbyte.Bits.bit0 = cbyte2.Bits.bit0; break;
                  case 1: cbyte.Bits.bit0 = cbyte2.Bits.bit1; break;
                  case 2: cbyte.Bits.bit0 = cbyte2.Bits.bit2; break;
                  case 3: cbyte.Bits.bit0 = cbyte2.Bits.bit3; break;
                  case 4: cbyte.Bits.bit0 = cbyte2.Bits.bit4; break;
                  case 5: cbyte.Bits.bit0 = cbyte2.Bits.bit5; break;
                  case 6: cbyte.Bits.bit0 = cbyte2.Bits.bit6; break;
                  case 7: cbyte.Bits.bit0 = cbyte2.Bits.bit7; break;
                }
        }
        else if(bit_counter == 1)
        {
                switch(bit_counter_2)
                {
                  case 0: cbyte.Bits.bit1 = cbyte2.Bits.bit0; break;
                  case 1: cbyte.Bits.bit1 = cbyte2.Bits.bit1; break;
                  case 2: cbyte.Bits.bit1 = cbyte2.Bits.bit2; break;
                  case 3: cbyte.Bits.bit1 = cbyte2.Bits.bit3; break;
                  case 4: cbyte.Bits.bit1 = cbyte2.Bits.bit4; break;
                  case 5: cbyte.Bits.bit1 = cbyte2.Bits.bit5; break;
                  case 6: cbyte.Bits.bit1 = cbyte2.Bits.bit6; break;
                  case 7: cbyte.Bits.bit1 = cbyte2.Bits.bit7; break;
                }
        }
        else if(bit_counter == 2)
        {
                switch(bit_counter_2)
                {
                  case 0: cbyte.Bits.bit2 = cbyte2.Bits.bit0; break;
                  case 1: cbyte.Bits.bit2 = cbyte2.Bits.bit1; break;
                  case 2: cbyte.Bits.bit2 = cbyte2.Bits.bit2; break;
                  case 3: cbyte.Bits.bit2 = cbyte2.Bits.bit3; break;
                  case 4: cbyte.Bits.bit2 = cbyte2.Bits.bit4; break;
                  case 5: cbyte.Bits.bit2 = cbyte2.Bits.bit5; break;
                  case 6: cbyte.Bits.bit2 = cbyte2.Bits.bit6; break;
                  case 7: cbyte.Bits.bit2 = cbyte2.Bits.bit7; break;
                }
        }
        else if(bit_counter == 3)
        {
                switch(bit_counter_2)
                {
                  case 0: cbyte.Bits.bit3 = cbyte2.Bits.bit0; break;
                  case 1: cbyte.Bits.bit3 = cbyte2.Bits.bit1; break;
                  case 2: cbyte.Bits.bit3 = cbyte2.Bits.bit2; break;
                  case 3: cbyte.Bits.bit3 = cbyte2.Bits.bit3; break;
                  case 4: cbyte.Bits.bit3 = cbyte2.Bits.bit4; break;
                  case 5: cbyte.Bits.bit3 = cbyte2.Bits.bit5; break;
                  case 6: cbyte.Bits.bit3 = cbyte2.Bits.bit6; break;
                  case 7: cbyte.Bits.bit3 = cbyte2.Bits.bit7; break;
                }
        }
        else if(bit_counter == 4)
        {
                switch(bit_counter_2)
                {
                  case 0: cbyte.Bits.bit4 = cbyte2.Bits.bit0; break;
                  case 1: cbyte.Bits.bit4 = cbyte2.Bits.bit1; break;
                  case 2: cbyte.Bits.bit4 = cbyte2.Bits.bit2; break;
                  case 3: cbyte.Bits.bit4 = cbyte2.Bits.bit3; break;
                  case 4: cbyte.Bits.bit4 = cbyte2.Bits.bit4; break;
                  case 5: cbyte.Bits.bit4 = cbyte2.Bits.bit5; break;
                  case 6: cbyte.Bits.bit4 = cbyte2.Bits.bit6; break;
                  case 7: cbyte.Bits.bit4 = cbyte2.Bits.bit7; break;
                }
        }
        else if(bit_counter == 5)
        {
                switch(bit_counter_2)
                {
                  case 0: cbyte.Bits.bit5 = cbyte2.Bits.bit0; break;
                  case 1: cbyte.Bits.bit5 = cbyte2.Bits.bit1; break;
                  case 2: cbyte.Bits.bit5 = cbyte2.Bits.bit2; break;
                  case 3: cbyte.Bits.bit5 = cbyte2.Bits.bit3; break;
                  case 4: cbyte.Bits.bit5 = cbyte2.Bits.bit4; break;
                  case 5: cbyte.Bits.bit5 = cbyte2.Bits.bit5; break;
                  case 6: cbyte.Bits.bit5 = cbyte2.Bits.bit6; break;
                  case 7: cbyte.Bits.bit5 = cbyte2.Bits.bit7; break;
                }
        }
        else if(bit_counter == 6)
        {
                switch(bit_counter_2)
                {
                  case 0: cbyte.Bits.bit6 = cbyte2.Bits.bit0; break;
                  case 1: cbyte.Bits.bit6 = cbyte2.Bits.bit1; break;
                  case 2: cbyte.Bits.bit6 = cbyte2.Bits.bit2; break;
                  case 3: cbyte.Bits.bit6 = cbyte2.Bits.bit3; break;
                  case 4: cbyte.Bits.bit6 = cbyte2.Bits.bit4; break;
                  case 5: cbyte.Bits.bit6 = cbyte2.Bits.bit5; break;
                  case 6: cbyte.Bits.bit6 = cbyte2.Bits.bit6; break;
                  case 7: cbyte.Bits.bit6 = cbyte2.Bits.bit7; break;
                }
        }
        else if(bit_counter == 7)
        {
                switch(bit_counter_2)
                {
                  case 0: cbyte.Bits.bit7 = cbyte2.Bits.bit0; break;
                  case 1: cbyte.Bits.bit7 = cbyte2.Bits.bit1; break;
                  case 2: cbyte.Bits.bit7 = cbyte2.Bits.bit2; break;
                  case 3: cbyte.Bits.bit7 = cbyte2.Bits.bit3; break;
                  case 4: cbyte.Bits.bit7 = cbyte2.Bits.bit4; break;
                  case 5: cbyte.Bits.bit7 = cbyte2.Bits.bit5; break;
                  case 6: cbyte.Bits.bit7 = cbyte2.Bits.bit6; break;
                  case 7: cbyte.Bits.bit7 = cbyte2.Bits.bit7; break;
                }
        }
        inc_counters();
  } 
}

void inc_counters()
{
  if(bit_counter == 7 && byte_counter >= 7)
  {
    canMsg1.data[7] = cbyte.byte;
    mcp2515.sendMessage(&canMsg1);
    delay(400);
    bit_counter = 0;
    byte_counter = 0;
    Serial.println("x");
  }
  else if(bit_counter == 7)
  {
    //Serial.println(byte_counter);
    canMsg1.data[byte_counter] = cbyte.byte;
    bit_counter = 0;
    byte_counter++;
  }
  else
  {
    bit_counter++;
  }
}
