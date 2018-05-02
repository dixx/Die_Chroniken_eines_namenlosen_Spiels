#include "GameFloatControl.h"

int main()
{
    GameFloatControl& game = GameFloatControl::getInstance();
    game.run();
    return game.status();
}
