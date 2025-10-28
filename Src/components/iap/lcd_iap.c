#include "lcd_iap.h"
#include "lcd_font.h"
#include <stdint.h>

static uint32_t g_back_color  = COLOR_BLACK;//0XFFFF; 

static lcd_status_t lcd_draw_point(lcd_handle_t *itf ,uint16_t x, uint16_t y, uint16_t color)
{
    lcd_status_t res = LCD_OK;
    if(itf->writedots == NULL)
    {
        res = LCD_ERR;
        return res;
    }
    itf->writedots(x,y,x,y,(uint16_t*)&color);
    return res;
}

static void lcd_show_char(lcd_handle_t *itf ,uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode, uint16_t color)
{
    uint8_t temp, t1, t;
    uint16_t y0 = y;
    uint8_t csize = 0;
    uint8_t *pfont = 0;

    csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);
    chr = chr - ' ';
    switch (size)
    {
        case 12: pfont = (uint8_t *)asc2_1206[chr]; break;
        case 16: pfont = (uint8_t *)asc2_1608[chr]; break;
        case 24: pfont = (uint8_t *)asc2_2412[chr]; break;
        case 32: pfont = (uint8_t *)asc2_3216[chr]; break;
        default: return;
    }
    for (t = 0; t < csize; t++)
    {
        temp = pfont[t];
        for (t1 = 0; t1 < 8; t1++)
        {
            if (temp & 0x80) {
                lcd_draw_point(itf,x, y, color);
            }else if (mode == 0) {
                lcd_draw_point(itf,x, y, g_back_color);
            }
            temp <<= 1;
            y++;
            if (y >= itf->lcd_size.y) return;
            if ((y - y0) == size) {
                y = y0;
                x++;
                if (x >= itf->lcd_size.x) return;
                break;
            }
        }
    }
}

void lcd_show_string(lcd_handle_t *itf ,uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p, uint16_t color)
{
    uint8_t x0 = x;
    width += x;
    height += y;
    while ((*p <= '~') && (*p >= ' '))
    {
        if (x >= width) {
            x = x0;
            y += size;
        }
        if (y >= height) break;
        lcd_show_char(itf,x, y, *p, size, 0, color);
        x += size / 2;
        p++;
    }
}
