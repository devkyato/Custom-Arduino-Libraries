#include <ArduinoPatterns.h>

const uint8_t pins[] = {6, 7, 8, 9, 10, 11};
const PatternStep steps[] = {
    {0b010101, 500},
    {0b101010, 1000},
    {0b000111, 1000},
    {0b111000, 1000},
    {0b100001, 1500},
    {0b010010, 1500},
    {0b001100, 1500},
};

LedBank lights(pins, sizeof(pins));
LedAnimator animation(lights, steps, sizeof(steps) / sizeof(steps[0]));

void setup() {
  lights.begin();
  animation.start(millis());
}

void loop() { animation.update(millis()); }
