#include "Game/Game.h"

int main()
{
    Game& myGame = Game::getInstance();
    myGame.start();

    while (myGame.isRunning())
        myGame.run();

    myGame.exit();

    return 0;
}