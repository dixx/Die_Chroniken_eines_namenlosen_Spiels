#include "GameStateShutdown.h"
#include "defines.h"

GameStateShutdown::GameStateShutdown(leviathan::LeviathanDevice& gameEngine) : gameEngine_(gameEngine) {
    // gameEngine_.halt();
}

GameStateShutdown::~GameStateShutdown() {

}

void GameStateShutdown::update(const float elapsedSeconds) {
    (void)elapsedSeconds;
}

void GameStateShutdown::draw() {

}
