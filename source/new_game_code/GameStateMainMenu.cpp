#include "GameStateMainMenu.h"
#include "defines.h"
#include <cstdint>

GameStateMainMenu::GameStateMainMenu(leviathan::LeviathanDevice& gameEngine) : gameEngine_(gameEngine) {
    for (uint32_t action = actions::EXIT; action != actions::ACTIONS_COUNT; ++action) {
        gameEngine_.Actions().subscribe(*this, action);
    }
    gameEngine_.MousePointerControl().createMousePointer(
        1, "gfx/Mauszeiger.bmp", irr::core::recti(0, 0, 60, 60), irr::core::vector2di(30, 30));
    gameEngine_.MousePointerControl().setActiveMousPointer(1);
}

GameStateMainMenu::~GameStateMainMenu() {
    for (uint32_t action = actions::EXIT; action != actions::ACTIONS_COUNT; ++action) {
        gameEngine_.Actions().unsubscribe(*this, action);
    }
}

void GameStateMainMenu::update(const float elapsedSeconds) {
    (void)elapsedSeconds;
}

void GameStateMainMenu::draw() {
    gameEngine_.MenuControl().draw();
    gameEngine_.MousePointerControl().draw();
}

void GameStateMainMenu::onAction(const uint32_t id, const bool isActive) {
    switch (id) {
    case actions::EXIT:
        if (isActive)
            gameEngine_.GameStateManager().transitTo(STATE_SHUTDOWN);
        break;
    }
}

void GameStateMainMenu::setActive() {
    for (uint32_t action = actions::EXIT; action != actions::ACTIONS_COUNT; ++action) {
        gameEngine_.Actions().subscribe(*this, action);
    }
}

void GameStateMainMenu::setInactive() {
    for (uint32_t action = actions::EXIT; action != actions::ACTIONS_COUNT; ++action) {
        gameEngine_.Actions().unsubscribe(*this, action);
    }
}
