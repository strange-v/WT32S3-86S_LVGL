#ifndef DISPLAY_DRIVER_H
#define DISPLAY_DRIVER_H

#define SPI_FREQUENCY 15000000

#define TFT_WIDTH 480
#define TFT_HEIGHT 480
#define TFT_BCKL 5
#define TFT_CS 38
#define TFT_SCLK 45
#define TFT_MOSI 48
#define TFT_DE 40
#define TFT_VSYNC 41
#define TFT_HSYNC 42
#define TFT_PCLK 39
#define TFT_D0 45
#define TFT_D1 48
#define TFT_D2 47
#define TFT_D3 0
#define TFT_D4 21
#define TFT_D5 14
#define TFT_D6 13
#define TFT_D7 12
#define TFT_D8 11
#define TFT_D9 16
#define TFT_D10 17
#define TFT_D11 18
#define TFT_D12 8
#define TFT_D13 3
#define TFT_D14 46
#define TFT_D15 10
#define BACKLIGHT_FREQUENCY 1000

#define I2C_TOUCH_FREQUENCY 400000
#define TOUCH_SDA 15
#define TOUCH_SCL 6
#define TOUCH_IRQ 4
#define TOUCH_RST -1

#define LGFX_USE_V1 1

#include <Arduino.h>
#include <lvgl.h>
#include <Arduino_GFX_Library.h>
#include <FT6X36.h>

struct Point
{
    uint16_t x;
    uint16_t y;
};

extern Arduino_DataBus *bus;
extern Arduino_ESP32RGBPanel *panel;
extern Arduino_RGB_Display *gfx;
extern FT6X36 ts;

void init_display_driver();
void IRAM_ATTR flush_pixels(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p);
void IRAM_ATTR touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
void on_touch(TPoint p, TEvent e);
void calibrate_touch();

#endif //DISPLAY_DRIVER_H