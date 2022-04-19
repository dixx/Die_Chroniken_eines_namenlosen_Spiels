#include "GameStateMainMenu.h"
#include "defines.h"
#include <ILeviathanDevice.h>
#include <characters/CharacterConfiguration.h>
#include <characters/IHeroes.h>
#include <core/IConfiguration.h>
#include <core/IGameStateManager.h>
#include <cstdint>
#include <gui/IMenuControl.h>
#include <gui/IMousePointerControl.h>
#include <gui/MousePointerConfiguration.h>
#include <input/Action.h>
#include <input/IActions.h>
#include <video/Dimension2D.h>
#include <video/Position2D.h>

GameStateMainMenu::GameStateMainMenu(leviathan::ILeviathanDevice& gameEngine) : mGameEngine(gameEngine) {
    mGameEngine.MousePointerControl().addMousePointer(1, {"gfx/Mauszeiger.bmp", {{0, 0}, {60, 60}}, {30, 30}});

    const leviathan::video::Dimension2D screenSize = mGameEngine.Configuration().getScreenSize();
    leviathan::video::Dimension2D menuSize({436, 555});
    leviathan::video::Position2D menuPosition(
        {static_cast<int32_t>(screenSize.w - menuSize.w), static_cast<int32_t>(screenSize.h - menuSize.h)});
    leviathan::gui::MenuConfiguration menuConfig({menuSize, menuPosition, "gfx/menues1.bmp", {588, 212}, true});
    mGameEngine.MenuControl().addMenu(L"Main Menu", menuConfig);

    leviathan::video::Position2D buttonPosition({menuPosition.x + 80, menuPosition.y + 64});
    leviathan::gui::ButtonConfiguration buttonConfig(
        {{313, 88}, buttonPosition, "gfx/menues1.bmp", {663, 115}, {654, 22}, true});
    mGameEngine.MenuControl().addButton(L"Main Menu", L"Start Game", buttonConfig);
    buttonConfig.relativePositionInMenu.y += 67;
    mGameEngine.MenuControl().addButton(L"Main Menu", L"Load Game", buttonConfig);
    buttonConfig.relativePositionInMenu.y += 284;
    mGameEngine.MenuControl().addButton(L"Main Menu", L"Main Menu - Quit", buttonConfig);
    leviathan::characters::CharacterConfiguration config = {
        "Anon", "Punk", {"gfx/sydney.md2", "gfx/sydney.bmp", {}, {0.f, 0.4f, 0.f}, {}, {0.025f, 0.025f, 0.025f}}};
    mGameEngine.Heroes().create(config);
    mGameEngine.Heroes().activate("Punk");
}

GameStateMainMenu::~GameStateMainMenu() {
    for (uint32_t action = actions::EXIT; action != actions::INVALID; ++action) {
        mGameEngine.Actions().unsubscribe(*this, action);
    }
}

void GameStateMainMenu::update(const float elapsedSeconds) {
    (void)elapsedSeconds;
}

void GameStateMainMenu::draw() {
    mGameEngine.MenuControl().draw();
    mGameEngine.MousePointerControl().draw();
}

void GameStateMainMenu::onAction(const leviathan::input::Action action) {
    switch (action.id) {
    case actions::START_NEW_GAME:
        if (action.isActive) mGameEngine.GameStateManager().transitTo(STATE_LOADER);
        break;
    case actions::EXIT:
        if (action.isActive) mGameEngine.GameStateManager().transitTo(STATE_SHUTDOWN);
        break;
    }
}

void GameStateMainMenu::setActive() {
    for (uint32_t action = actions::EXIT; action != actions::INVALID; ++action) {
        mGameEngine.Actions().subscribe(*this, action);
    }
    mGameEngine.MenuControl().enable(L"Main Menu");
    mGameEngine.MousePointerControl().setActiveMousPointer(1);
}

void GameStateMainMenu::setInactive() {
    for (uint32_t action = actions::EXIT; action != actions::INVALID; ++action) {
        mGameEngine.Actions().unsubscribe(*this, action);
    }
    mGameEngine.MenuControl().disable(L"Main Menu");
}
