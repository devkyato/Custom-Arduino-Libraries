#include <ArduinoPatterns.h>

const uint8_t pins[] = {6, 7, 8, 9};
const PatternStep scan[] = {
    {0b0001, 180},
    {0b0010, 180},
    {0b0100, 180},
    {0b1000, 180},
    {0b0100, 180},
    {0b0010, 180},
};

LedBank lights(pins, sizeof(pins));
LedAnimator scanner(lights, scan, sizeof(scan) / sizeof(scan[0]));

void setup() {
  lights.begin();
  scanner.start(millis());
}

void loop() { scanner.update(millis()); }
