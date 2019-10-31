#ifndef SPI_FACTORY_H
#define SPI_FACTORY_H

#include "SPI_Interface.h"
#include "SPI_4Pin.h"
#include "SPI_Config.h" 

class SpiFactory
 {
 public:
     static SPI_Interface *SPI_Factory(const SPI_Config cfg)
     {
         return new SPI_4Pin( );
     }
 };
 #endif
