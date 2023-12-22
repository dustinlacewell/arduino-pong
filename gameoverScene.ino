#include "gameoverScene.h"
#include "gameplayScene.h"

#include "src/buttons.h"


void GameoverScene::setup(void)
{
    audio.play(LoseSound);
    this->leaderboardPos = leaderboard.submitScore(score);
}

void GameoverScene::loop(unsigned long dt)
{
    drawScore();

    if (this->leaderboardPos >= 0)
    {
        // say "New Highscore!" centered, towards the top, using arcada api
        int x = g_width / 2;
        int y = g_height / 4;
        drawCenteredText("New Highscore!", 1, x, y);
    }

    if (
        buttons.pressed(ARCADA_BUTTONMASK_A) ||
        buttons.pressed(ARCADA_BUTTONMASK_B) ||
        buttons.pressed(ARCADA_BUTTONMASK_START)
    )
    {
        reset();
        switchTo(new GameplayScene());
    }
}