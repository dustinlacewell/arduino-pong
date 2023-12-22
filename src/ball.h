#pragma once

#include "globals.h"
#include "sounds/kick.h"

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
                game->audio->play(KickSound);
            }

            if (y <= top + this->radius) {
                dy = -dy;
                y = top + this->radius;
                game->audio->play(KickSound);
            }

            if (y >= bottom - radius) {
                dy = -dy;
                y = bottom - radius;
                game->audio->play(KickSound);
            }
        }

        void draw() {
            game->canvas->fillCircle(x, y, radius, 0xFFFF);
        }
};

