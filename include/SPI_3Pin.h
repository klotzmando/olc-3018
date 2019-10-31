#ifndef OLED3PIN_H
#define OLED3PIN_H

#include "SPI_Interface.h"

class SPI_3Pin : SPI_Interface {


public:
     /**
      * 3-Pin spi constructor.
      */
     SPI_3Pin();

     /**
      * Put the device in operate state by toggling the appropriate data and control pins.
      */
     virtual void Initialize();

     /**
      * Writes a command to the attached device as  opposed to data.
      * Modifies the behavior of the device not its presentation.
      */
     virtual void WriteCommand(uint8_t cmd);

     /**
      * Writes data to the interface as opposed to writing commands to the interface.
      */
     virtual void WriteData(uint8_t data);

     virtual void WriteData(uint8_t* dat_p, int length);
};

#endif
