#include <ArduinoPatterns.h>

#include <cassert>
#include <climits>
#include <cstring>

namespace {
uint8_t modes[256];
uint8_t values[256];
uint32_t fakeMillis;
}  // namespace

void pinMode(uint8_t pin, uint8_t mode) { modes[pin] = mode; }

void digitalWrite(uint8_t pin, uint8_t value) { values[pin] = value; }

uint32_t millis() { return fakeMillis; }

void resetFakes() {
  std::memset(modes, 0, sizeof(modes));
  std::memset(values, 0, sizeof(values));
  fakeMillis = 0;
}

void test_led_bank_initializes_and_writes_masks() {
  resetFakes();
  const uint8_t pins[] = {2, 4, 7};
  LedBank bank(pins, 3);
  assert(bank.valid());

  bank.begin();
  assert(modes[2] == OUTPUT);
  assert(values[2] == LOW);

  bank.writeMask(0b101);
  assert(values[2] == HIGH);
  assert(values[4] == LOW);
  assert(values[7] == HIGH);
  assert(bank.mask() == 0b101);

  bank.writeMask(0xFFFFFFFF);
  assert(bank.mask() == 0b111);
}

void test_led_bank_supports_active_low_outputs() {
  resetFakes();
  const uint8_t pins[] = {3};
  LedBank bank(pins, 1, false);
  bank.begin();
  assert(values[3] == HIGH);
  bank.writeMask(1);
  assert(values[3] == LOW);
}

void test_animator_advances_without_delay_and_catches_up() {
  resetFakes();
  const uint8_t pins[] = {2, 3};
  const PatternStep steps[] = {{0b01, 10}, {0b10, 20}, {0b11, 30}};
  LedBank bank(pins, 2);
  LedAnimator animation(bank, steps, 3);
  bank.begin();

  assert(animation.start(100));
  assert(bank.mask() == 0b01);
  assert(!animation.update(109));
  assert(animation.update(130));
  assert(bank.mask() == 0b11);
  assert(animation.currentStep() == 2);
}

void test_animator_handles_millis_rollover() {
  resetFakes();
  const uint8_t pins[] = {2};
  const PatternStep steps[] = {{0, 10}, {1, 10}};
  LedBank bank(pins, 1);
  LedAnimator animation(bank, steps, 2, false);
  bank.begin();

  animation.start(UINT32_MAX - 5);
  assert(animation.update(4));
  assert(bank.mask() == 1);
}

void test_non_repeating_animation_stops() {
  resetFakes();
  const uint8_t pins[] = {2};
  const PatternStep steps[] = {{1, 5}, {0, 5}};
  LedBank bank(pins, 1);
  LedAnimator animation(bank, steps, 2, false);
  bank.begin();
  animation.start(0);

  animation.update(10);
  assert(!animation.running());
  assert(bank.mask() == 0);
}

void test_periodic_output_handles_skipped_periods() {
  resetFakes();
  PeriodicOutput output(9, 100, true, false);
  output.begin(0);
  assert(values[9] == LOW);

  assert(output.update(100));
  assert(output.active());
  assert(output.update(300));
  assert(output.active());
  assert(output.update(400));
  assert(!output.active());
}

int main(int, char**) {
  test_led_bank_initializes_and_writes_masks();
  test_led_bank_supports_active_low_outputs();
  test_animator_advances_without_delay_and_catches_up();
  test_animator_handles_millis_rollover();
  test_non_repeating_animation_stops();
  test_periodic_output_handles_skipped_periods();
  return 0;
}
