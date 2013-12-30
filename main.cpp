#include "GameFloatControl.h"
#include "Constants.h"

int main()
{
    GameFloatControl& game = GameFloatControl::getInstance();
    if ( game.start() == FAILED )
        return 1;
    game.run();
    game.stop();
    return 0;
}
