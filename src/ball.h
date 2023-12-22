#pragma once

#include "globals.h"
#include "audioPlayer.h"

// Ball class for a pong game.
// This is a simple class that has a position, velocity, and radius.

class Ball {
    public:
        float x;
        float y;

        float dx;
        float dy;

        float radius;
        float maxSpeed;

        Ball(float x, float y, float dx, float dy, float radius, float maxSpeed) {
            this->x = x;
            this->y = y;
            this->dx = dx;
            this->dy = dy;
            this->radius = radius;
            this->maxSpeed = maxSpeed;
        }

        void update(float dt) {
            x += dx * dt;
            y += dy * dt;

            if (x >= wall - radius) {
                dx = -dx;
                x = wall - radius;
                score += 1;
                audio.play(KickSound);
            }

            if (y <= top + this->radius) {
                dy = -dy;
                y = top + this->radius;
                audio.play(KickSound);
            }

            if (y >= bottom - radius) {
                dy = -dy;
                y = bottom - radius;
                audio.play(KickSound);
            }
        }

        void draw() {
            g_canvas->fillCircle(x, y, radius, 0xFFFF);
        }
};

