#include "display.h"
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void displayInit() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
}

void drawBitmap(uint16_t *data, int w, int h) {
    tft.pushImage(0, 0, w, h, data);
}