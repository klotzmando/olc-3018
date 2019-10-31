#include "SPI_3Pin.h"
#include "SPI_Config.h"

const SPI_Config cfg;

void SPI_3Pin::Initialize()
{
     digitalWrite(cfg.dc, LOW);
};

void SPI_3Pin::WriteCommand(uint8_t cmd) {

  uint8_t i;

  digitalWrite(cfg.clk, LOW);
  digitalWrite(cfg.din, LOW);
  digitalWrite(cfg.clk, HIGH);

  for (i = 0x80; i > 0; i >>= 1)
  {

       digitalWrite(cfg.clk, LOW);

       if (cmd & i)
            digitalWrite(cfg.din, HIGH);
       else
            digitalWrite(cfg.din, LOW);

       digitalWrite(cfg.clk, HIGH);
  }
}

void SPI_3Pin::WriteData(uint8_t data) {

  uint8_t i;

  digitalWrite(cfg.clk, LOW);
  digitalWrite(cfg.din, HIGH);
  digitalWrite(cfg.clk, HIGH);

  for (i = 0x80; i > 0; i >>= 1)
  {

       digitalWrite(cfg.clk, LOW);

       if (data & i)
            digitalWrite(cfg.din, HIGH);
       else
            digitalWrite(cfg.din, LOW);
       digitalWrite(cfg.clk, HIGH);
  }
}

void SPI_3Pin::WriteData(uint8_t *dat_p, int length)
{

     uint16_t i;
     uint8_t j;

     for (i = 0; i < length; i++)
     {

          digitalWrite(cfg.clk, LOW);
          digitalWrite(cfg.din, HIGH);
          digitalWrite(cfg.clk, HIGH);

          for (j = 0x80; j > 0; j >>= 1)
          {

               digitalWrite(cfg.clk, LOW);
               if (dat_p[i] & j)
                    digitalWrite(cfg.din, HIGH);
               else
                    digitalWrite(cfg.din, LOW);
               digitalWrite(cfg.clk, HIGH);
          }
     }
}
