#ifndef CAMERAMOVER_H
#define CAMERAMOVER_H

#include <cstdint>
#include <input/IActionConsumer.h>
#include <unordered_map>
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
    enum cameraActions { ROTATE_LEFT = 2010, ROTATE_RIGHT, MOVE_FORWARD, MOVE_BACKWARD, MOVE_LEFT, MOVE_RIGHT };
    const float MOVEMENT_SPEED = 15.f;  // virtual units per second
    const float ROTATION_SPEED = 100.f;  // degree per second
    leviathan::input::IActions& actions_;
    std::unordered_map<uint32_t, bool> actionActiveStates = {{ROTATE_LEFT, false}, {ROTATE_RIGHT, false},
        {MOVE_FORWARD, false}, {MOVE_BACKWARD, false}, {MOVE_LEFT, false}, {MOVE_RIGHT, false}};
    leviathan::video::Vector3D direction_ = leviathan::video::Vector3D();
};

#endif
