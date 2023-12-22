#include <stdint.h>
#include <gamedev.h>
#include "Adafruit_Arcada.h"

#include "src/globals.h"
#include "gameplayScene.h"


int lastTime = 0;

void setup(void)
{
  game = new Game();
  game->setup();
  game->switchTo(new GameplayScene());
}

void loop()
{
  game->loop();
}