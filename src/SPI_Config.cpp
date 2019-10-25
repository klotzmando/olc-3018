#include "SPI_Config.h"

SPI_Config::SPI_Config(uint8_t pinCS, int pinDin, int pinCLK, int pinDC,uint8_t pinRST) 
: cs(pinCS)
, din(pinDin)
, clk(pinCLK)
, dc(pinDC)
, rst(pinRST)
{
}

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
