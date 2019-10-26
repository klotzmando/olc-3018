#ifndef SPI_4PIN_H
#define SPI_4PIN_H

#include "SPI_4Pin.h"
#include <spi.h>

void SPI_4Pin::WriteData(uint8_t data) {
	
  cfg.DC(HIGH);
  SPI.transfer(data);
  cfg.DC(LOW);

}

void SPI_4Pin::WriteCommand(uint8_t cmd) {
  cfg.DC(LOW);
  SPI.transfer(cmd);
  cfg.DC(HIGH);
}

#endif
