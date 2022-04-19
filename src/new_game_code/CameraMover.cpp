#include "CameraMover.h"
#include <input/Action.h>
#include <input/IActions.h>

CameraMover::CameraMover(leviathan::input::IActions& actions) : mActions(actions) {}

CameraMover::~CameraMover() {
    ignoreInput();
}

void CameraMover::onAction(const leviathan::input::Action action) {
    if (action.id < ROTATE_LEFT || action.id > MOVE_RIGHT) return;

    mActionActiveStates[action.id] = action.isActive;
}

bool CameraMover::isMoving() {
    return mActionActiveStates[MOVE_FORWARD] || mActionActiveStates[MOVE_BACKWARD] || mActionActiveStates[MOVE_LEFT]
           || mActionActiveStates[MOVE_RIGHT];
}

bool CameraMover::isRotating() {
    return mActionActiveStates[ROTATE_LEFT] || mActionActiveStates[ROTATE_RIGHT];
}

leviathan::video::Vector3D CameraMover::getMovementSpeed() {
    mDirection.x = 0.f;
    mDirection.z = 0.f;
    if (mActionActiveStates[MOVE_FORWARD]) mDirection.z += MOVEMENT_SPEED;
    if (mActionActiveStates[MOVE_BACKWARD]) mDirection.z -= MOVEMENT_SPEED;
    if (mActionActiveStates[MOVE_LEFT]) mDirection.x -= MOVEMENT_SPEED;
    if (mActionActiveStates[MOVE_RIGHT]) mDirection.x += MOVEMENT_SPEED;
    return mDirection;
}

float CameraMover::getRotationSpeed() {
    if (mActionActiveStates[ROTATE_LEFT] == mActionActiveStates[ROTATE_RIGHT]) return 0.f;

    return (mActionActiveStates[ROTATE_LEFT] ? ROTATION_SPEED : -ROTATION_SPEED);
}

void CameraMover::ignoreInput() {
    mActions.unsubscribe(*this, ROTATE_LEFT);
    mActions.unsubscribe(*this, ROTATE_RIGHT);
    mActions.unsubscribe(*this, MOVE_FORWARD);
    mActions.unsubscribe(*this, MOVE_BACKWARD);
    mActions.unsubscribe(*this, MOVE_LEFT);
    mActions.unsubscribe(*this, MOVE_RIGHT);
}

void CameraMover::reactToInput() {
    mActions.subscribe(*this, ROTATE_LEFT);
    mActions.subscribe(*this, ROTATE_RIGHT);
    mActions.subscribe(*this, MOVE_FORWARD);
    mActions.subscribe(*this, MOVE_BACKWARD);
    mActions.subscribe(*this, MOVE_LEFT);
    mActions.subscribe(*this, MOVE_RIGHT);
}
