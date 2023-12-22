#pragma once

#include <gamedev.h>

#include "globals.h"
#include "text.h"

void drawScore()
{
    int digits = countDigits(score);

    int scoreX = g_width / 2 - (digits * 36) / 2;

    game->canvas->setTextSize(6);
    uint16_t color = floatToGreyscale16Bit(.4f);
    game->canvas->setTextColor(color);
    game->canvas->setCursor(scoreX, g_height / 2 - 20);
    game->canvas->print(score);
}