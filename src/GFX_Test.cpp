#include "GFX_Test.h"

void GFX_Test::RunTest()
{
    static uint8_t testNumber = 0;
    switch (testNumber++)
    {
    case 0:
        oled.ClearScreen();

        oled.SetFGColor(BLUE);
        oled.print_String(20, 50, (const uint8_t *)"Hello WaveShare !", FONT_5X8);
        break;

    case 1:
        oled.ClearScreen();

        oled.SetFGColor(WHITE);
        oled.DrawPixel(50, 50);
        break;
    case 3:
        lcdTestPattern();
        break;
    case 4:
        testlines();
        break;
    case 5:
        testfastlines();
        break;
    case 6:
        testdrawrects();
        break;
    case 7:
        testfillrects(BLUE, YELLOW);
        break;
    case 8:
        oled.ClearScreen();
        testfillcircles(63, BLUE);
        break;
    case 9:
        testdrawcircles(WHITE);
        break;
    case 10:
        testroundrects();
        break;
    case 11:
        testtriangles();
        break;
    case 12:
        oled.DisplayInterface();
        delay(2000); // temporary to allow for better inspection
        break;
    case 13:
        testNumber = 0;
        break;
    }
}

void GFX_Test::testlines(void)
{

    oled.SetFGColor(RED);
    oled.ClearScreen();
    for (uint16_t x = 0; x <= SSD1351_WIDTH - 1; x += 6)
    {
        oled.Draw_Line(0, 0, x, SSD1351_HEIGHT - 1);
        delay(10);
    }
    for (uint16_t y = 0; y < SSD1351_HEIGHT - 1; y += 6)
    {
        oled.Draw_Line(0, 0, SSD1351_WIDTH - 1, y);
        delay(10);
    }

    oled.SetFGColor(YELLOW);
    oled.ClearScreen();
    for (uint16_t x = 0; x < SSD1351_WIDTH - 1; x += 6)
    {
        oled.Draw_Line(SSD1351_WIDTH - 1, 0, x, SSD1351_HEIGHT - 1);
        delay(10);
    }
    for (uint16_t y = 0; y < SSD1351_HEIGHT - 1; y += 6)
    {
        oled.Draw_Line(SSD1351_WIDTH - 1, 0, 0, y);
        delay(10);
    }

    oled.SetFGColor(BLUE);
    oled.ClearScreen();
    for (uint16_t x = 0; x < SSD1351_WIDTH - 1; x += 6)
    {
        oled.Draw_Line(0, SSD1351_HEIGHT - 1, x, 0);
        delay(10);
    }
    for (uint16_t y = 0; y < SSD1351_HEIGHT - 1; y += 6)
    {
        oled.Draw_Line(0, SSD1351_HEIGHT - 1, SSD1351_WIDTH - 1, y);
        delay(10);
    }

    oled.SetFGColor(GREEN);
    oled.ClearScreen();
    for (uint16_t x = 0; x < SSD1351_WIDTH - 1; x += 6)
    {
        oled.Draw_Line(SSD1351_WIDTH - 1, SSD1351_HEIGHT - 1, x, 0);
        delay(10);
    }
    for (uint16_t y = 0; y < SSD1351_HEIGHT - 1; y += 6)
    {
        oled.Draw_Line(SSD1351_WIDTH - 1, SSD1351_HEIGHT - 1, 0, y);
        delay(10);
    }
}

void GFX_Test::lcdTestPattern(void)
{
    uint32_t i, j;
    oled.SetCoordinate(0, 0);

    for (i = 0; i < 128; i++)
    {
        for (j = 0; j < 128; j++)
        {
            if (i < 16)
            {
                oled.SetFGColor(RED);
                oled.DrawPixel();
            }
            else if (i < 32)
            {
                oled.SetFGColor(YELLOW);
                oled.DrawPixel();
            }
            else if (i < 48)
            {
                oled.SetFGColor(GREEN);
                oled.DrawPixel();
            }
            else if (i < 64)
            {
                oled.SetFGColor(CYAN);
                oled.DrawPixel();
            }
            else if (i < 80)
            {
                oled.SetFGColor(BLUE);
                oled.DrawPixel();
            }
            else if (i < 96)
            {
                oled.SetFGColor(MAGENTA);
                oled.DrawPixel();
            }
            else if (i < 112)
            {
                oled.SetFGColor(BLACK);
                oled.DrawPixel();
            }
            else
            {
                oled.SetFGColor(WHITE);
                oled.DrawPixel();
            }
        }
    }
}

void GFX_Test::testfastlines(void)
{

    oled.SetFGColor(WHITE);
    oled.ClearScreen();

    for (uint16_t y = 0; y < SSD1351_WIDTH - 1; y += 5)
    {
        oled.DrawFastHLine(0, y, SSD1351_WIDTH - 1);
        delay(10);
    }
    for (uint16_t x = 0; x < SSD1351_HEIGHT - 1; x += 5)
    {
        oled.DrawFastVLine(x, 0, SSD1351_HEIGHT - 1);
        delay(10);
    }
}

void GFX_Test::testdrawrects(void)
{
    oled.ClearScreen();
    for (uint16_t x = 0; x < SSD1351_HEIGHT - 1; x += 6)
    {
        oled.Draw_Rect((SSD1351_WIDTH - 1) / 2 - x / 2, (SSD1351_HEIGHT - 1) / 2 - x / 2, x, x);
        delay(10);
    }
}

void GFX_Test::testfillrects(uint16_t color1, uint16_t color2)
{

    uint16_t x = SSD1351_HEIGHT - 1;
    oled.ClearScreen();
    oled.SetFillColor(color2);
    for (; x > 6; x -= 6)
    {
        oled.Fill_Rect((SSD1351_WIDTH - 1) / 2 - x / 2, (SSD1351_HEIGHT - 1) / 2 - x / 2, x, x);
        oled.SetFGColor(color1);
        oled.Draw_Rect((SSD1351_WIDTH - 1) / 2 - x / 2, (SSD1351_HEIGHT - 1) / 2 - x / 2, x, x);
    }
}

void GFX_Test::testfillcircles(uint8_t radius, uint16_t color)
{

    oled.SetFGColor(color);

    oled.Fill_Circle(64, 64, radius);
}

void GFX_Test::testdrawcircles(uint16_t color)
{

    uint8_t r = 0;
    oled.SetFGColor(color);

    for (; r < SSD1351_WIDTH / 2; r += 4)
    {
        oled.Draw_Circle(64, 64, r);
        delay(10);
    }
}

void GFX_Test::testroundrects(void)
{

    int color = 100;
    int x = 0, y = 0;
    int w = SSD1351_WIDTH - 1, h = SSD1351_HEIGHT - 1;

    oled.ClearScreen();

    for (int i = 0; i <= 20; i++)
    {

        oled.Draw_RoundRect(x, y, w, h, 5);
        x += 2;
        y += 3;
        w -= 4;
        h -= 6;
        color += 1100;
        oled.SetFGColor(color);
    }
}

void GFX_Test::testtriangles(void)
{
    oled.ClearScreen();
    int color = 0xF800;
    int t;
    int w = SSD1351_WIDTH / 2;
    int x = SSD1351_HEIGHT - 1;
    int y = 0;
    int z = SSD1351_WIDTH;
    for (t = 0; t <= 15; t += 1)
    {
        oled.Draw_Triangle(w, y, y, x, z, x);
        x -= 4;
        y += 4;
        z -= 4;
        color += 100;
        oled.SetFGColor(color);
    }
}
