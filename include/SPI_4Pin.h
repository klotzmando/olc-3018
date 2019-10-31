#include <stdint.h>
#include "SPI_Interface.h"

class SPI_4Pin : public SPI_Interface {

public:
	/**
	 * Writes data to the interface as opposed to writing commands to the interface.
	 */
	virtual void WriteData(uint8_t data);

	virtual void WriteData(uint8_t* dat_p, int length);

	virtual void Initialize(){};

	/**
	 * Writes a command to the attached device as  opposed to data.
	 * Modifies the behavior of the device not its presentation.
	 */
	virtual void WriteCommand(uint8_t cmd);

	SPI_4Pin(){ };

};
