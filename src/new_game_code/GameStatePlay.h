#ifndef GAMESTATEPLAY_H
#define GAMESTATEPLAY_H

#include "CameraMover.h"
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
    enum actions { OPEN_IN_GAME_OPTIONS = 2002, TARGET_SELECTED = 3001 };

    explicit GameStatePlay(leviathan::ILeviathanDevice& gameEngine);
    ~GameStatePlay();

    GameStatePlay() = delete;
    GameStatePlay(const GameStatePlay&) = delete;
    GameStatePlay(const GameStatePlay&&) = delete;
    GameStatePlay& operator=(const GameStatePlay&) = delete;
    GameStatePlay& operator=(const GameStatePlay&&) = delete;

    void update(const float elapsedSeconds) override;

    void draw() override;

    void setActive() override;

    void setInactive() override;

    void onAction(const leviathan::input::Action action) override;

private:
    leviathan::ILeviathanDevice& mGameEngine;
    CameraMover mCameraMover;

    void handleCameraActions(const leviathan::input::Action& action);
    void moveCamera(const float elapsedSeconds);
};

#endif
