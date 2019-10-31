#include "OLED_Driver.h"
#include "ASCII_Font.h"
#include "SpiFactory.h"



#if INTERFACE_4WIRE_SPI
  #if INTERFACE_3WIRE_SPI
    #error "SPI Setting Error !!"
  #endif
#elif INTERFACE_3WIRE_SPI

#else
  #error "SPI Setting Error !!"
#endif

uint8_t color_byte[2];
uint8_t color_fill_byte[2];
const uint8_t clear_byte[] = {0x00, 0x00};

const SPI_Config cfg;
OLED_Driver::OLED_Driver(void):oSpi(SpiFactory::SPI_Factory(cfg))  {
}


void OLED_Driver::Set_Color(uint16_t color)  {
  
  color_byte[0] = (uint8_t)(color >> 8);
  color_byte[1] = (uint8_t)(color & 0x00ff);
}

void OLED_Driver::Set_FillColor(uint16_t color)  {
  
  color_fill_byte[0] = (uint8_t)(color >> 8);
  color_fill_byte[1] = (uint8_t)(color & 0x00ff);
}

void OLED_Driver::RAM_Address(void)  {
  
  oSpi->WriteCommand(0x15);
  oSpi->WriteData(0x00);
  oSpi->WriteData(0x7f);

  oSpi->WriteCommand(0x75);
  oSpi->WriteData(0x00);
  oSpi->WriteData(0x7f);
}

void OLED_Driver::Clear_Screen(void)  {
  
  int i,j;
  
  RAM_Address();
  oSpi->WriteCommand(0x5C);
  for(i=0;i<128;i++)  {
    for(j=0;j<128;j++)  {
#if INTERFACE_4WIRE_SPI
      oSpi->WriteData(clear_byte[0]);
      oSpi->WriteData(clear_byte[1]);
#elif INTERFACE_3WIRE_SPI
      oSpi->WriteData(clear_byte, 2);
#endif
    }
  }
}


void OLED_Driver::Fill_Color(uint16_t color)  {
  
  uint16_t i,j;
  RAM_Address();
  oSpi->WriteCommand(0x5C);
  Set_FillColor(color);
  for(i = 0; i < 128; i++)  {
    for(j = 0; j < 128; j++)  {
#if INTERFACE_4WIRE_SPI
      oSpi->WriteData(color_fill_byte[0]);
      oSpi->WriteData(color_fill_byte[1]);
#elif INTERFACE_3WIRE_SPI
      oSpi->WriteData(color_fill_byte, 2);
#endif

    }
  }
}

void OLED_Driver::Set_Coordinate(uint16_t x, uint16_t y)  {

  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT))
    return;
  //Set x and y coordinate
  oSpi->WriteCommand(SSD1351_CMD_SETCOLUMN);
  oSpi->WriteData(x);
  oSpi->WriteData(SSD1351_WIDTH-1);
  
  oSpi->WriteCommand(SSD1351_CMD_SETROW);
  oSpi->WriteData(y);
  oSpi->WriteData(SSD1351_HEIGHT-1);
  
  oSpi->WriteCommand(SSD1351_CMD_WRITERAM);
}

void OLED_Driver::Set_Address(uint8_t column, uint8_t row)  {
  
  oSpi->WriteCommand(SSD1351_CMD_SETCOLUMN);  
  oSpi->WriteData(column);  //X start 
  oSpi->WriteData(column); //X end 
  oSpi->WriteCommand(SSD1351_CMD_SETROW); 
  oSpi->WriteData(row);  //Y start 
  oSpi->WriteData(row+7);  //Y end 
  oSpi->WriteCommand(SSD1351_CMD_WRITERAM); 
}

void OLED_Driver::Write_text(uint8_t dat) {
    
  uint8_t i;

  for (i = 0; i < 8; i++)
  {
    if (dat & 0x01)
    {
      oSpi->WriteData(color_byte[0]);
      oSpi->WriteData(color_byte[1]);
    }
    else
    {
      oSpi->WriteData(0x00);
      oSpi->WriteData(0x00);
    }
    dat >>= 1;
  }
}

void  OLED_Driver::Invert(bool v) {
  
  if (v)
    oSpi->WriteCommand(SSD1351_CMD_INVERTDISPLAY);
  else
    oSpi->WriteCommand(SSD1351_CMD_NORMALDISPLAY);
}

void OLED_Driver::Draw_Pixel(int16_t x, int16_t y)
{
  // Bounds check.
  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT)) return;
  if ((x < 0) || (y < 0)) return;

  Set_Address(x, y);
  
  // transfer data
#if INTERFACE_4WIRE_SPI
  oSpi->WriteData(color_byte[0]);
  oSpi->WriteData(color_byte[1]);
#elif INTERFACE_3WIRE_SPI
  oSpi->WriteData(color_byte, 2);
#endif
  
}
  

  
void OLED_Driver::Device_Init(void) {
  oSpi->Initialize();
  digitalWrite(cfg.cs, LOW);
  digitalWrite(cfg.rst, LOW);
  delay(500);
  digitalWrite(cfg.rst, HIGH);
  delay(500);
    
  oSpi->WriteCommand(0xfd);  // command lock
  oSpi->WriteData(0x12);
  oSpi->WriteCommand(0xfd);  // command lock
  oSpi->WriteData(0xB1);

  oSpi->WriteCommand(0xae);  // display off
  oSpi->WriteCommand(0xa4);  // Normal Display mode

  oSpi->WriteCommand(0x15);  //set column address
  oSpi->WriteData(0x00); //column address start 00
  oSpi->WriteData(0x7f); //column address end 95
  oSpi->WriteCommand(0x75);  //set row address
  oSpi->WriteData(0x00); //row address start 00
  oSpi->WriteData(0x7f); //row address end 63  

  oSpi->WriteCommand(0xB3);
  oSpi->WriteData(0xF1);

  oSpi->WriteCommand(0xCA);  
  oSpi->WriteData(0x7F);

  oSpi->WriteCommand(0xa0);  //set re-map & data format
  oSpi->WriteData(0x74); //Horizontal address increment
            //74
  oSpi->WriteCommand(0xa1);  //set display start line
  oSpi->WriteData(0x00); //start 00 line

  oSpi->WriteCommand(0xa2);  //set display offset
  oSpi->WriteData(0x00);

  oSpi->WriteCommand(0xAB);  
  oSpi->WriteCommand(0x01);  

  oSpi->WriteCommand(0xB4);  
  oSpi->WriteData(0xA0);   
  oSpi->WriteData(0xB5);  
  oSpi->WriteData(0x55);    

  oSpi->WriteCommand(0xC1);  
  oSpi->WriteData(0xC8); 
  oSpi->WriteData(0x80);
  oSpi->WriteData(0xC0);

  oSpi->WriteCommand(0xC7);  
  oSpi->WriteData(0x0F);

  oSpi->WriteCommand(0xB1);  
  oSpi->WriteData(0x32);

  oSpi->WriteCommand(0xB2);  
  oSpi->WriteData(0xA4);
  oSpi->WriteData(0x00);
  oSpi->WriteData(0x00);

  oSpi->WriteCommand(0xBB);  
  oSpi->WriteData(0x17);

  oSpi->WriteCommand(0xB6);  
  oSpi->WriteData(0x01);

  oSpi->WriteCommand(0xBE);  
  oSpi->WriteData(0x05);

  oSpi->WriteCommand(0xA6);

  Clear_Screen();
  oSpi->WriteCommand(0xaf);   //display on
}

  
  
// Draw a horizontal line ignoring any screen rotation.
void OLED_Driver::Draw_FastHLine(int16_t x, int16_t y, int16_t length) {
  // Bounds check
  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT))
    return;

  // X bounds check
  if (x+length > SSD1351_WIDTH) {
    length = SSD1351_WIDTH - x - 1;
  }

  if (length < 0)
    return;

  // set location
  oSpi->WriteCommand(SSD1351_CMD_SETCOLUMN);
  oSpi->WriteData(x);
  oSpi->WriteData(x+length-1);
  oSpi->WriteCommand(SSD1351_CMD_SETROW);
  oSpi->WriteData(y);
  oSpi->WriteData(y);
  // fill!
  oSpi->WriteCommand(SSD1351_CMD_WRITERAM);  

  for (uint16_t i=0; i < uint16_t( length); i++)  {
    oSpi->WriteData(color_byte[0]);
    oSpi->WriteData(color_byte[1]);
  }
}
  
  // Draw a vertical line ignoring any screen rotation.
void OLED_Driver::Draw_FastVLine(int16_t x, int16_t y, int16_t length)  {
  // Bounds check

  uint16_t i;
  
  if ((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT))
    return;
  // X bounds check
  if (y+length > SSD1351_HEIGHT) {
    length = SSD1351_HEIGHT - y - 1;
  }
  if (length < 0)
    return;

  // set location
  oSpi->WriteCommand(SSD1351_CMD_SETCOLUMN);
  oSpi->WriteData(x);
  oSpi->WriteData(x);
  oSpi->WriteCommand(SSD1351_CMD_SETROW);
  oSpi->WriteData(y);
  oSpi->WriteData(y+length-1);
  // fill!
  oSpi->WriteCommand(SSD1351_CMD_WRITERAM);  
    
  for (i = 0; i < length; i++)  {
#if INTERFACE_4WIRE_SPI
    oSpi->WriteData(color_byte[0]);
    oSpi->WriteData(color_byte[1]);
#elif INTERFACE_3WIRE_SPI
    oSpi->WriteData(color_byte, 2);
#endif
  }
}

void OLED_Driver::Display_Interface(void)
{

  uint16_t i, j, color;

  Fill_Color(BLACK);

  Set_Coordinate(0, 1);
  for (i = 0; i < 8; i++)
  {
    for(j = 0; j < 128; j++) {
      if((interface_1[(i*128+j)/8]>>((i*128+j)%8))&0x01)  
        color = GREEN+((i*128+j)<<11);      
      else
        color = BLACK;
      
      Set_Color(color);
      oSpi->WriteData(color_byte[0]);
      oSpi->WriteData(color_byte[1]);
    }
  }

  Set_Coordinate(0,20);
  for(i = 0 ; i < 22 ; i++) {
    for(j = 0; j < 128; j++)  {
      if((interface_2[(i*128+j)/8]>>((i*128+j)%8))&0x01)  
        color = CYAN;
      else
        color = BLACK;
      
      Set_Color(color);
      oSpi->WriteData(color_byte[0]);
      oSpi->WriteData(color_byte[1]);
    }
  }

  Set_Coordinate(0,60);
  for(i = 0 ; i < 18 ; i++) {
    for(j = 0; j < 128; j++)  {
      if((interface_4[(i*128+j)/8]>>((i*128+j)%8))&0x01)  
        color = BLUE+(i&0xf000);
      else
        color = BLACK;
      
      Set_Color(color);
      oSpi->WriteData(color_byte[0]);
      oSpi->WriteData(color_byte[1]);      
    }
  }

  oSpi->WriteCommand(SSD1351_CMD_SETCOLUMN);  
  oSpi->WriteData(80);  //X start 
  oSpi->WriteData(80+8*5-1); //X end 
  oSpi->WriteCommand(SSD1351_CMD_SETROW); 
  oSpi->WriteData(90);  //Y start 
  oSpi->WriteData(90+16-1);  //Y end 
  oSpi->WriteCommand(SSD1351_CMD_WRITERAM); 
  
  for(i = 0 ; i < 16 ; i++) {
    for(j = 0; j < 8*5; j++)  {
      if((interface_text1[(i*8*5+j)/8]>>((i*8*5+j)%8))&0x01)  
        color = BLUE+0x0f00+i*128+j*32;
      else
        color = BLACK;
      
      Set_Color(color);
      oSpi->WriteData(color_byte[0]);
      oSpi->WriteData(color_byte[1]);      
    }
  }

  oSpi->WriteCommand(SSD1351_CMD_SETCOLUMN);  
  oSpi->WriteData(0);  //X start 
  oSpi->WriteData(0+8*9-1); //X end 
  oSpi->WriteCommand(SSD1351_CMD_SETROW); 
  oSpi->WriteData(90);  //Y start 
  oSpi->WriteData(90+16-1);  //Y end 
  oSpi->WriteCommand(SSD1351_CMD_WRITERAM); 
  
  for(i = 0 ; i < 16 ; i++) {
    for(j = 0; j < 8*9; j++)  {
      if((interface_text2[(i*8*9+j)/8]>>((i*8*9+j)%8))&0x01)  
        color = BLUE+0xf000+i*128;
      else
        color = BLACK;
      
      Set_Color(color);
      oSpi->WriteData(color_byte[0]);
      oSpi->WriteData(color_byte[1]);      
    }
  }

  Set_Coordinate(0,118);
  for(i = 0 ; i < 9 ; i++) {
    for(j = 0; j < 128; j++)  {
      if((interface_3[(i*128+j)/8]>>((i*128+j)%8))&0x01)  
        color = RED+(i*128+j);
      else
        color = BLACK;
      
      Set_Color(color);
      oSpi->WriteData(color_byte[0]);
      oSpi->WriteData(color_byte[1]);
    }
  }

  
  Set_Coordinate(0,15);
  for(i = 0 ; i < 22 ; i++)  {
    for(j = 0; j < 128; j++) {
      if((interface_2[(i*128+j)/8]>>((i*128+j)%8))&0x01)  {
        if((i*128+j)<128*12)
          color = GREEN+((i*128+j)<<11);
        else if((i*128+j)<128*40)
          color = CYAN;
        else
          color = RED+(i*128+j)-128*40;
      }
      else  {
        color = BLACK;
      }
      Set_Color(color);
      oSpi->WriteData(color_byte[0]);
      oSpi->WriteData(color_byte[1]);
    }
  }

}




