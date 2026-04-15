#include <Arduino.h>
#include "display.h"
#include "serial.h"

void setup() {
    displayInit();
    serialInit();

    // Test screen
    delay(500);
}

void loop() {
    serialLoop();
}