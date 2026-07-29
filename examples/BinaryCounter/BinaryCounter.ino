#include <ArduinoPatterns.h>

const uint8_t pins[] = {9, 8, 7, 6};  // least-significant bit first
LedBank bits(pins, sizeof(pins));

uint8_t value = 0;
uint32_t changedAt = 0;

void setup() {
  bits.begin();
  bits.writeMask(value);
}

void loop() {
  const uint32_t now = millis();
  if (static_cast<uint32_t>(now - changedAt) >= 1000) {
    changedAt += 1000;
    value = (value + 1) & 0x0F;
    bits.writeMask(value);
  }
}
