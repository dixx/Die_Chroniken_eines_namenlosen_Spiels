#ifndef CAMERAMOVER_H
#define CAMERAMOVER_H

#include <input/IActionConsumer.h>
#include <video/Vector3D.h>

namespace leviathan {
    namespace input {
        struct IActions;
    }
}

/*! \class CameraMover
 *  \brief Reagiert auf Camera-Actionen und berechnet Bewegungs- oder Rotationsgeschwindigkeitsvektoren
 */
class CameraMover final : public leviathan::input::IActionConsumer {
public:
    enum cameraActions { ROTATE_LEFT = 2008, ROTATE_RIGHT, MOVE_FORWARD = 2011, MOVE_BACKWARD, MOVE_LEFT, MOVE_RIGHT };

    explicit CameraMover(leviathan::input::IActions& actions);

    ~CameraMover();

    CameraMover() = delete;
    CameraMover(const CameraMover&) = delete;
    CameraMover(CameraMover&&) = delete;
    CameraMover& operator=(const CameraMover&) = delete;
    CameraMover& operator=(CameraMover&&) = delete;

    void onAction(const leviathan::input::Action action) override;

    bool isMoving();

    bool isRotating();

    leviathan::video::Vector3D getMovementSpeed();

    float getRotationSpeed();

    void ignoreInput();

    void reactToInput();

private:
    leviathan::input::IActions& actions_;
    bool isMovingLeft_ = false;
    bool isMovingRight_ = false;
    bool isMovingForward_ = false;
    bool isMovingBackward_ = false;
    bool isRotatingLeft_ = false;
    bool isRotatingRight_ = false;
    leviathan::video::Vector3D direction_ = leviathan::video::Vector3D();
};

#endif
