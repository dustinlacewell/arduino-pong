#pragma once

#include "globals.h"

// Ball class for a pong game.
// This is a simple class that has a position, velocity, and radius.

class Paddle
{
public:
    float originalX;
    float x;
    float y;

    float wiggle;
    int wiggleRoom;

    int width;
    int height;

    Paddle(float x, float y, int width, int height, int wiggleRoom)
    {
        this->originalX = x;
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->wiggle = 0;
        this->wiggleRoom = wiggleRoom;
    }

    void update(float dt)
    {
        // joystick inputs range from -512 to 512
        // we want to map this to the screen size
        // but account for the size of the paddle
        int padY = arcada.readJoystickY();
        int padX = arcada.readJoystickX();
        // Ensure that the paddle stays within the screen bounds
        this->y = map(padY, -512, 512, 0, g_height - height);
        this->wiggle = map(padX, -512, 512, 0, wiggleRoom);
        this->x = this->originalX + this->wiggle;
    }

    void draw()
    {
        // draw the paddle
        // but clip it at `top` and `bottom`
        if (this->y < top) {
            g_canvas->fillRect(this->x, top, this->width, this->height - (top - this->y), 0xFFFF);
        } else if (this->y + this->height > bottom) {
            g_canvas->fillRect(this->x, this->y, this->width, this->height - ((this->y + this->height) - bottom), 0xFFFF);
        } else {
            g_canvas->fillRect(this->x, this->y, this->width, this->height, 0xFFFF);
        }
    }
};
