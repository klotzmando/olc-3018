#ifndef FONT_5X8_H
#define FONT_5X8_H

class Font_5x8 : Font
{
private:
    const unsigned char ascii_table_5x8[95][5];

public:
    Font_5x8();
};

#endif
