#ifndef GFX_TEST_H
#define GFX_TEST_H

#include "OLED_GFX.h"

class GFX_Test
{

private:
	OLED_GFX &oled;

public:
	GFX_Test(OLED_GFX &display)
		: oled(display){};

	void RunTest();

private:
	void lcdTestPattern(void);
	void testroundrects(void);
	void testlines(void);
	void testfastlines(void);
	void testdrawrects(void);
	void testfillrects(uint16_t color1, uint16_t color2);
	void testfillcircles(uint8_t radius, uint16_t color);
	void testdrawcircles(uint16_t color);
	void testtriangles(void);
};

#endif
