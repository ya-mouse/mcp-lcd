#ifndef _LCD__H
#define _LCD__H 1

#define MAX_X 240
#define MAX_Y 320

void LCD_setCursor(int xpos, int ypos);
void LCD_Clear(int Color);
int LCD_init();

#endif
/* _LCD__H */
