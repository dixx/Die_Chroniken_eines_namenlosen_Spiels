#include "GameStatePlay.h"
#include "defines.h"

GameStatePlay::GameStatePlay(leviathan::LeviathanDevice& gameEngine) : gameEngine_(gameEngine) {
    gameEngine_.MousePointerControl().createMousePointer(
        2001, "gfx/Mauszeiger.bmp", irr::core::recti(0, 61, 60, 120), irr::core::vector2di(30, 30));

    gameEngine_.Heroes().getActiveHero().setRotation({0.f, -90.f, 0.f});
    gameEngine_.Heroes().getActiveHero().setPosition({11.f, 0.f, 11.f});
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

void GameStatePlay::onAction(const leviathan::input::Action action) {
    switch (action.id) {
    case actions::OPEN_IN_GAME_OPTIONS: {
        if (action.isActive) gameEngine_.GameStateManager().transitTo(STATE_LOADER);
        break;
    }
    case actions::CAMERA_ROTATE_LEFT:
        break;
    case actions::CAMERA_ROTATE_RIGHT:
        break;
    case actions::HERO_MOVE_FORWARD: {
        auto position = gameEngine_.Heroes().getActiveHero().getPosition();
        position.z += 0.2f;
        gameEngine_.Heroes().getActiveHero().setPosition(position);
        break;
    }
    case actions::HERO_MOVE_BACKWARD: {
        auto position = gameEngine_.Heroes().getActiveHero().getPosition();
        position.z -= 0.2f;
        gameEngine_.Heroes().getActiveHero().setPosition(position);
        break;
    }
    case actions::HERO_MOVE_LEFT: {
        auto position = gameEngine_.Heroes().getActiveHero().getPosition();
        position.x -= 0.2f;
        gameEngine_.Heroes().getActiveHero().setPosition(position);
        break;
    }
    case actions::HERO_MOVE_RIGHT: {
        auto position = gameEngine_.Heroes().getActiveHero().getPosition();
        position.x += 0.2f;
        gameEngine_.Heroes().getActiveHero().setPosition(position);
        break;
    }
    }
}

void GameStatePlay::setActive() {
    gameEngine_.Actions().subscribe(*this, actions::OPEN_IN_GAME_OPTIONS);
    gameEngine_.Actions().subscribe(*this, actions::HERO_MOVE_FORWARD);
    gameEngine_.Actions().subscribe(*this, actions::HERO_MOVE_BACKWARD);
    gameEngine_.Actions().subscribe(*this, actions::HERO_MOVE_LEFT);
    gameEngine_.Actions().subscribe(*this, actions::HERO_MOVE_RIGHT);
    gameEngine_.Heroes().getActiveHero().enablePlayableCharacter();
    gameEngine_.MousePointerControl().setActiveMousPointer(2001);
}

void GameStatePlay::setInactive() {
    gameEngine_.Heroes().getActiveHero().disablePlayableCharacter();
    gameEngine_.Actions().unsubscribe(*this, actions::OPEN_IN_GAME_OPTIONS);
    gameEngine_.Actions().unsubscribe(*this, actions::HERO_MOVE_FORWARD);
    gameEngine_.Actions().unsubscribe(*this, actions::HERO_MOVE_BACKWARD);
    gameEngine_.Actions().unsubscribe(*this, actions::HERO_MOVE_LEFT);
    gameEngine_.Actions().unsubscribe(*this, actions::HERO_MOVE_RIGHT);
}
