#ifndef __OLED_DRIVER_H
#define __OLED_DRIVER_H

#include "stdlib.h"
#include "SPI.h"
#include "SPI_Interface.h"

#define SSD1351_WIDTH 128
#define SSD1351_HEIGHT 128

#define SSD1351_CMD_SETCOLUMN 0x15
#define SSD1351_CMD_SETROW 0x75
#define SSD1351_CMD_WRITERAM 0x5C
#define SSD1351_CMD_READRAM 0x5D
#define SSD1351_CMD_SETREMAP 0xA0
#define SSD1351_CMD_STARTLINE 0xA1
#define SSD1351_CMD_DISPLAYOFFSET 0xA2
#define SSD1351_CMD_DISPLAYALLOFF 0xA4
#define SSD1351_CMD_DISPLAYALLON 0xA5
#define SSD1351_CMD_NORMALDISPLAY 0xA6
#define SSD1351_CMD_INVERTDISPLAY 0xA7
#define SSD1351_CMD_FUNCTIONSELECT 0xAB
#define SSD1351_CMD_DISPLAYOFF 0xAE
#define SSD1351_CMD_DISPLAYON 0xAF
#define SSD1351_CMD_PRECHARGE 0xB1
#define SSD1351_CMD_DISPLAYENHANCE 0xB2
#define SSD1351_CMD_CLOCKDIV 0xB3
#define SSD1351_CMD_SETVSL 0xB4
#define SSD1351_CMD_SETGPIO 0xB5
#define SSD1351_CMD_PRECHARGE2 0xB6
#define SSD1351_CMD_SETGRAY 0xB8
#define SSD1351_CMD_USELUT 0xB9
#define SSD1351_CMD_PRECHARGELEVEL 0xBB
#define SSD1351_CMD_VCOMH 0xBE
#define SSD1351_CMD_CONTRASTABC 0xC1
#define SSD1351_CMD_CONTRASTMASTER 0xC7
#define SSD1351_CMD_MUXRATIO 0xCA
#define SSD1351_CMD_COMMANDLOCK 0xFD
#define SSD1351_CMD_HORIZSCROLL 0x96
#define SSD1351_CMD_STOPSCROLL 0x9E
#define SSD1351_CMD_STARTSCROLL 0x9F

#define swap(a, b) \
  {                \
    uint8_t t = a; \
    a = b;         \
    b = t;         \
  }

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

class OLED_Driver
{
private:
  SPI_Interface *oSpi;
  uint8_t backgroundColor[2];
  uint8_t foregroundColor[2];
  uint8_t color_fill_byte[2];

public:
  OLED_Driver(void);

  void DeviceInit(void);
  void ClearScreen(void);
  void FillColor(uint16_t color);
  void SetCoordinate(uint16_t x, uint16_t y);

  void Writetext(uint8_t data1);
  void SetAddress(uint8_t column, uint8_t row);

  /**
      * Set the color used for object drawn on the display.
      */
  void SetFGColor(uint16_t color);

  /**
      * Set the color for the background which can also be used for "blank"
      */
  void SetBGColor(/* The RGB value for the color. */ uint16_t color);
  
  void SetFillColor(uint16_t color);

  void Invert(bool v);
  void DrawPixel(int16_t x, int16_t y);
  void DrawPixel(void);
  void ErasePixel(void);

  void WriteCommand(uint8_t dat) { oSpi->WriteCommand(dat); };
  void WriteData(uint8_t dat) { oSpi->WriteData(dat); };
  void WriteData(uint8_t *dat_p, int length) { oSpi->WriteData(dat_p, length); };

  void DrawFastHLine(int16_t x, int16_t y, int16_t length);
  void DrawFastVLine(int16_t x, int16_t y, int16_t length);

  void Displaybmp(void);
  void DisplayInterface(void);

private:
  void RAMAddress(void);

public:
};

#endif
