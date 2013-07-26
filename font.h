#ifndef FONT_H
#define FONT_H 1

#include "lcd.h"

 typedef struct {
     uint32_t code;
     const tImage *image;
     } tChar;

 typedef struct {
     int length;
     const tChar *chars;
     } tFont;

void FONT_draw_string(const char *str, int x, int y, uint32_t fgColor, uint32_t bgColor, const tFont *font);

#endif /* FONT_H */
