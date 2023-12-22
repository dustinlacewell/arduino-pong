#pragma once

#include "globals.h"
#include "ball.h"
#include "paddle.h"
#include "collision.h"
#include "files.h"
#include "leaderboard.h"

Ball ball = Ball(g_width - g_width / 4, g_height / 2, .1, .2, 4, .25);
Paddle paddle = Paddle(5, 100, 3, 25, 10);
Collision collision = Collision();

LeaderboardManager leaderboard = LeaderboardManager();


void reset() {
    ball = Ball(g_width - g_width / 4, g_height / 2, .2, .1, 4, .25);
    paddle = Paddle(5, 100, 3, 25, 10);
    score = 0;
    top = 1;
    bottom = g_height - 1;    
    wall = g_width - 1;
    stage = Stage::TopBottomShrink;
}
