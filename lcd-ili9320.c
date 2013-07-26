#include <HDL51001_ccf.h>
#include <spi.h>
#include <uart.h>

#include "lcd.h"
#include "util.h"

#define SPI_CS_LOW  SPI0->SS = 0x06
#define SPI_CS_HI   SPI0->SS = 0x07

int SPI_WRITE(int data)
{
    SPI0->TX = ((uint32_t)data) << 24;
    while(SPI_ST_TIP(SPI0) == 1);
    while(SPI_ST_NE(SPI0) == 0);
    return SPI0->RX;
}

void LCD_WriteData(int data)
{
	SPI_CS_LOW;

	SPI_WRITE(0x70 | 0x02);
	SPI_WRITE(data >> 8);
	SPI_WRITE(data & 0xff);

	SPI_CS_HI;
}

void LCD_WriteIndex(int index)
{
    SPI_CS_LOW;

    SPI_WRITE(0x70);
    SPI_WRITE(0);
    SPI_WRITE(index & 0xff);

    SPI_CS_HI;
}

uint32_t LCD_ReadData()
{
    uint32_t v;

    SPI_CS_LOW;

    SPI_WRITE(0x70 | 0x02 | 0x01);

    SPI_WRITE(0); // dummy read of value 0x83

    v = SPI_WRITE(0) >> 8; // should be 16

    v |= SPI_WRITE(0) >> 16; // should be 24

    SPI_CS_HI;
    return v;
}

void LCD_WriteReg(int LCD_Reg, int LCD_RegValue)
{
	LCD_WriteIndex(LCD_Reg);
	LCD_WriteData(LCD_RegValue);
}

int LCD_ReadReg(int LCD_reg)
{
    LCD_WriteIndex(LCD_reg);
    return LCD_ReadData();
}

void LCD_setCursor(int xpos, int ypos)
{
	LCD_WriteReg(0x0020, xpos);
	LCD_WriteReg(0x0021, ypos);
}

void LCD_WriteDataStart()
{
	SPI_WRITE(0x70 | 0x02);
}

void LCD_WriteDataOnly(int data)
{
	SPI_WRITE(data >> 8);
	SPI_WRITE(data & 0xff);
}

void LCD_Clear(int Color)
{
	uint32_t index=0;

	LCD_setCursor(0,0);

	LCD_WriteIndex(0x0022);

 	SPI_CS_LOW;
	LCD_WriteDataStart();

	for( index = 0; index < (uint32_t)MAX_X * MAX_Y; index++ )
	{
		LCD_WriteDataOnly(Color);
	}
	SPI_CS_HI;
}

int LCD_init()
{
	int v;
        GPIOB->OUT |= 0x100;
        DELAY_US(1000);
        GPIOB->OUT &= ~0x100;
        DELAY_US(5000);
        GPIOB->OUT |= 0x100;
        DELAY_US(20000);

        v = LCD_ReadReg(0x0);
        uart_send_str("LCD_ID=", UART3);
        uart_send_str(itoa(v, 16), UART3);
        uart_send_str("\r\n", UART3);
        if (v != 0x9320)
            return 0;

	LCD_WriteReg(0x00,0x0000);
	LCD_WriteReg(0x01,0x0100); /* Driver Output Contral */
	LCD_WriteReg(0x02,0x0700); /* LCD Driver Waveform Contral */
	LCD_WriteReg(0x03,0x1228); /* Set the scan mode */
	LCD_WriteReg(0x04,0x0000); /* Scalling Contral */
	LCD_WriteReg(0x08,0x0202); /* Display Contral 2 */
	LCD_WriteReg(0x09,0x0000); /* Display Contral 3 */
	LCD_WriteReg(0x0a,0x0000); /* Frame Cycle Contal */
	LCD_WriteReg(0x0c,(1<<0)); /* Extern Display Interface Contral 1 */
	LCD_WriteReg(0x0d,0x0000); /* Frame Maker Position */
	LCD_WriteReg(0x0f,0x0000); /* Extern Display Interface Contral 2 */

	LCD_WriteReg(0x07,0x0101); /* Display Contral */

	LCD_WriteReg(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4)); /* Power Control 1 */
	LCD_WriteReg(0x11,0x0007);                              /* Power Control 2 */
	LCD_WriteReg(0x12,(1<<8)|(1<<4)|(0<<0));                /* Power Control 3 */
	LCD_WriteReg(0x13,0x0b00);                              /* Power Control 4 */
	DELAY_US(200000);
	LCD_WriteReg(0x29,0x0000);                              /* Power Control 7 */
	LCD_WriteReg(0x2b,(1<<14)|(1<<4));

	LCD_WriteReg(48, 0x0007);
	LCD_WriteReg(49, 0x0302);
	LCD_WriteReg(50, 0x0105);
	LCD_WriteReg(53, 0x0206);
	LCD_WriteReg(54, 0x0808);
	LCD_WriteReg(55, 0x0206);
	LCD_WriteReg(56, 0x0504);
	LCD_WriteReg(57, 0x0007);
	LCD_WriteReg(60, 0x0105);
	LCD_WriteReg(61, 0x0808);

	LCD_WriteReg(0x50,0);       /* Set X Start */
	LCD_WriteReg(0x51,239);	    /* Set X End */
	LCD_WriteReg(0x52,0);	    /* Set Y Start */
	LCD_WriteReg(0x53,319);	    /* Set Y End */
	DELAY_US(50000);

	LCD_WriteReg(0x60,0x2700); /* Driver Output Control */
	LCD_WriteReg(0x61,0x0001); /* Driver Output Control */
	LCD_WriteReg(0x6a,0x0000); /* Vertical Srcoll Control */

	LCD_WriteReg(0x80,0x0000); /* Display Position? Partial Display 1 */
	LCD_WriteReg(0x81,0x0000); /* RAM Address Start? Partial Display 1 */
	LCD_WriteReg(0x82,0x0000); /* RAM Address End-Partial Display 1 */
	LCD_WriteReg(0x83,0x0000); /* Displsy Position? Partial Display 2 */
	LCD_WriteReg(0x84,0x0000); /* RAM Address Start? Partial Display 2 */
	LCD_WriteReg(0x85,0x0000); /* RAM Address End? Partial Display 2 */

	LCD_WriteReg(0x90,(0<<7)|(16<<0)); /* Frame Cycle Contral */
	LCD_WriteReg(0x92,0x0000);         /* Panel Interface Contral 2 */
	LCD_WriteReg(0x93,0x0001);         /* Panel Interface Contral 3 */
	LCD_WriteReg(0x95,0x0110);         /* Frame Cycle Contral */
	LCD_WriteReg(0x97,(0<<8));
	LCD_WriteReg(0x98,0x0000);         /* Frame Cycle Contral */
	LCD_WriteReg(0x07,0x0133);
	DELAY_US(50000);
	LCD_Clear(0x0000);

	return 1;
}

void LCD_SetPoint( unsigned int Xpos, unsigned int Ypos, unsigned int point)
{
#if 0
	if( Xpos >= MAX_X || Ypos >= MAX_Y )
	{
		return;
	}
#endif
	LCD_setCursor(Xpos,Ypos);
	LCD_WriteReg(0x0022,point);
}

void LCD_drawColorBMP(int x, int y, const tImage *image)
{
    int next = 0;
    const uint32_t *pdata = (const uint32_t *) image->data;

    int width;
    int i, k, cnt, size;
    int c, v;

    /* Ограничиваем область вывода для ускорения вывода */
	LCD_WriteReg(0x50,MAX_X - y - image->height - 1); // 80
	LCD_WriteReg(0x51,MAX_X - y );
	LCD_WriteReg(0x52,x);
	LCD_WriteReg(0x53,x + image->width - 1); // 47
	LCD_setCursor(MAX_X - y, x);

        uart_send_str("\r\nh=", UART3);
        uart_send_str(itoa(image->height, 10), UART3);
        uart_send_str(" w=", UART3);
        uart_send_str(itoa(image->width, 10), UART3);

	LCD_WriteIndex(0x0022);

 	SPI_CS_LOW;
	LCD_WriteDataStart();

	size = image->width * image->height;

#define NEXT_WORD 						\
		if (!next) 						\
		{								\
			c = (*pdata >> 16) & 0xffff;	\
		}								\
		else							\
		{								\
			c = *pdata & 0xffff;			\
			pdata++;					\
		}								\
		next ^= 1

	y = 0;
	width = 0;
	while (size > 0) {
		NEXT_WORD;
		if (c > 0x8000) {
			cnt = c - 0x8000;
			for (i = 0; i < cnt; i++, size--)
			{
				NEXT_WORD;
				LCD_WriteDataOnly(c);
			}
		} else {
			cnt = c;
			NEXT_WORD;
			for (i = 0; i < cnt; i++, size--)
			{
				LCD_WriteDataOnly(c);
			}
		}
	}

    SPI_CS_HI;
}

#if 1
void LCD_drawBMP(int x, int y, int fgColor, int bgColor, const tImage *image)
{
    int next = 0;
    const uint32_t *pdata = (const uint32_t *) image->data;

    int width;
    int i, k, cnt, size;
    int c, v;

    /* Ограничиваем область вывода для ускорения вывода */
	LCD_WriteReg(0x50,MAX_X - y - image->height - 1); // 80
	LCD_WriteReg(0x51,MAX_X - y );
	LCD_WriteReg(0x52,x);
	LCD_WriteReg(0x53,x + image->width - 1); // 47
	LCD_setCursor(MAX_X - y, x);

        uart_send_str("\r\nh=", UART3);
        uart_send_str(itoa(image->height, 10), UART3);
        uart_send_str(" w=", UART3);
        uart_send_str(itoa(image->width, 10), UART3);

	LCD_WriteIndex(0x0022);

 	SPI_CS_LOW;
	LCD_WriteDataStart();

	size = image->width * image->height;

#define NEXT_BYTE 						\
		if (!next) 						\
		{								\
			c = (*pdata >> 8) & 0xff;	\
		}								\
		else							\
		{								\
			c = *pdata & 0xff;			\
			pdata++;					\
		}								\
		next ^= 1

	y = 0;
	width = 0;
	while (size > 0) {
		NEXT_BYTE;
		if (c > 128) {
			cnt = c - 128;
			for (i = 0; i < cnt; i++)
			{
				NEXT_BYTE;
				if (width < 1) {
					width = image->width;
					y++;
				}
				for (k = 0; k < 8 && width > 0; k++, c <<= 1, size--, width--)
				{
					if ((c & 0x80) != 0)
						LCD_WriteDataOnly(fgColor);
					else
						LCD_WriteDataOnly(bgColor);
				}
			}
		} else {
			cnt = c;
			NEXT_BYTE;
			for (i = 0; i < cnt; i++)
			{
				v = c;
				if (width < 1) {
					width = image->width;
					y++;
				}
				for (k = 0; k < 8 && width > 0; k++, v <<= 1, size--, width--)
				{
					if ((v & 0x80) != 0)
						LCD_WriteDataOnly(fgColor);
					else
						LCD_WriteDataOnly(bgColor);
				}
			}
		}
	}

    SPI_CS_HI;
}
#endif

#if 0
void LCD_PlotLine( int y1, int x1, int y2, int x2 , unsigned int color, int len )
{
    int deltaX;
    int deltaY;
    int signX;
    int signY;
    int error;
    int cnt = 0;

    x1 = MAX_X - x1;
    x2 = MAX_X - x2;
    deltaX = abs(x2 - x1);
    deltaY = abs(y2 - y1);
    signX = x1 < x2 ? 1 : -1;
    signY = y1 < y2 ? 1 : -1;
    error = deltaX - deltaY;

    LCD_SetPoint(x2, y2, color);
    while(x1 != x2 || y1 != y2) {
        const int error2 = error * 2;
//        if (cnt++ > len)
        	LCD_SetPoint(x1, y1, color);
        //
        if (error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
}

void LCD_DrawLine( unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1 , unsigned int color )
{
    short dx,dy;      /* The definition of the X Y axis increase the value of the variable */
    short temp;

    if( x0 > x1 )
    {
	    temp = x1;
		x1 = x0;
		x0 = temp;
    }
    if( y0 > y1 )
    {
		temp = y1;
		y1 = y0;
		y0 = temp;
    }

	dx = x1-x0;
	dy = y1-y0;

    if( dx == 0 )
    {
        do
        {
            LCD_SetPoint(x0, y0, color);
            y0++;
        }
        while( y1 >= y0 );
		return;
    }
    if( dy == 0 )
    {
        do
        {
            LCD_SetPoint(x0, y0, color);
            x0++;
        }
        while( x1 >= x0 );
		return;
    }

    if( dx > dy )
    {
	    temp = 2 * dy - dx;
        while( x0 != x1 )
        {
	        LCD_SetPoint(x0,y0,color);
	        x0++;
	        if( temp > 0 )
	        {
	            y0++;
	            temp += 2 * dy - 2 * dx;
	 	    }
            else
            {
			    temp += 2 * dy;
			}
        }
        LCD_SetPoint(x0,y0,color);
    }
    else
    {
	    temp = 2 * dx - dy;
        while( y0 != y1 )
        {
	 	    LCD_SetPoint(x0,y0,color);
            y0++;
            if( temp > 0 )
            {
                x0++;
                temp+=2*dy-2*dx;
            }
            else
			{
                temp += 2 * dy;
			}
        }
        LCD_SetPoint(x0,y0,color);
	}
}
#endif

void LCD_DrawBar(const unsigned int x, const unsigned int y, const unsigned int w, const unsigned int h, const unsigned int color)
{
	int i;

	LCD_WriteReg(0x50,MAX_X - (y + h));
	LCD_WriteReg(0x51,MAX_X - y);
	LCD_WriteReg(0x52,x);
	LCD_WriteReg(0x53,x + w - 1);

	LCD_setCursor(MAX_X - y, x);

	LCD_WriteIndex(0x0022);

 	SPI_CS_LOW;
	LCD_WriteDataStart();

	for (i = w*h; i > 0; i--)
		LCD_WriteDataOnly(color);

	SPI_CS_HI;
}

void LCD_DrawCircle(unsigned int xMidPoint, unsigned int yMidPoint, int radius, unsigned int color)
{
    int f = 1 - radius;
    int ddF_x = 1;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;

    //Right middle
//    LCD_SetPoint(xMidPoint, yMidPoint + radius, color);

    //Left Middle
    LCD_SetPoint(xMidPoint, yMidPoint - radius, color);

    //Top Middle
    LCD_SetPoint(xMidPoint + radius, yMidPoint, 0xffe0);

    //Bottom Middle
//    LCD_SetPoint(xMidPoint - radius, yMidPoint, color);

    while( x < y )
    {
        if(f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        //Top Right
        if (x < (radius >> 3))
        {
//        	LCD_SetPoint(xMidPoint + x, yMidPoint + y, color);
        	LCD_SetPoint(xMidPoint + y, yMidPoint + x, 0xffe0);
        }

        //Lower Right
//        LCD_SetPoint(xMidPoint - x, yMidPoint + y, color);
//        LCD_SetPoint(xMidPoint - y, yMidPoint + x, color);

        //Top Left
        LCD_SetPoint(xMidPoint + x, yMidPoint - y, color);
        LCD_SetPoint(xMidPoint + y, yMidPoint - x, x < (radius >> 3) ? 0xffe0 : color);

        //Lower Left
        if (x < (radius >> 2))
        {
        	LCD_SetPoint(xMidPoint - x, yMidPoint - y, 0xf800);
//        	LCD_SetPoint(xMidPoint - y, yMidPoint - x, color);
        }
    }
}
