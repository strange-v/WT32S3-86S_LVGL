#include <display_driver.h>

Point point;

void init_display_driver()
{
    bus = new Arduino_SWSPI(
        GFX_NOT_DEFINED, /* DC */
        TFT_CS,          /* CS */
        TFT_SCLK,        /* SCK or SCLK */
        TFT_MOSI,        /* MOSI */
        GFX_NOT_DEFINED  /* MISO */
    );
    panel = new Arduino_ESP32RGBPanel(
        TFT_DE,    /* DE */
        TFT_VSYNC, /* VSYNC */
        TFT_HSYNC, /* HSYNC */
        TFT_PCLK,  /* PCLK */
        TFT_D11,   /* R0 */
        TFT_D12,   /* R1 */
        TFT_D13,   /* R2 */
        TFT_D14,   /* R3 */
        TFT_D15,   /* R4 */
        TFT_D5,    /* G0 */
        TFT_D6,    /* G1 */
        TFT_D7,    /* G2 */
        TFT_D8,    /* G3 */
        TFT_D9,    /* G4 */
        TFT_D10,   /* G5 */
        TFT_D0,    /* B0 */
        TFT_D1,    /* B1 */
        TFT_D2,    /* B2 */
        TFT_D3,    /* B3 */
        TFT_D4,    /* B4 */
        1,         /* hsync_polarity */
        8,         /* hsync_front_porch */
        10,        /* hsync_pulse_width */
        50,        /* hsync_back_porch */
        1,         /* vsync_polarity */
        8,         /* vsync_front_porch */
        10,        /* vsync_pulse_width */
        20         /* vsync_back_porch */
    );
    gfx = new Arduino_RGB_Display(
        TFT_WIDTH,  /* width */
        TFT_HEIGHT, /* height */
        panel,
        0,    /* rotation */
        true, /* auto_flush (IPS, in makerfabs project it is IPS) */
        bus,
        41, /* RST */
        gc9503v_type1_init_operations,
        sizeof(gc9503v_type1_init_operations));

    gfx->begin();
    gfx->fillScreen(BLACK);

    ts.begin();
    ts.registerTouchHandler(on_touch);
}

/* Update TFT */
void IRAM_ATTR flush_pixels(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
    gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

    lv_disp_flush_ready(disp);
}

/* Read the touchpad */
void IRAM_ATTR touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    if (ts.touched())
    {
        ts.processTouch();

        data->point.x = point.x;
        data->point.y = point.y;
        data->state = LV_INDEV_STATE_PR;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
}

void on_touch(TPoint p, TEvent e)
{
  point.x = p.x;
  point.y = p.y;
}

void calibrate_touch()
{
    // if (lcd.touch())
    // {
    //     // Draw a guide text on the screen.
    //     lcd.setTextDatum(textdatum_t::middle_center);
    //     lcd.drawString("touch the arrow marker.", lcd.width() >> 1, lcd.height() >> 1);
    //     lcd.setTextDatum(textdatum_t::top_left);

    //     // If you use touch, calibrate. Touch the tips of the arrows displayed in the four corners of the screen in order.
    //     uint16_t data[8];
    //     lcd.calibrateTouch(data, TFT_WHITE, TFT_BLACK, std::max(lcd.width(), lcd.height()) >> 3);

    //     Serial.print("Calibration data: {");
    //     for (int i = 0; i < 8; ++i)
    //     {
    //         Serial.printf("%d, ", data[i]);
    //     }
    //     Serial.print("}\n");
    //     lcd.fillScreen(TFT_BLACK);
    // }
}