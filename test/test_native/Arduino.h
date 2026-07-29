#pragma once

#include <stddef.h>
#include <stdint.h>

#define LOW 0x0
#define HIGH 0x1
#define OUTPUT 0x1

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t value);
uint32_t millis();
