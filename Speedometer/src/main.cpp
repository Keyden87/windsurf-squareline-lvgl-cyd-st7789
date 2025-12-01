#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include "ui/ui.h"

// Touch Screen Pins (Standard CYD)
#define XPT_CS   33
#define XPT_IRQ  36
#define XPT_MOSI 32
#define XPT_MISO 39
#define XPT_CLK  25

SPIClass touchSpi(VSPI);
XPT2046_Touchscreen ts(XPT_CS, XPT_IRQ);
TFT_eSPI tft = TFT_eSPI();

// Screen dimensions
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 240;

// LVGL Draw Buffer
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 10];

// Display Flush Callback
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

// Touch Read Callback
void my_touch_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
    if (ts.touched()) {
        TS_Point p = ts.getPoint();
        // Calibration needed? Usually CYD needs some mapping.
        // Mapping 0-4096 to 0-320/240.
        // These values are approximate for CYD, might need tuning.
        // X: 200-3800, Y: 200-3800
        
        // Simple mapping for now, user can calibrate if needed.
        // Note: Touch coordinates might be inverted or swapped depending on rotation.
        // ST7789 usually Landscape.
        
        // Let's assume standard orientation for now.
        // Map raw values to screen coordinates.
        // This is a rough guess for CYD landscape.
        uint16_t touchX = map(p.x, 200, 3800, 0, screenWidth);
        uint16_t touchY = map(p.y, 200, 3800, 0, screenHeight);

        data->state = LV_INDEV_STATE_PR;
        data->point.x = touchX;
        data->point.y = touchY;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}

void setup() {
    Serial.begin(115200);

    // Init Touch SPI
    touchSpi.begin(XPT_CLK, XPT_MISO, XPT_MOSI, XPT_CS);
    ts.begin(touchSpi);
    ts.setRotation(1); // Adjust to match TFT rotation

    // Init TFT
    tft.begin();
    tft.setRotation(1); // Landscape
    
    // Backlight is handled by TFT_eSPI if defined in platformio.ini, 
    // but let's be explicit since user asked for it.
    pinMode(27, OUTPUT);
    digitalWrite(27, HIGH);

    // Init LVGL
    lv_init();
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * screenHeight / 10);

    // Init Display Driver
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    // Init Input Driver
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touch_read;
    lv_indev_drv_register(&indev_drv);

    // Init SquareLine UI
    ui_init();

    Serial.println("Setup done");
}

void loop() {
    lv_timer_handler();
    delay(5);
}
