#include <ArduinoPatterns.h>

const uint8_t pins[] = {6, 7, 8, 9, 10, 11};
const PatternStep countSteps[] = {
    {0b000001, 300},
    {0b000011, 300},
    {0b000111, 300},
    {0b001111, 300},
    {0b011111, 300},
    {0b111111, 300},
    {0b011111, 300},
    {0b001111, 300},
    {0b000111, 300},
    {0b000011, 300},
    {0b000001, 300},
    {0b000000, 300},
};

LedBank lights(pins, sizeof(pins));
LedAnimator counter(lights, countSteps,
                    sizeof(countSteps) / sizeof(countSteps[0]));

void setup() {
  lights.begin();
  counter.start(millis());
}

void loop() { counter.update(millis()); }
