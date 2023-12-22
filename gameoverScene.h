#pragma once

#include <gamedev.h>

#include "src/state.h"
#include "src/score.h"
#include "src/walls.h"


class GameoverScene : public Scene {
private:
    int leaderboardPos = -1;
public:
    void setup(void);
    void loop(unsigned long dt);
};
