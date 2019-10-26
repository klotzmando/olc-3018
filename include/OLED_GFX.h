#ifndef __OLED_GFX_H
#define __OLED_GFX_H


#include "OLED_Driver.h"
#include "font.h"
#include "Font_5X8.h"
#include "Font_8x16.h"

class OLED_GFX : virtual public OLED_Driver {

  private:
    Font* font;
    Font_5x8 font_5x8;
    Font_8x16 font_8x16;
  
  public:
      
    OLED_GFX(void);
      
    void Set_FontSize(FONT_SIZE size);
    
    void Draw_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    
    void Draw_Rect(int16_t x, int16_t y, int16_t w, int16_t h);
    void Fill_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
    
    void Fill_Circle(int16_t x0, int16_t y0, int16_t r);
    void Draw_Circle(int16_t x0, int16_t y0, int16_t r);
    
    void Draw_RoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r);
    void Draw_Triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2);
    
    void print_String(uint8_t x, uint8_t y, const uint8_t *text, FONT_SIZE size);
    void Display_String_5x8(uint8_t x, uint8_t y, const uint8_t *text);
    void Display_String_8x16(uint8_t x, uint8_t y, const uint8_t *text);
    
  private:
    
    void Write_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    
    void FillCircle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta);
    void DrawCircle_Helper( int16_t x0, int16_t y0, int16_t r, uint8_t corner);

  };
  

#endif
