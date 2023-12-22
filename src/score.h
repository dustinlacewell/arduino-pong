#pragma once

#include "globals.h"
#include "text.h"
#include "colors.h"

void drawScore()
{
    int digits = countDigits(score);

    int scoreX = g_width / 2 - (digits * 36) / 2;

    g_canvas->setTextSize(6);
    uint16_t color = floatToGreyscale16Bit(.4f);
    g_canvas->setTextColor(color);
    g_canvas->setCursor(scoreX, g_height / 2 - 20);
    g_canvas->print(score);
}