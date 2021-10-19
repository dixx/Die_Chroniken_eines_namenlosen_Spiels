#include "CameraMover.h"
#include <input/Action.h>
#include <input/IActions.h>

CameraMover::CameraMover(leviathan::input::IActions& actions) : actions_(actions) {}

CameraMover::~CameraMover() {
    ignoreInput();
}

void CameraMover::onAction(const leviathan::input::Action action) {
    if (action.id == cameraActions::MOVE_FORWARD) {
        isMovingForward_ = action.isActive;
    } else if (action.id == cameraActions::MOVE_BACKWARD) {
        isMovingBackward_ = action.isActive;
    } else if (action.id == cameraActions::MOVE_LEFT) {
        isMovingLeft_ = action.isActive;
    } else if (action.id == cameraActions::MOVE_RIGHT) {
        isMovingRight_ = action.isActive;
    } else if (action.id == cameraActions::ROTATE_LEFT) {
        isRotatingLeft_ = action.isActive;
    } else if (action.id == cameraActions::ROTATE_RIGHT) {
        isRotatingRight_ = action.isActive;
    }
}

bool CameraMover::isMoving() {
    return isMovingForward_ || isMovingBackward_ || isMovingLeft_ || isMovingRight_;
}

bool CameraMover::isRotating() {
    return isRotatingLeft_ || isRotatingRight_;
}

leviathan::video::Vector3D CameraMover::getMovementSpeed() {
    direction_.x = 0.f;
    direction_.z = 0.f;
    if (isMovingForward_) direction_.z += 15.f;
    if (isMovingBackward_) direction_.z -= 15.f;
    if (isMovingLeft_) direction_.x -= 15.f;
    if (isMovingRight_) direction_.x += 15.f;
    return direction_;
}

float CameraMover::getRotationSpeed() {
    if (isRotatingLeft_ == isRotatingRight_) return 0.f;

    return (isRotatingLeft_ ? 100.f : -100.f);
}

void CameraMover::ignoreInput() {
    actions_.unsubscribe(*this, cameraActions::ROTATE_LEFT);
    actions_.unsubscribe(*this, cameraActions::ROTATE_RIGHT);
    actions_.unsubscribe(*this, cameraActions::MOVE_FORWARD);
    actions_.unsubscribe(*this, cameraActions::MOVE_BACKWARD);
    actions_.unsubscribe(*this, cameraActions::MOVE_LEFT);
    actions_.unsubscribe(*this, cameraActions::MOVE_RIGHT);
}

void CameraMover::reactToInput() {
    actions_.subscribe(*this, cameraActions::ROTATE_LEFT);
    actions_.subscribe(*this, cameraActions::ROTATE_RIGHT);
    actions_.subscribe(*this, cameraActions::MOVE_FORWARD);
    actions_.subscribe(*this, cameraActions::MOVE_BACKWARD);
    actions_.subscribe(*this, cameraActions::MOVE_LEFT);
    actions_.subscribe(*this, cameraActions::MOVE_RIGHT);
}
