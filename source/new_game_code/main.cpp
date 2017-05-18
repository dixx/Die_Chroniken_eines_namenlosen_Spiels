#include "leviathan.h"

int main()
{
    leviathan::LeviathanDevice gameEngine;
    gameEngine.init( "config.ini" );
    GameStatePlay play;
    gameEngine.GameStateManager().add( play, 1 );
    gameEngine.GameStateManager().transitTo( 1 );
    // gameEngine.run();
    return 0; // gameEngine.exitStatus();
}
