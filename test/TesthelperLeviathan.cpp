#include "TesthelperLeviathan.h"

namespace TesthelperLeviathan
{
    GameStateSub::GameStateSub() : isDrawn(false), isUpdated(false), delta(0.0f)
    {
    }

    void GameStateSub::draw()
    {
        isDrawn = true;
    }

    void GameStateSub::update( const irr::f32 seconds )
    {
        isUpdated = true;
        delta = seconds;
    }
}
