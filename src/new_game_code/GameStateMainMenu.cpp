#include "GameStateMainMenu.h"
#include "defines.h"
#include <cstdint>
#include <video/Dimension2D.h>

GameStateMainMenu::GameStateMainMenu(leviathan::LeviathanDevice& gameEngine) : gameEngine_(gameEngine) {
    gameEngine_.MousePointerControl().createMousePointer(
        1, "gfx/Mauszeiger.bmp", irr::core::recti(0, 0, 60, 60), irr::core::vector2di(30, 30));

    const leviathan::video::Dimension2D screenSize = gameEngine_.Configuration().getScreenSize();
    leviathan::video::Dimension2D menuSize({436, 555});
    leviathan::video::Position2D menuPosition(
        {static_cast<int32_t>(screenSize.w - menuSize.w), static_cast<int32_t>(screenSize.h - menuSize.h)});
    leviathan::gui::MenuConfiguration menuConfig({menuSize, menuPosition, "gfx/menues1.bmp", {588, 212}, true});
    gameEngine_.MenuControl().addMenu(L"Main Menu", menuConfig);

    leviathan::video::Position2D buttonPosition({menuPosition.x + 80, menuPosition.y + 64});
    leviathan::gui::ButtonConfiguration buttonConfig(
        {{313, 88}, buttonPosition, "gfx/menues1.bmp", {663, 115}, {654, 22}, true});
    gameEngine_.MenuControl().addButton(L"Main Menu", L"Start Game", buttonConfig);
    buttonConfig.relativePositionInMenu.y += 67;
    gameEngine_.MenuControl().addButton(L"Main Menu", L"Load Game", buttonConfig);
    buttonConfig.relativePositionInMenu.y += 284;
    gameEngine_.MenuControl().addButton(L"Main Menu", L"Main Menu - Quit", buttonConfig);
    leviathan::characters::CharacterConfiguration config = {
        "Anon", "Punk", {"gfx/sydney.md2", "gfx/sydney.bmp", {}, {}, {}, {0.025f, 0.025f, 0.025f}}};
    gameEngine_.Heroes().create(config);
    gameEngine_.Heroes().activate("Punk");
}

GameStateMainMenu::~GameStateMainMenu() {
    for (uint32_t action = actions::EXIT; action != actions::INVALID; ++action) {
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

void GameStateMainMenu::onAction(const leviathan::input::Action action) {
    switch (action.id) {
    case actions::START_NEW_GAME:
        if (action.isActive) gameEngine_.GameStateManager().transitTo(STATE_LOADER);
        break;
    case actions::EXIT:
        if (action.isActive) gameEngine_.GameStateManager().transitTo(STATE_SHUTDOWN);
        break;
    }
}

void GameStateMainMenu::setActive() {
    for (uint32_t action = actions::EXIT; action != actions::INVALID; ++action) {
        gameEngine_.Actions().subscribe(*this, action);
    }
    gameEngine_.MenuControl().enable(L"Main Menu");
    gameEngine_.MousePointerControl().setActiveMousPointer(1);
}

void GameStateMainMenu::setInactive() {
    for (uint32_t action = actions::EXIT; action != actions::INVALID; ++action) {
        gameEngine_.Actions().unsubscribe(*this, action);
    }
    gameEngine_.MenuControl().disable(L"Main Menu");
}
