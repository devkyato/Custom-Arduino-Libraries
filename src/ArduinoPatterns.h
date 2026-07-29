#pragma once

#include <Arduino.h>

#include <stddef.h>
#include <stdint.h>

struct PatternStep {
  uint32_t mask;
  uint32_t durationMs;
};

class LedBank {
 public:
  static constexpr size_t kMaximumPins = 32;

  LedBank(const uint8_t* pins, size_t count, bool activeHigh = true);

  void begin();
  void writeMask(uint32_t mask);
  void clear();

  size_t size() const;
  uint32_t mask() const;
  bool valid() const;

 private:
  const uint8_t* pins_;
  size_t count_;
  bool activeHigh_;
  uint32_t mask_;
};

class LedAnimator {
 public:
  LedAnimator(LedBank& bank, const PatternStep* steps, size_t count,
              bool repeat = true);

  bool start(uint32_t now);
  void stop(bool clearOutputs = true);
  bool update(uint32_t now);
  void setRepeat(bool repeat);

  bool running() const;
  size_t currentStep() const;

 private:
  LedBank& bank_;
  const PatternStep* steps_;
  size_t count_;
  bool repeat_;
  bool running_;
  size_t current_;
  uint32_t changedAt_;

  void advance(uint32_t now);
};

class PeriodicOutput {
 public:
  PeriodicOutput(uint8_t pin, uint32_t intervalMs, bool activeHigh = true,
                 bool initialState = false);

  void begin(uint32_t now);
  bool update(uint32_t now);
  void setInterval(uint32_t intervalMs, uint32_t now);
  void set(bool active, uint32_t now);

  bool active() const;
  uint32_t interval() const;

 private:
  uint8_t pin_;
  uint32_t intervalMs_;
  bool activeHigh_;
  bool state_;
  uint32_t changedAt_;

  void write();
};
