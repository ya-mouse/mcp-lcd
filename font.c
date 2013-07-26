#include <HDL51001_ccf.h>
#include <spi.h>

#include "font.h"
#include "lcd.h"

void draw_bitmap_mono_rle(int x, int y, uint32_t fgColor, uint32_t bgColor, const tImage *image)
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


const tChar *find_char_by_code(uint32_t code, const tFont *font)
{
    int count = font->length;
    int first = 0;
    int last = count - 1;
    int mid = 0;

    if (count > 0)
    {
        if ((code >= font->chars[0].code) && (code <= font->chars[count - 1].code))
        {
            while (last >= first)
            {
                mid = first + ((last - first) / 2);

                if (font->chars[mid].code < code)
                    first = mid + 1;
                else
                    if (font->chars[mid].code > code)
                        last = mid - 1;
                    else
                        break;
            }

            if (font->chars[mid].code == code)
                return (&font->chars[mid]);
        }
    }

    return (0);
}

int utf8_next_char(const char *str, int start, uint32_t *resultCode, int *nextIndex)
{
    int len = 0;
    int index = 0;
    unsigned char c;
    uint32_t code = 0;
    int result = 0;
    int skip = 0;

    *resultCode = 0;

    while (*(str + index) != 0)
    {
        index++;
    }

    len = index;
    *resultCode = 0;
    *nextIndex = -1;

    if (start >= 0 && start < len)
    {
        index = start;

        while (index < len)
        {
            c = *(str + index);
            index++;

            // msb
            if (skip == 0)
            {
                // if range 0x00010000-0x001fffff
                if ((c & 0xf8) == 0xf0)
                {
                    skip = 3;
                    code = c;
                }
                // if range 0x00000800-0x0000ffff
                else if ((c & 0xf0) == 0xe0)
                {
                    skip = 2;
                    code = c;
                }
                // if range 0x00000080-0x000007ff
                else if ((c & 0xe0) == 0xc0)
                {
                    skip = 1;
                    code = c;
                }
                // if range 0x00-0x7f
                else //if ((c & 0x80) == 0x00)
                {
                    skip = 0;
                    code = c;
                }
            }
            else // not msb
            {
                code = (uint32_t)code << 8;
                code |= c;
                skip--;
            }
            if (skip == 0)
            {
                // completed
                *resultCode = code;
                *nextIndex = index;
                result = 1;
                break;
            }
        }
    }
    return (result);
}

void FONT_draw_string(const char *str, int x, int y, uint32_t fgColor, uint32_t bgColor, const tFont *font)
{
    int index = 0;
    uint32_t code = 0;
    int x1;
    int width = 0;
    int nextIndex;
    const char *p = str;

    while (*p != '\0')
    {
        if (utf8_next_char(str, index, &code, &nextIndex) != 0)
        {
            const tChar *ch = find_char_by_code(code, font);
            if (ch != 0)
            	width += ch->image->width;
        }
        p++;
        index = nextIndex;
        if (nextIndex < 0)
            break;
    }

    p = str;
    index = 0;
    x1 = x - (width >> 1);
    if (x1 < 0)
    	x1 = 0;

    while (*p != '\0')
    {
        if (utf8_next_char(str, index, &code, &nextIndex) != 0)
        {
            const tChar *ch = find_char_by_code(code, font);
            if (ch != 0)
            {
                draw_bitmap_mono_rle(x1, y, fgColor, bgColor, ch->image);
                x1 += ch->image->width;
            }
        }
        p++;
        index = nextIndex;
        if (nextIndex < 0)
            break;
    }
}
