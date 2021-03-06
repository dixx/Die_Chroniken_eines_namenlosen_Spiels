#ifndef GAMESTATEPLAY_H
#define GAMESTATEPLAY_H

#include "leviathan.h"

class GameStatePlay final : public leviathan::core::IGameState, leviathan::input::IActionConsumer {
public:
    enum actions { OPEN_IN_GAME_OPTIONS = 2002 };

    explicit GameStatePlay(leviathan::LeviathanDevice& gameEngine);
    virtual ~GameStatePlay();
    GameStatePlay(const GameStatePlay&) = delete;
    GameStatePlay& operator=(const GameStatePlay&) = delete;

    void update(const float elapsedSeconds);

    void draw();

    void setActive();

    void setInactive();

    void onAction(const leviathan::input::Action action);

private:
    leviathan::LeviathanDevice& gameEngine_;
};

#endif
