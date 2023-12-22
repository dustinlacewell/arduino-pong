#pragma once

#include "globals.h"

void drawWalls() {
        g_canvas->drawFastHLine(0, top, g_width, 0xFFFF);
        g_canvas->drawFastHLine(0, bottom, g_width, 0xFFFF);
        g_canvas->drawFastVLine(wall, bottom, top - bottom, 0xFFFF);    
}