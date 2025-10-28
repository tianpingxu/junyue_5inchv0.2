#ifndef __LCD_EX_H_
#define __LCD_EX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "lcd_interface.h"

#define DriverIC_COLOR(r, g, b) (((r & 0x1F) << 11) | ((g & 0x3F) << 5) | ((b & 0x1F) << 0))
#define COLOR_WHITE             DriverIC_COLOR(0xFF, 0xFF, 0xFF)
#define COLOR_BLACK             DriverIC_COLOR(0, 0, 0)
#define COLOR_RED               DriverIC_COLOR(0x8F, 0, 0)
#define COLOR_GREEN             DriverIC_COLOR(0, 0x8F, 0)
#define COLOR_BLUE              DriverIC_COLOR(0, 0, 0xFF)
#define COLOR_YELLOW            DriverIC_COLOR(0x8f, 0x8F, 0X00)


void lcd_show_string(lcd_handle_t *itf ,uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p, uint16_t color);

#ifdef __cplusplus
 }
#endif
#endif 
