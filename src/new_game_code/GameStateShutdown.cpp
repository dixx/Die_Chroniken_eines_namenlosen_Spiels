#include "GameStateShutdown.h"
#include <ILeviathanDevice.h>

GameStateShutdown::GameStateShutdown(leviathan::ILeviathanDevice& gameEngine) : mGameEngine(gameEngine) {}

GameStateShutdown::~GameStateShutdown() {}

void GameStateShutdown::update(const float elapsedSeconds) {
    (void)elapsedSeconds;
    mGameEngine.halt();
}

void GameStateShutdown::draw() {}
