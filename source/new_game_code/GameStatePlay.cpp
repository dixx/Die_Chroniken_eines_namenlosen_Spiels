#include "GameStatePlay.h"
#include "defines.h"

GameStatePlay::GameStatePlay(leviathan::LeviathanDevice& gameEngine) : gameEngine_(gameEngine) {
    gameEngine_.Actions().subscribe(*this, actions::OPEN_IN_GAME_OPTIONS);
    gameEngine_.MousePointerControl().createMousePointer(
        1, "gfx/Mauszeiger.bmp", irr::core::recti(0, 0, 60, 60), irr::core::vector2di(30, 30));
    gameEngine_.MousePointerControl().setActiveMousPointer(1);
}

GameStatePlay::~GameStatePlay() {
    gameEngine_.Actions().unsubscribe(*this, actions::OPEN_IN_GAME_OPTIONS);
}

void GameStatePlay::update(const float elapsedSeconds) {
    (void)elapsedSeconds;
}

void GameStatePlay::draw() {
    gameEngine_.MousePointerControl().draw();
}

void GameStatePlay::onAction(const uint32_t id, const bool isActive) {
    switch (id) {
    case actions::OPEN_IN_GAME_OPTIONS:
        if (isActive)
            gameEngine_.GameStateManager().transitTo(STATE_SHUTDOWN);
        break;
    }
}
