#include "OLED_Interface.h"
#include <spi.h>

void OLED_Interface::Initialize(SPI_Config pins) {
	this->pins = pins;

}

void OLED_Interface::WriteData(uint8_t data) {
	
  pins.DC(HIGH);
  SPI.transfer(data);
  pins.DC(LOW);

}

void OLED_Interface::WriteCommand(uint8_t cmd) {
  pins.DC(LOW);
  SPI.transfer(cmd);
  pins.DC(HIGH);
}

OLED_Interface::OLED_Interface() {
}
