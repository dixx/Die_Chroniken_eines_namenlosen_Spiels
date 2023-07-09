#include "GameStateLoadGame.h"
#include "defines.h"
#include <ILeviathanDevice.h>
#include <characters/IHero.h>
#include <characters/IHeroes.h>
#include <core/IGameStateManager.h>
#include <video/ICamera.h>
#include <world/IGround.h>
#include <world/Node3DConfiguration.h>

GameStateLoadGame::GameStateLoadGame(leviathan::ILeviathanDevice& gameEngine) : mGameEngine(gameEngine) {}

GameStateLoadGame::~GameStateLoadGame() {}

void GameStateLoadGame::update(const float elapsedSeconds) {
    (void)elapsedSeconds;
    if (!mFullyLoaded) {
        mGameEngine.Ground().add(
            {"gfx/landscape_river_10.obj", "gfx/brushed_terrain.png", {}, {}, {}, {}, {100.001f, 100.0f, 100.001f}});
        auto startingPosition = leviathan::video::Position3D(
            {11.f, mGameEngine.Ground().getHeight({11.f, 0.f, 11.f}), 11.f});
        mGameEngine.Heroes().getActiveHero().setRotation({0.f, 0.f, 0.f});
        mGameEngine.Heroes().getActiveHero().setPosition(startingPosition);
        mGameEngine.Camera().setTargetPosition(startingPosition);
        mGameEngine.Camera().update(0.f);
        mGameEngine.GameStateManager().transitTo(STATE_PLAY);
        mFullyLoaded = true;
    } else {
        mGameEngine.Ground().unload();
        mGameEngine.GameStateManager().transitTo(STATE_MAIN_MENU);
        mFullyLoaded = false;
    }
}

void GameStateLoadGame::draw() {}
