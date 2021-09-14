#include "GameStatePlay.h"
#include "defines.h"
#include <ILeviathanDevice.h>
#include <characters/IHero.h>
#include <characters/IHeroes.h>
#include <core/IGameStateManager.h>
#include <gui/IMousePointerControl.h>
#include <gui/MousePointerConfiguration.h>
#include <input/Action.h>
#include <input/IActions.h>
#include <video/ICamera.h>
#include <world/IGround.h>
#include <world/Node3DConfiguration.h>

GameStatePlay::GameStatePlay(leviathan::ILeviathanDevice& gameEngine) : gameEngine_(gameEngine) {
    gameEngine_.MousePointerControl().addMousePointer(2001, {"gfx/Mauszeiger.bmp", {{0, 61}, {60, 120}}, {30, 30}});

    auto startingPosition = leviathan::video::Position3D(
        {11.f, gameEngine_.Ground().getHeight({11.f, 0.f, 11.f}), 11.f});
    gameEngine_.Heroes().getActiveHero().setRotation({0.f, -90.f, 0.f});
    gameEngine_.Heroes().getActiveHero().setPosition(startingPosition);
    gameEngine_.Camera().setTargetPosition(startingPosition);
}

GameStatePlay::~GameStatePlay() {
    gameEngine_.Actions().unsubscribe(*this, actions::OPEN_IN_GAME_OPTIONS);
}

void GameStatePlay::update(const float elapsedSeconds) {
    gameEngine_.Camera().update(elapsedSeconds);
}

void GameStatePlay::draw() {
    gameEngine_.MousePointerControl().draw();
}

void GameStatePlay::onAction(const leviathan::input::Action action) {
    handleHeroMovementActions(action);
    handleCameraActions(action);
    if (action.id == actions::OPEN_IN_GAME_OPTIONS && action.isActive) {
        gameEngine_.GameStateManager().transitTo(STATE_LOADER);
    }
}

void GameStatePlay::setActive() {
    gameEngine_.Actions().subscribe(*this, actions::OPEN_IN_GAME_OPTIONS);
    gameEngine_.Actions().subscribe(*this, actions::HERO_MOVE_FORWARD);
    gameEngine_.Actions().subscribe(*this, actions::HERO_MOVE_BACKWARD);
    gameEngine_.Actions().subscribe(*this, actions::HERO_MOVE_LEFT);
    gameEngine_.Actions().subscribe(*this, actions::HERO_MOVE_RIGHT);
    gameEngine_.Actions().subscribe(*this, actions::CAMERA_ROTATE_LEFT);
    gameEngine_.Actions().subscribe(*this, actions::CAMERA_ROTATE_RIGHT);
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
    gameEngine_.Actions().unsubscribe(*this, actions::CAMERA_ROTATE_LEFT);
    gameEngine_.Actions().unsubscribe(*this, actions::CAMERA_ROTATE_RIGHT);
}

/* private */

void GameStatePlay::handleHeroMovementActions(const leviathan::input::Action& action) {
    if (action.id == actions::HERO_MOVE_FORWARD) {
        moveHero(0.0f, 0.2f);
    }
    if (action.id == actions::HERO_MOVE_BACKWARD) {
        moveHero(0.0f, -0.2f);
    }
    if (action.id == actions::HERO_MOVE_LEFT) {
        moveHero(-0.2f, 0.0f);
    }
    if (action.id == actions::HERO_MOVE_RIGHT) {
        moveHero(0.2f, 0.0f);
    }
}

void GameStatePlay::handleCameraActions(const leviathan::input::Action& action) {
    if (action.id == actions::CAMERA_ROTATE_LEFT) {
        gameEngine_.Camera().setRotationSpeed(100.f);
        gameEngine_.Camera().enableRotation(action.isActive);
    } else if (action.id == actions::CAMERA_ROTATE_RIGHT) {
        gameEngine_.Camera().setRotationSpeed(-100.f);
        gameEngine_.Camera().enableRotation(action.isActive);
    }
}

void GameStatePlay::moveHero(float x, float z) {
    auto position = gameEngine_.Heroes().getActiveHero().getPosition();
    position.x += x;
    position.z += z;
    position.y = gameEngine_.Ground().getHeight(position);
    gameEngine_.Heroes().getActiveHero().setPosition(position);
    gameEngine_.Camera().setTargetPosition(position);
}
