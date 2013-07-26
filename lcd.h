#ifndef _LCD__H
#define _LCD__H 1

#define MAX_X 240
#define MAX_Y 320

typedef struct {
     const uint32_t *data;
     int width;
     int height;
} tImage;

void LCD_WriteData(int data);
void LCD_WriteIndex(int index);
void LCD_WriteReg(int LCD_Reg, int LCD_RegValue);
void LCD_WriteDataStart();
void LCD_WriteDataOnly(int data);

void LCD_drawBMP(int x, int y, int fgColor, int bgColor, const tImage *image);
void LCD_DrawBar(const unsigned int x, const unsigned int y, const unsigned int w, const unsigned int h, const unsigned int color);
void LCD_DrawCircle(unsigned int xMidPoint, unsigned int yMidPoint, int radius, unsigned int color);

void LCD_setCursor(int xpos, int ypos);
void LCD_Clear(int Color);
int LCD_init();

#define SPI_CS_LOW  SPI0->SS = 0x06
#define SPI_CS_HI   SPI0->SS = 0x07

int SPI_WRITE(int data);

#endif
/* _LCD__H */
