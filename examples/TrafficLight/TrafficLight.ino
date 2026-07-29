#include <ArduinoPatterns.h>

// Pins are ordered green, yellow, red; bit 0 maps to the first pin.
const uint8_t pins[] = {6, 7, 8};
const PatternStep phases[] = {
    {0b001, 5000},
    {0b010, 2000},
    {0b100, 5000},
};

LedBank trafficLights(pins, sizeof(pins));
LedAnimator traffic(trafficLights, phases,
                    sizeof(phases) / sizeof(phases[0]));

void setup() {
  trafficLights.begin();
  traffic.start(millis());
}

void loop() { traffic.update(millis()); }
