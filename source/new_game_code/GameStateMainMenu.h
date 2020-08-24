#ifndef GAMESTATEMAINMENU_H
#define GAMESTATEMAINMENU_H

#include "leviathan.h"

class GameStateMainMenu final : public leviathan::core::IGameState, leviathan::input::IActionConsumer {
public:
    enum actions {
        EXIT = 1,
        START_NEW_GAME,

        INVALID  // helpful for looping over all actions
    };

    explicit GameStateMainMenu(leviathan::LeviathanDevice& gameEngine);
    virtual ~GameStateMainMenu();
    GameStateMainMenu(const GameStateMainMenu&) = delete;
    GameStateMainMenu& operator=(const GameStateMainMenu&) = delete;

    void update(const float elapsedSeconds);

    void draw();

    void setActive();

    void setInactive();

    void onAction(const leviathan::input::Action action);

private:
    leviathan::LeviathanDevice& gameEngine_;
};

#endif
