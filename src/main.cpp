#include <Arduino.h>
#define INTERFACE_4WIRE_SPI 1
#include "OLED_GFX.h"
#include "GFX_Test.h"

#include <SPI.h>
#include <Wire.h>

OLED_GFX oled = OLED_GFX();
GFX_Test theTest(oled);

void setup()  {

  //Init GPIO
  pinMode(oled_cs, OUTPUT);
  pinMode(oled_rst, OUTPUT);
  pinMode(oled_dc, OUTPUT);

  //Init UART
  Serial.begin(115200);

#if INTERFACE_4WIRE_SPI
  //Init SPI
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();

#elif INTERFACE_3WIRE_SPI

  pinMode(oled_sck, OUTPUT);
  pinMode(oled_din, OUTPUT);

#endif

  oled.Device_Init();
  
}


void loop() {
  theTest.RunTest();
  delay(1000);
}

