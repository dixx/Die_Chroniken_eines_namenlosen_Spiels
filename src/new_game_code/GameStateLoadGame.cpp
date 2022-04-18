#include "GameStateLoadGame.h"
#include "defines.h"
#include <ILeviathanDevice.h>
#include <core/IGameStateManager.h>
#include <world/IGround.h>
#include <world/Node3DConfiguration.h>

GameStateLoadGame::GameStateLoadGame(leviathan::ILeviathanDevice& gameEngine) : gameEngine_(gameEngine) {}

GameStateLoadGame::~GameStateLoadGame() {}

void GameStateLoadGame::update(const float elapsedSeconds) {
    (void)elapsedSeconds;
    if (!fullyLoaded) {
        gameEngine_.Ground().add(
            {"gfx/landscape_river_10.obj", "gfx/brushed_terrain.png", {}, {}, {}, {100.001f, 100.0f, 100.001f}});
        gameEngine_.GameStateManager().transitTo(STATE_PLAY);
        fullyLoaded = true;
    } else {
        gameEngine_.Ground().unload();
        gameEngine_.GameStateManager().transitTo(STATE_MAIN_MENU);
        fullyLoaded = false;
    }
}

void GameStateLoadGame::draw() {}
