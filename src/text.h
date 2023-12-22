#pragma once

#include "globals.h"

int countDigits(int number)
{
    int digits = 1;
    if (number > 9)
        digits = 2;
    if (number > 99)
        digits = 3;
    if (number > 999)
        digits = 4;
    if (number > 9999)
        digits = 5;
    return digits;
}

void drawCenteredText(const String &text, int size, int x, int y) {
  int16_t x1, y1;
  uint16_t w, h;

  // Temporarily set the text size to calculate the width and height
  g_canvas->setTextSize(size);
  g_canvas->getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

  // Calculate the starting position (top-left corner) for the text
  int16_t startX = x - (w / 2);
  int16_t startY = y - (h / 2) - y1; // Adjust for the height above the baseline

  // Set the cursor to the starting position
  g_canvas->setCursor(startX, startY);

  // Draw the text on the screen
  g_canvas->print(text);
}