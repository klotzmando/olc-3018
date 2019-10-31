#ifndef SPI_CONFIG_H
#define SPI_CONFIG_H
#include <stdint.h>
#include <arduino.h>
/**
 * This is a container for the  I/O pins used to interface to a device connected via SPI.
 */
struct SPI_Config
{
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

	enum InterfaceSpi
	{
		i_4pinSpi,
		i_3pinSpi
	} SpiConnecion = i_4pinSpi;

public:
	SPI_Config(uint8_t Cs = PA4, uint8_t Din = PA7, uint8_t Clk = PA5, uint8_t Dc = PB8, uint8_t Rst = PB9)
		: cs(Cs), din(Din), clk(Clk), dc(Dc), rst(Rst), SpiConnecion(i_4pinSpi){};

};

#endif
