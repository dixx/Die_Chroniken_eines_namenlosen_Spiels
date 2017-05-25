#ifndef _TESTHELPER_GAME_STATE_HEADER
#define _TESTHELPER_GAME_STATE_HEADER

#include "leviathan.h"

namespace TesthelperGameState
{
    class GameStateSub final: public leviathan::core::GameState
    {
    public:
        bool isDrawn, isUpdated;
        irr::f32 delta;
        GameStateSub();
        void draw() final;
        void update( const irr::f32 seconds ) final;
    };
}

#endif
