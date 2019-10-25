#ifndef SPI_CONFIG_H
#define SPI_CONFIG_H
#include <stdint.h>
#include <arduino.h>
/**
 * This is a container for the  I/O pins used to interface to a device connected via SPI.
 */
class SPI_Config {

private:
	/**
	 * Device chip select
	 */
	uint8_t cs;
	/**
	 * Data in, MOSI, used to transfer data to the attached device.
	 */
	uint8_t din;
	/**
	 * Data transfer clock.
	 */
	uint8_t clk;
	/**
	 * Not really part of the SPI configuration, but the displays tend to use dc to indicate that the data being transferred is to be interpreted as a command.
	 */
	uint8_t dc;
	/**
	 * Sends a reset signal to the device to place it in a know state.
	 */
	uint8_t rst;

public:
	/**
	 * Constructor
	 */
	SPI_Config(/* The pin used to supply chip select (CS) */uint8_t pinCS = PA4, /* Data pin for data being sent to the device.
The normal spi name is MOSI. */int pinDin = PA7, /* Pin supplying the clock to transfer data. */int pinCLK = PA5, /* The pin to use to indicate the data is for command or data. */int pinDC = PB8, /* The pin for sending a reset signal to the connected device. */uint8_t pinRST = PB9);

	void CS(/* Sets the CS to either HIGH or LOW */uint8_t setting);

	void DIN(uint8_t data );

	void CLK(/* set clock state either HIGH or LOW */uint8_t state);

	void DC(/* High or LOW */uint8_t state);

	void RST(/* High or low */uint8_t state);
};

#endif
