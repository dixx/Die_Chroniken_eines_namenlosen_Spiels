#ifndef GAMESTATEMAINMENU_H
#define GAMESTATEMAINMENU_H

#include <core/IGameState.h>
#include <input/IActionConsumer.h>

namespace leviathan {
    struct ILeviathanDevice;
    namespace input {
        struct Action;
    }
}

class GameStateMainMenu final : public leviathan::core::IGameState, leviathan::input::IActionConsumer {
public:
    enum actions {
        EXIT = 1,
        START_NEW_GAME,

        INVALID  // helpful for looping over all actions
    };

    explicit GameStateMainMenu(leviathan::ILeviathanDevice& gameEngine);
    ~GameStateMainMenu();

    GameStateMainMenu() = delete;
    GameStateMainMenu(const GameStateMainMenu&) = delete;
    GameStateMainMenu(const GameStateMainMenu&&) = delete;
    GameStateMainMenu& operator=(const GameStateMainMenu&) = delete;
    GameStateMainMenu& operator=(const GameStateMainMenu&&) = delete;

    void update(const float elapsedSeconds);

    void draw();

    void setActive() override;

    void setInactive() override;

    void onAction(const leviathan::input::Action action) override;

private:
    leviathan::ILeviathanDevice& mGameEngine;
};

#endif
