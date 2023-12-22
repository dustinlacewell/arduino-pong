#include "gameplayScene.h"
#include "gameoverScene.h"

void GameplayScene::setup(void) {}

void GameplayScene::loop(unsigned long dt)
{
    ball.update(dt);
    paddle.update(dt);

    if (ball.x < -100)
    {
        switchTo(new GameoverScene());
    }

    collision.checkAndResolveCollision(ball, paddle, PaddleSide::LEFT);

    drawScore();
    ball.draw();
    paddle.draw();
    drawWalls();
}