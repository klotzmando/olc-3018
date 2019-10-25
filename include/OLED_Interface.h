#ifndef OLED_INTERFACE_H
#define OLED_INTERFACE_H

#include <stdint.h>
#include "SPI_Config.h"


class OLED_Interface {

protected:
	SPI_Config pins;

public:
	/**
	 * Writes data to the interface as opposed to writing commands to the interface.
	 */
	void WriteData(uint8_t data);

	void Write_Data(uint8_t* dat_p, int length);

	/**
	 * Writes a command to the attached device as  opposed to data.
	 * Modifies the behavior of the device not its presentation.
	 */
	void WriteCommand(uint8_t cmd);

	/**
	 * Prepares the hardware for communication.
	 */
	void Initialize(SPI_Config pins);

	OLED_Interface();

	enum InterfaceSpi {
		i_4pinSpi, 
		i_3pinSpi
	};
};

#endif
