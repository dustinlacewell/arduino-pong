#pragma once

#include <gamedev.h>

#include "src/state.h"
#include "src/score.h"
#include "src/walls.h"


class GameplayScene : public Scene {
public:
    void setup(void);
    void loop(unsigned long dt);
};

