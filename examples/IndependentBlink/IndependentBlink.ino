#include <ArduinoPatterns.h>

PeriodicOutput slowLed(9, 1000);
PeriodicOutput fastLed(10, 500);

void setup() {
  const uint32_t now = millis();
  slowLed.begin(now);
  fastLed.begin(now);
}

void loop() {
  const uint32_t now = millis();
  slowLed.update(now);
  fastLed.update(now);
}
