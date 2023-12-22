#pragma once

#include "globals.h"

void drawWalls() {
        game->canvas->drawFastHLine(0, top, g_width, 0xFFFF);
        game->canvas->drawFastHLine(0, bottom, g_width, 0xFFFF);
        game->canvas->drawFastVLine(wall, bottom, top - bottom, 0xFFFF);    
}