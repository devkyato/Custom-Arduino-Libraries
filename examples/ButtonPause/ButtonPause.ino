#include <ArduinoPatterns.h>

// Pause and resume a scanning animation with a momentary button on pin 2.
// The button uses INPUT_PULLUP; press to ground.

const uint8_t pins[] = {6, 7, 8, 9};
const PatternStep steps[] = {
    {0b0001, 120},
    {0b0010, 120},
    {0b0100, 120},
    {0b1000, 120},
    {0b0100, 120},
    {0b0010, 120},
};

LedBank lights(pins, 4);
LedAnimator scanner(lights, steps, 6);
const uint8_t kPauseButton = 2;
bool previousPressed = false;

void setup() {
  pinMode(kPauseButton, INPUT_PULLUP);
  lights.begin();
  scanner.start(millis());
}

void loop() {
  const uint32_t now = millis();
  const bool pressed = digitalRead(kPauseButton) == LOW;
  if (pressed && !previousPressed) {
    if (scanner.running()) {
      scanner.stop(false);
    } else {
      scanner.start(now);
    }
  }
  previousPressed = pressed;
  scanner.update(now);
}
