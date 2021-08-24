#ifndef GAMESTATEPLAY_H
#define GAMESTATEPLAY_H

#include <core/IGameState.h>
#include <input/IActionConsumer.h>

namespace leviathan {
    struct ILeviathanDevice;
    namespace input {
        struct Action;
    }
}

class GameStatePlay final : public leviathan::core::IGameState, leviathan::input::IActionConsumer {
public:
    enum actions {
        OPEN_IN_GAME_OPTIONS = 2002,
        CAMERA_ROTATE_LEFT = 2008,
        CAMERA_ROTATE_RIGHT,
        HERO_MOVE_FORWARD = 2011,
        HERO_MOVE_BACKWARD,
        HERO_MOVE_LEFT,
        HERO_MOVE_RIGHT
    };

    explicit GameStatePlay(leviathan::ILeviathanDevice& gameEngine);
    ~GameStatePlay();
    GameStatePlay(const GameStatePlay&) = delete;
    GameStatePlay& operator=(const GameStatePlay&) = delete;

    void update(const float elapsedSeconds);

    void draw();

    void setActive() override;

    void setInactive() override;

    void onAction(const leviathan::input::Action action);

private:
    leviathan::ILeviathanDevice& gameEngine_;

    void handleHeroMovementActions(const leviathan::input::Action& action);
    void moveHero(float x, float z);
};

#endif
