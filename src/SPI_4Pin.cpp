#ifndef SPI_4PIN_H
#define SPI_4PIN_H

#include <spi.h>
#include "SPI_Config.h"
#include "SPI_4Pin.h"

const SPI_Config cfg;

void SPI_4Pin::Initialize()
{
  //Init GPIO
  pinMode(cfg.cs, OUTPUT);
  pinMode(cfg.rst, OUTPUT);
  pinMode(cfg.dc, OUTPUT);
  
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();
}

void SPI_4Pin::WriteData(uint8_t data) {
	
  digitalWrite(cfg.dc, HIGH);
  SPI.transfer(data);

}
void SPI_4Pin::WriteData(uint8_t* dat_p, int length)
{
  digitalWrite(cfg.dc, HIGH);
  for(int i=0; i < length; i++){
    SPI.transfer(dat_p[i]);
  }
  // SPI.transfer(dat_p, length);
}


void SPI_4Pin::WriteCommand(uint8_t cmd) {
  digitalWrite(cfg.dc,LOW);
  SPI.transfer(cmd);
}

#endif
