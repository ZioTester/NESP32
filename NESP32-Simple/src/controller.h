#pragma once

#include <Arduino.h>

extern "C" void controller_init();
extern "C" uint32_t controller_read_input();

