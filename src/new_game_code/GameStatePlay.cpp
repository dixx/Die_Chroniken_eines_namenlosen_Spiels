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
: mGameEngine(gameEngine), mCameraMover(mGameEngine.Actions()) {
    mGameEngine.MousePointerControl().addMousePointer(2001, {"gfx/Mauszeiger.bmp", {{0, 61}, {60, 120}}, {30, 30}});

    auto startingPosition = leviathan::video::Position3D(
        {11.f, mGameEngine.Ground().getHeight({11.f, 0.f, 11.f}), 11.f});
    mGameEngine.Heroes().getActiveHero().setRotation({0.f, 0.f, 0.f});
    mGameEngine.Heroes().getActiveHero().setPosition(startingPosition);
    mGameEngine.Camera().setTargetPosition(startingPosition);
}

GameStatePlay::~GameStatePlay() {
    mGameEngine.Actions().unsubscribe(*this, actions::OPEN_IN_GAME_OPTIONS);
    mGameEngine.Actions().unsubscribe(*this, actions::TARGET_SELECTED);
}

void GameStatePlay::update(const float elapsedSeconds) {
    moveCamera(elapsedSeconds);
}

void GameStatePlay::draw() {
    mGameEngine.MousePointerControl().draw();
}

void GameStatePlay::onAction(const leviathan::input::Action action) {
    if (action.id == actions::TARGET_SELECTED && action.isActive) {
        leviathan::world::Collision collision = mGameEngine.Collider().getCollisionFromScreenCoordinates(
            mGameEngine.MousePointerControl().getPosition());
        if (collision.happened) {
            mGameEngine.Heroes().getActiveHero().setPosition(collision.collisionPoint);
        }
    }
    if (action.id == actions::OPEN_IN_GAME_OPTIONS && action.isActive) {
        mGameEngine.GameStateManager().transitTo(STATE_LOADER);
    }
}

void GameStatePlay::setActive() {
    mGameEngine.Actions().subscribe(*this, actions::OPEN_IN_GAME_OPTIONS);
    mGameEngine.Actions().subscribe(*this, actions::TARGET_SELECTED);
    mGameEngine.Heroes().getActiveHero().enablePlayableCharacter();
    mGameEngine.MousePointerControl().setActiveMousPointer(2001);
    mCameraMover.reactToInput();
}

void GameStatePlay::setInactive() {
    mGameEngine.Heroes().getActiveHero().disablePlayableCharacter();
    mGameEngine.Actions().unsubscribe(*this, actions::OPEN_IN_GAME_OPTIONS);
    mGameEngine.Actions().unsubscribe(*this, actions::TARGET_SELECTED);
    mCameraMover.ignoreInput();
}

/* private */

void GameStatePlay::moveCamera(const float elapsedSeconds) {
    mGameEngine.Camera().setMovementSpeed(mCameraMover.getMovementSpeed());
    mGameEngine.Camera().enableMovement(mCameraMover.isMoving());
    mGameEngine.Camera().setRotationSpeed(mCameraMover.getRotationSpeed());
    mGameEngine.Camera().enableRotation(mCameraMover.isRotating());
    mGameEngine.Camera().update(elapsedSeconds);
    mGameEngine.Ground().adjustHeightOf(mGameEngine.Camera());
}
