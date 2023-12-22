#pragma once

#include "Adafruit_Arcada.h"

#include "enums.h"

Adafruit_Arcada arcada;

GFXcanvas16 *g_canvas;

uint8_t g_width = 160;
uint8_t g_height = 128;

uint32_t top = 1;
uint32_t bottom = g_height - 1;

uint32_t maxTop = g_height / 4;

Stage stage = Stage::TopBottomShrink;

uint32_t wall = g_width - 1;
uint32_t wallPauseRatio = .2f;

uint8_t score = 0;

bool muted = false;
