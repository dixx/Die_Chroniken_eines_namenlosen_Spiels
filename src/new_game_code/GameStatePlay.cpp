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
: mGameEngine(gameEngine), mCameraMover(mGameEngine.Actions()), mHeroMover(mGameEngine) {
    mGameEngine.MousePointerControl().addMousePointer(2001, {"gfx/Mauszeiger.bmp", {{0, 61}, {60, 120}}, {30, 30}});
}

GameStatePlay::~GameStatePlay() {
    mGameEngine.Actions().unsubscribe(*this, actions::OPEN_IN_GAME_OPTIONS);
}

void GameStatePlay::update(const float elapsedSeconds) {
    moveCamera(elapsedSeconds);
    moveHero(elapsedSeconds);
}

void GameStatePlay::draw() {
    mGameEngine.MousePointerControl().draw();
}

void GameStatePlay::onAction(const leviathan::input::Action action) {
    if (action.id == actions::OPEN_IN_GAME_OPTIONS && action.isActive) {
        mGameEngine.GameStateManager().transitTo(STATE_LOADER);
    }
}

void GameStatePlay::setActive() {
    mGameEngine.Actions().subscribe(*this, actions::OPEN_IN_GAME_OPTIONS);
    mGameEngine.Heroes().getActiveHero().enablePlayableCharacter();
    mGameEngine.MousePointerControl().setActiveMousPointer(2001);
    mCameraMover.reactToInput();
    mHeroMover.reactToInput();
}

void GameStatePlay::setInactive() {
    mGameEngine.Heroes().getActiveHero().disablePlayableCharacter();
    mGameEngine.Actions().unsubscribe(*this, actions::OPEN_IN_GAME_OPTIONS);
    mCameraMover.ignoreInput();
    mHeroMover.ignoreInput();
}

/* private */

void GameStatePlay::moveCamera(const float elapsedSeconds) {
    mGameEngine.Camera().setMovementSpeed(mCameraMover.getMovementSpeed());
    mGameEngine.Camera().enableMovement(mCameraMover.isMoving());
    mGameEngine.Camera().setRotationSpeed(mCameraMover.getRotationSpeed());
    mGameEngine.Camera().enableRotation(mCameraMover.isRotating());
    if (mCameraMover.isMoving()) {
        mGameEngine.Camera().update(elapsedSeconds);
        mGameEngine.Ground().adjustHeightOf(mGameEngine.Camera());
    }
}

void GameStatePlay::moveHero(const float elapsedSeconds) {
    leviathan::characters::IHero& hero = mGameEngine.Heroes().getActiveHero();
    mHeroMover.update(elapsedSeconds, hero.getPosition());
    hero.setPosition(mHeroMover.getPosition());
    hero.setRotation(mHeroMover.getRotation());
    hero.setIsMoving(mHeroMover.isMoving());
    hero.update(elapsedSeconds);
}
