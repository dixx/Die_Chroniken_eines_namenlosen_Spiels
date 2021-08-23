#include "GameStateShutdown.h"
#include "defines.h"

GameStateShutdown::GameStateShutdown(leviathan::ILeviathanDevice& gameEngine) : gameEngine_(gameEngine) {}

GameStateShutdown::~GameStateShutdown() {}

void GameStateShutdown::update(const float elapsedSeconds) {
    (void)elapsedSeconds;
    gameEngine_.halt();
}

void GameStateShutdown::draw() {}

void GameStateShutdown::setActive() {}

void GameStateShutdown::setInactive() {}
