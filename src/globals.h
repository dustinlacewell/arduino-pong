#pragma once

#include <gamedev.h>

#include "enums.h"

Game* game;

uint32_t top = 1;
uint32_t bottom = g_height - 1;

uint32_t maxTop = g_height / 4;

Stage stage = Stage::TopBottomShrink;

uint32_t wall = g_width - 1;
uint32_t wallPauseRatio = .2f;

uint8_t score = 0;
