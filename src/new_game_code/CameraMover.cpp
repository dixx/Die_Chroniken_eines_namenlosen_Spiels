#include "CameraMover.h"
#include <input/Action.h>
#include <input/IActions.h>

CameraMover::CameraMover(leviathan::input::IActions& actions) : actions_(actions) {}

CameraMover::~CameraMover() {
    ignoreInput();
}

void CameraMover::onAction(const leviathan::input::Action action) {
    if (action.id < ROTATE_LEFT || action.id > MOVE_RIGHT) return;

    actionActiveStates[action.id] = action.isActive;
}

bool CameraMover::isMoving() {
    return actionActiveStates[MOVE_FORWARD] || actionActiveStates[MOVE_BACKWARD] || actionActiveStates[MOVE_LEFT]
           || actionActiveStates[MOVE_RIGHT];
}

bool CameraMover::isRotating() {
    return actionActiveStates[ROTATE_LEFT] || actionActiveStates[ROTATE_RIGHT];
}

leviathan::video::Vector3D CameraMover::getMovementSpeed() {
    direction_.x = 0.f;
    direction_.z = 0.f;
    if (actionActiveStates[MOVE_FORWARD]) direction_.z += MOVEMENT_SPEED;
    if (actionActiveStates[MOVE_BACKWARD]) direction_.z -= MOVEMENT_SPEED;
    if (actionActiveStates[MOVE_LEFT]) direction_.x -= MOVEMENT_SPEED;
    if (actionActiveStates[MOVE_RIGHT]) direction_.x += MOVEMENT_SPEED;
    return direction_;
}

float CameraMover::getRotationSpeed() {
    if (actionActiveStates[ROTATE_LEFT] == actionActiveStates[ROTATE_RIGHT]) return 0.f;

    return (actionActiveStates[ROTATE_LEFT] ? ROTATION_SPEED : -ROTATION_SPEED);
}

void CameraMover::ignoreInput() {
    actions_.unsubscribe(*this, ROTATE_LEFT);
    actions_.unsubscribe(*this, ROTATE_RIGHT);
    actions_.unsubscribe(*this, MOVE_FORWARD);
    actions_.unsubscribe(*this, MOVE_BACKWARD);
    actions_.unsubscribe(*this, MOVE_LEFT);
    actions_.unsubscribe(*this, MOVE_RIGHT);
}

void CameraMover::reactToInput() {
    actions_.subscribe(*this, ROTATE_LEFT);
    actions_.subscribe(*this, ROTATE_RIGHT);
    actions_.subscribe(*this, MOVE_FORWARD);
    actions_.subscribe(*this, MOVE_BACKWARD);
    actions_.subscribe(*this, MOVE_LEFT);
    actions_.subscribe(*this, MOVE_RIGHT);
}
