#include <gamedev.h>

#include "gameoverScene.h"
#include "gameplayScene.h"
#include "src/sounds/lose.h"


void GameoverScene::setup(void)
{
    game->audio->play(LoseSound);
    this->leaderboardPos = game->leaderboard->submitScore(score);
}

void GameoverScene::loop(unsigned long dt)
{
    drawScore();

    if (this->leaderboardPos >= 0)
    {
        // say "New Highscore!" centered, towards the top, using arcada api
        int x = g_width / 2;
        int y = g_height / 4;
        drawCenteredText(game->canvas, "New Highscore!", 1, x, y);
    }

    if (
        game->buttons->pressed(ARCADA_BUTTONMASK_A) ||
        game->buttons->pressed(ARCADA_BUTTONMASK_B) ||
        game->buttons->pressed(ARCADA_BUTTONMASK_START)
    )
    {
        reset();
        game->switchTo(new GameplayScene());
    }
}