#include "serial.h"
#include "protocol.h"
#include "display.h"

#define MAX_PIXELS 16384  // 128x128 max

static uint16_t buffer[MAX_PIXELS];

static int indexPos = 0;
static int width = 0;
static int height = 0;

enum State {
    WAIT_SOF1,
    WAIT_SOF2,
    READ_W,
    READ_H,
    READ_DATA
};

State state = WAIT_SOF1;

void serialInit() {
    Serial.begin(115200);
}

void serialLoop() {
    while (Serial.available()) {
        uint8_t b = Serial.read();

        switch (state) {

        case WAIT_SOF1:
            if (b == SOF1) state = WAIT_SOF2;
            break;

        case WAIT_SOF2:
            if (b == SOF2) state = READ_W;
            else state = WAIT_SOF1;
            break;

        case READ_W:
            width = b;
            state = READ_H;
            break;

        case READ_H:
            height = b;
            indexPos = 0;
            state = READ_DATA;
            break;

        case READ_DATA:
            buffer[indexPos++] = (b << 8); // high byte first
            if (indexPos >= width * height) {
                drawBitmap(buffer, width, height);
                state = WAIT_SOF1;
            }
            break;
        }
    }
}