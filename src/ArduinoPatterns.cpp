#include "ArduinoPatterns.h"

LedBank::LedBank(const uint8_t* pins, size_t count, bool activeHigh)
    : pins_(pins),
      count_(count <= kMaximumPins ? count : 0),
      activeHigh_(activeHigh),
      mask_(0) {}

void LedBank::begin() {
  if (!valid()) {
    return;
  }
  for (size_t index = 0; index < count_; ++index) {
    pinMode(pins_[index], OUTPUT);
  }
  clear();
}

void LedBank::writeMask(uint32_t mask) {
  if (!valid()) {
    return;
  }
  const uint32_t bounded =
      count_ == kMaximumPins ? mask : mask & ((uint32_t{1} << count_) - 1);
  for (size_t index = 0; index < count_; ++index) {
    const bool active = (bounded & (uint32_t{1} << index)) != 0;
    digitalWrite(pins_[index], active == activeHigh_ ? HIGH : LOW);
  }
  mask_ = bounded;
}

void LedBank::clear() { writeMask(0); }

size_t LedBank::size() const { return count_; }

uint32_t LedBank::mask() const { return mask_; }

bool LedBank::valid() const { return pins_ != nullptr && count_ > 0; }

LedAnimator::LedAnimator(LedBank& bank, const PatternStep* steps, size_t count,
                         bool repeat)
    : bank_(bank),
      steps_(steps),
      count_(count),
      repeat_(repeat),
      running_(false),
      current_(0),
      changedAt_(0) {}

bool LedAnimator::start(uint32_t now) {
  if (!bank_.valid() || steps_ == nullptr || count_ == 0) {
    running_ = false;
    return false;
  }
  current_ = 0;
  changedAt_ = now;
  running_ = true;
  bank_.writeMask(steps_[current_].mask);
  return true;
}

void LedAnimator::stop(bool clearOutputs) {
  running_ = false;
  if (clearOutputs) {
    bank_.clear();
  }
}

bool LedAnimator::update(uint32_t now) {
  if (!running_) {
    return false;
  }

  bool changed = false;
  while (running_ && static_cast<uint32_t>(now - changedAt_) >=
                         steps_[current_].durationMs) {
    const uint32_t duration = steps_[current_].durationMs;
    changedAt_ += duration;
    advance(now);
    changed = true;
    if (duration == 0) {
      changedAt_ = now;
      break;
    }
  }
  return changed;
}

void LedAnimator::setRepeat(bool repeat) { repeat_ = repeat; }

bool LedAnimator::running() const { return running_; }

size_t LedAnimator::currentStep() const { return current_; }

void LedAnimator::advance(uint32_t now) {
  if (current_ + 1 < count_) {
    ++current_;
    bank_.writeMask(steps_[current_].mask);
    return;
  }
  if (repeat_) {
    current_ = 0;
    bank_.writeMask(steps_[current_].mask);
    return;
  }
  running_ = false;
  changedAt_ = now;
}

PeriodicOutput::PeriodicOutput(uint8_t pin, uint32_t intervalMs,
                               bool activeHigh, bool initialState)
    : pin_(pin),
      intervalMs_(intervalMs),
      activeHigh_(activeHigh),
      state_(initialState),
      changedAt_(0) {}

void PeriodicOutput::begin(uint32_t now) {
  pinMode(pin_, OUTPUT);
  changedAt_ = now;
  write();
}

bool PeriodicOutput::update(uint32_t now) {
  if (intervalMs_ == 0 ||
      static_cast<uint32_t>(now - changedAt_) < intervalMs_) {
    return false;
  }
  const uint32_t elapsed = static_cast<uint32_t>(now - changedAt_);
  const uint32_t periods = elapsed / intervalMs_;
  changedAt_ += periods * intervalMs_;
  if ((periods & 1U) != 0) {
    state_ = !state_;
    write();
  }
  return true;
}

void PeriodicOutput::setInterval(uint32_t intervalMs, uint32_t now) {
  intervalMs_ = intervalMs;
  changedAt_ = now;
}

void PeriodicOutput::set(bool active, uint32_t now) {
  state_ = active;
  changedAt_ = now;
  write();
}

bool PeriodicOutput::active() const { return state_; }

uint32_t PeriodicOutput::interval() const { return intervalMs_; }

void PeriodicOutput::write() {
  digitalWrite(pin_, state_ == activeHigh_ ? HIGH : LOW);
}
