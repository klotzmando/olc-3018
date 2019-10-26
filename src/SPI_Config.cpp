#include "SPI_Config.h"

void SPI_Config::CS(uint8_t setting) {
	digitalWrite(cs, setting);
}

void SPI_Config::DC(/* High or LOW */uint8_t state) {
	digitalWrite(dc, state);
}

void SPI_Config::RST(/* High or low */uint8_t state) {
	digitalWrite(rst, state);
}
