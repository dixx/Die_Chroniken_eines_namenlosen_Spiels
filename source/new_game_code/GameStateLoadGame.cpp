#include "GameStateLoadGame.h"
#include "defines.h"

GameStateLoadGame::GameStateLoadGame(leviathan::LeviathanDevice& gameEngine) : gameEngine_(gameEngine) {}

GameStateLoadGame::~GameStateLoadGame() {}

void GameStateLoadGame::update(const float elapsedSeconds) {
    (void)elapsedSeconds;
    if (fullyLoaded) {
        gameEngine_.GameStateManager().transitTo(STATE_MAIN_MENU);
        fullyLoaded = false;
    } else {
        gameEngine_.GameStateManager().transitTo(STATE_PLAY);
        fullyLoaded = true;
    }
}

void GameStateLoadGame::draw() {}

void GameStateLoadGame::setActive() {}

void GameStateLoadGame::setInactive() {}
