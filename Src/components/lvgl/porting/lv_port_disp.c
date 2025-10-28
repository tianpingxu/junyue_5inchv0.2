/**
 * @file lv_port_disp_templ.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp.h"
#include <stdbool.h>
#include "lvgl_test.h"
#include <stdint.h>
#include <string.h>
#include "cmsis_armclang.h"
#include "lcd_interface.h"
extern lcd_handle_t lcd_dev;
/*********************
 *      DEFINES
 *********************/
#ifndef MY_DISP_HOR_RES
//    #warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen width, default value 480 is used for now.
#define MY_DISP_HOR_RES LV_CCORE_WIDTH
#endif

#ifndef MY_DISP_VER_RES
// #warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen height, default value 320 is used for now.
#define MY_DISP_VER_RES LV_CCORE_HEIGHT
#endif

#if DISPLAY_RGB565
#define BYTE_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565)) /*will be 2 for RGB565 */
#elif DISPLAY_RGB888
#define BYTE_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB888)) /*will be 3 for RGB888 */
#elif DISPLAY_ARGB8888
#define BYTE_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_ARGB8888)) /*will be 4 for ARGB8888 */
#endif

#if LV_CCORE_RENDER_MODE_PARTIAL
LV_ATTRIBUTE_MEM_ALIGN
uint8_t buf_1_1[MY_DISP_HOR_RES * MY_DISP_VER_RES * BYTE_PER_PIXEL] __attribute__((section("EXRAM2")));            //(MY_DISP_VER_RES可定义)
#endif


#if LV_CCORE_RENDER_MODE_FULL
LV_ATTRIBUTE_MEM_ALIGN
uint8_t buf_3_1[MY_DISP_HOR_RES * MY_DISP_VER_RES * BYTE_PER_PIXEL] __attribute__((section("EXRAM2")));

LV_ATTRIBUTE_MEM_ALIGN
uint8_t buf_3_2[MY_DISP_HOR_RES * MY_DISP_VER_RES * BYTE_PER_PIXEL] __attribute__((section("EXRAM2")));
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);
// static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
//         const lv_area_t * fill_area, lv_color_t color);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/
    disp_init();

    /*------------------------------------
     * Create a display and set a flush_cb
     * -----------------------------------*/
    lv_display_t *disp = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_display_set_flush_cb(disp, disp_flush);

    /* Example 1
     * One buffer for partial rendering*/
    // LV_ATTRIBUTE_MEM_ALIGN
    // static uint8_t buf_1_1[MY_DISP_HOR_RES * 10 * BYTE_PER_PIXEL];            /*A buffer for 10 rows*/
#if LV_CCORE_RENDER_MODE_PARTIAL    
    lv_display_set_buffers(disp, buf_1_1, NULL, sizeof(buf_1_1), LV_DISPLAY_RENDER_MODE_PARTIAL);
#endif
    /* Example 2
     * Two buffers for partial rendering
     * In flush_cb DMA or similar hardware should be used to update the display in the background.*/
    // lv_display_set_buffers(disp, buf_2_1, buf_2_2, sizeof(buf_2_1), LV_DISPLAY_RENDER_MODE_PARTIAL);

    /* Example 3
     * Two buffers screen sized buffer for double buffering.
     * Both LV_DISPLAY_RENDER_MODE_DIRECT and LV_DISPLAY_RENDER_MODE_FULL works, see their comments*/
#if LV_CCORE_RENDER_MODE_FULL
    lv_display_set_buffers(disp, buf_3_1, buf_3_2, sizeof(buf_3_1), LV_DISPLAY_RENDER_MODE_FULL);
#endif
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    /*You code here*/
}

volatile bool disp_flush_enabled = true;

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void)
{
    disp_flush_enabled = true;
}

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void)
{
    disp_flush_enabled = false;
}

/*Flush the content of the internal buffer the specific area on the display
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_disp_flush_ready()' has to be called when finished.*/
static void disp_flush(lv_display_t *disp_drv, const lv_area_t *area, uint8_t *px_map)
{
    //    if(disp_flush_enabled) {
    //        /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/
    //                static int i=0;
    //        int32_t x;
    //        int32_t y;
    //                printf("\r\n\r\n");
    //        for(y = area->y1; y <= area->y2; y++) {
    //            for(x = area->x1; x <= area->x2; x++) {
    //                /*Put a pixel to the display. For example:*/
    //                /*put_px(x, y, *color_p)*/
    //                                printf("%d:%d=%x\r\n", x, y, *color_p);
    //                color_p++;
    //            }
    //        }
    //    }

    // to add LVGL DISP color
    if (disp_flush_enabled)
    {
        lcd_write_dots(&lcd_dev, area->x1, area->y1, area->x2, area->y2, (uint8_t *)px_map);
        //    LVGL_DISP_Color_Fill(area->x1, area->y1, area->x2, area->y2, (uint16_t*)color_p);
    }

    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_display_flush_ready(disp_drv);
}


/*OPTIONAL: GPU INTERFACE*/

/*If your MCU has hardware accelerator (GPU) then you can use it to fill a memory with a color*/
// static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
//                     const lv_area_t * fill_area, lv_color_t color)
//{
//     /*It's an example code which should be done by your GPU*/
//     int32_t x, y;
//     dest_buf += dest_width * fill_area->y1; /*Go to the first line*/
//
//     for(y = fill_area->y1; y <= fill_area->y2; y++) {
//         for(x = fill_area->x1; x <= fill_area->x2; x++) {
//             dest_buf[x] = color;
//         }
//         dest_buf+=dest_width;    /*Go to the next line*/
//     }
// }

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
