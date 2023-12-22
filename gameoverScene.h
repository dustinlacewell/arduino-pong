#pragma once

#include "src/state.h"
#include "src/score.h"
#include "src/walls.h"
#include "src/text.h"
#include "src/scene.h"


class GameoverScene : public Scene {
private:
    int leaderboardPos = -1;
public:
    void setup(void);
    void loop(unsigned long dt);
};
