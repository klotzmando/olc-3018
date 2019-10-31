#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

#include <stdint.h>
#include "SPI_Config.h"


class SPI_Interface {
public:
	/**
	 * Writes data to the interface as opposed to writing commands to the interface.
	 */
	virtual void WriteData(uint8_t data) = 0;

	virtual void WriteData(uint8_t* dat_p, int length) = 0;

	/**
	 * Writes a command to the attached device as  opposed to data.
	 * Modifies the behavior of the device not its presentation.
	 */
	virtual void WriteCommand(uint8_t cmd) = 0;

	SPI_Interface(){};

	virtual void Initialize() = 0;
};

#endif
