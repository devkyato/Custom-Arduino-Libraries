# API reference

Include the library with:

```cpp
#include <ArduinoPatterns.h>
```

## `PatternStep`

```cpp
struct PatternStep {
  uint32_t mask;
  uint32_t durationMs;
};
```

Bit zero in `mask` controls the first pin in a `LedBank`. `durationMs` is the
time before advancing to the next step. A zero-duration step advances at most
once per `update()` call, preventing an infinite loop.

## `LedBank`

```cpp
LedBank(const uint8_t* pins, size_t count, bool activeHigh = true);
```

The caller owns the pin array and must keep it alive for as long as the bank is
used. A bank supports 1–32 pins. A larger count or null pin array creates an
invalid bank.

- `begin()` configures pins as outputs and clears them.
- `writeMask(mask)` writes the lowest `count` bits.
- `clear()` turns every logical output off.
- `size()`, `mask()`, and `valid()` inspect current state.

With `activeHigh = false`, a logical on state writes `LOW`, which is useful for
active-low relay and LED modules.

## `LedAnimator`

```cpp
LedAnimator(LedBank& bank, const PatternStep* steps, size_t count,
            bool repeat = true);
```

- `start(now)` selects step zero and returns whether the configuration is valid.
- `update(now)` catches up all elapsed non-zero-duration steps without blocking.
- `stop(clearOutputs)` stops playback and optionally clears the bank.
- `setRepeat(repeat)` changes end-of-sequence behavior.
- `running()` and `currentStep()` expose playback state.

Pass the current `millis()` value to `start()` and `update()`. Unsigned
subtraction makes elapsed-time checks safe across the `millis()` rollover.

## `PeriodicOutput`

```cpp
PeriodicOutput(uint8_t pin, uint32_t intervalMs,
               bool activeHigh = true, bool initialState = false);
```

- `begin(now)` configures and writes the initial state.
- `update(now)` processes elapsed intervals and reports whether any interval
  elapsed. When an even number was skipped, the final logical state is unchanged.
- `setInterval(intervalMs, now)` updates the period and restarts its timer.
- `set(active, now)` writes a logical state and restarts its timer.
- `active()` and `interval()` return the current configuration.

An interval of zero disables automatic toggling.
