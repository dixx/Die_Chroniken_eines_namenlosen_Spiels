#ifndef HEROMOVER_H
#define HEROMOVER_H

#include <ILeviathanDevice.h>
#include <input/IActionConsumer.h>
#include <video/Vector3D.h>

namespace leviathan {
    namespace gui {
        struct IMousePointerControl;
    }
    namespace input {
        struct IActions;
    }
    namespace world {
        struct ICollider;
    }
}

/*! \class HeroMover
 *  \brief Reagiert auf Held-spezifische Aktionen und berechnet Bewegungsgeschwindigkeitsvektoren und Rotation
 */
class HeroMover final : public leviathan::input::IActionConsumer {
public:
    explicit HeroMover(leviathan::ILeviathanDevice& gameEngine);

    ~HeroMover();

    HeroMover() = delete;
    HeroMover(const HeroMover&) = delete;
    HeroMover(HeroMover&&) = delete;
    HeroMover& operator=(const HeroMover&) = delete;
    HeroMover& operator=(HeroMover&&) = delete;

    void onAction(const leviathan::input::Action action) override;

    void update(const float elapsedSeconds, const leviathan::video::Position3D& currentPosition);

    leviathan::video::Vector3D getPosition() const;

    leviathan::video::Rotation3D getRotation() const;

    void ignoreInput();

    void reactToInput();

private:
    enum mHeroActions { TARGET_SELECTED = 3001 };
    float mLocomotionSpeed = 3.2f;  // virtual units per second
    leviathan::input::IActions& mActions;
    leviathan::world::ICollider& mCollider;
    leviathan::gui::IMousePointerControl& mMousePointer;
    leviathan::video::Position3D mPosition = leviathan::video::Position3D({});
    leviathan::video::Position3D mTargetPosition = leviathan::video::Position3D({});
    leviathan::video::Rotation3D mRotation = leviathan::video::Rotation3D({});
    bool mIsMoving = false;
};

#endif
