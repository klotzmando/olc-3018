#ifndef FONT_8X16_H
#define FONT_8X16_H

class Font_8x16
: public Font {
private:
    const unsigned char ascii_table_8x16[95][16];

public:
    Font_8x16();
};

#endif
