#ifndef _TESTHELPER_LEVIATHAN_HEADER
#define _TESTHELPER_LEVIATHAN_HEADER

#include "leviathan.h"

namespace TesthelperLeviathan
{
    class GameStateSub final: public leviathan::core::GameState
    {
    public:
        bool isDrawn, isUpdated;
        irr::f32 delta;
        GameStateSub();
        void draw() final;
        void update( const irr::f32 frameDeltaTime ) final;
    };
}

#endif
