#include "GameStateShutdown.h"
#include <ILeviathanDevice.h>

GameStateShutdown::GameStateShutdown(leviathan::ILeviathanDevice& gameEngine) : gameEngine_(gameEngine) {}

GameStateShutdown::~GameStateShutdown() {}

void GameStateShutdown::update(const float elapsedSeconds) {
    (void)elapsedSeconds;
    gameEngine_.halt();
}

void GameStateShutdown::draw() {}
