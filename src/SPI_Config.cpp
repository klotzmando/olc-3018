#include "SPI_Config.h"

void SPI_Config::CS(uint8_t setting) {
	digitalWrite(cs, setting);
}

void SPI_Config::DIN(uint8_t data) {
	digitalWrite(din, data);
}

void SPI_Config::CLK(/* set clock state either HIGH or LOW */uint8_t state) {
	digitalWrite(clk, state);
}

void SPI_Config::DC(/* High or LOW */uint8_t state) {
	digitalWrite(dc, state);
}

void SPI_Config::RST(/* High or low */uint8_t state) {
	digitalWrite(rst, state);
}
