#include "GameStateMainMenu.h"
#include "defines.h"
#include <cstdint>

GameStateMainMenu::GameStateMainMenu(leviathan::LeviathanDevice& gameEngine) : gameEngine_(gameEngine) {
    gameEngine_.MousePointerControl().createMousePointer(
        1, "gfx/Mauszeiger.bmp", irr::core::recti(0, 0, 60, 60), irr::core::vector2di(30, 30));
    gameEngine_.MousePointerControl().setActiveMousPointer(1);
    leviathan::gui::MenuConfiguration menuConfig({{436, 555}, {663, 115}, "gfx/menues1.bmp", {588, 212}, true});
    gameEngine_.MenuControl().addMenu(L"Main Menu", menuConfig);
    leviathan::gui::ButtonConfiguration buttonConfig({
        {313, 88}, {85, 63}, "gfx/menues1.bmp", {663, 115}, {654, 22}, true
    });
    gameEngine_.MenuControl().addButton(L"Main Menu", L"Start Game", buttonConfig);
    buttonConfig.relativePositionInMenu.y = 134;
    gameEngine_.MenuControl().addButton(L"Main Menu", L"Load Game", buttonConfig);
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
        if (isActive) gameEngine_.GameStateManager().transitTo(STATE_SHUTDOWN);
        break;
    }
}

void GameStateMainMenu::setActive() {
    for (uint32_t action = actions::EXIT; action != actions::ACTIONS_COUNT; ++action) {
        gameEngine_.Actions().subscribe(*this, action);
    }
    gameEngine_.MenuControl().enable(L"Main Menu");
}

void GameStateMainMenu::setInactive() {
    for (uint32_t action = actions::EXIT; action != actions::ACTIONS_COUNT; ++action) {
        gameEngine_.Actions().unsubscribe(*this, action);
    }
    gameEngine_.MenuControl().disable(L"Main Menu");
}
