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
#include <world/Collision.h>
#include <world/ICollider.h>
#include <world/IGround.h>
#include <world/Node3DConfiguration.h>

GameStatePlay::GameStatePlay(leviathan::ILeviathanDevice& gameEngine)
: gameEngine_(gameEngine), cameraMover_(gameEngine_.Actions()) {
    gameEngine_.MousePointerControl().addMousePointer(2001, {"gfx/Mauszeiger.bmp", {{0, 61}, {60, 120}}, {30, 30}});

    auto startingPosition = leviathan::video::Position3D(
        {11.f, gameEngine_.Ground().getHeight({11.f, 0.f, 11.f}), 11.f});
    gameEngine_.Heroes().getActiveHero().setRotation({0.f, 0.f, 0.f});
    gameEngine_.Heroes().getActiveHero().setPosition(startingPosition);
    gameEngine_.Camera().setTargetPosition(startingPosition);
}

GameStatePlay::~GameStatePlay() {
    gameEngine_.Actions().unsubscribe(*this, actions::OPEN_IN_GAME_OPTIONS);
    gameEngine_.Actions().unsubscribe(*this, actions::TARGET_SELECTED);
}

void GameStatePlay::update(const float elapsedSeconds) {
    moveCamera(elapsedSeconds);
}

void GameStatePlay::draw() {
    gameEngine_.MousePointerControl().draw();
}

void GameStatePlay::onAction(const leviathan::input::Action action) {
    if (action.id == actions::TARGET_SELECTED && action.isActive) {
        leviathan::world::Collision collision = gameEngine_.Collider().getCollisionFromScreenCoordinates(
            gameEngine_.MousePointerControl().getPosition());
        if (collision.happened) {
            gameEngine_.Heroes().getActiveHero().setPosition(collision.collisionPoint);
        }
    }
    if (action.id == actions::OPEN_IN_GAME_OPTIONS && action.isActive) {
        gameEngine_.GameStateManager().transitTo(STATE_LOADER);
    }
}

void GameStatePlay::setActive() {
    gameEngine_.Actions().subscribe(*this, actions::OPEN_IN_GAME_OPTIONS);
    gameEngine_.Actions().subscribe(*this, actions::TARGET_SELECTED);
    gameEngine_.Heroes().getActiveHero().enablePlayableCharacter();
    gameEngine_.MousePointerControl().setActiveMousPointer(2001);
    cameraMover_.reactToInput();
}

void GameStatePlay::setInactive() {
    gameEngine_.Heroes().getActiveHero().disablePlayableCharacter();
    gameEngine_.Actions().unsubscribe(*this, actions::OPEN_IN_GAME_OPTIONS);
    gameEngine_.Actions().unsubscribe(*this, actions::TARGET_SELECTED);
    cameraMover_.ignoreInput();
}

/* private */

void GameStatePlay::moveCamera(const float elapsedSeconds) {
    gameEngine_.Camera().setMovementSpeed(cameraMover_.getMovementSpeed());
    gameEngine_.Camera().enableMovement(cameraMover_.isMoving());
    gameEngine_.Camera().setRotationSpeed(cameraMover_.getRotationSpeed());
    gameEngine_.Camera().enableRotation(cameraMover_.isRotating());
    gameEngine_.Camera().update(elapsedSeconds);
    gameEngine_.Ground().adjustHeightOf(gameEngine_.Camera());
}
