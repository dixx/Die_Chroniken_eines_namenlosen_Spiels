#ifndef GAMESTATESHUTDOWN_H
#define GAMESTATESHUTDOWN_H

#include "leviathan.h"

class GameStateShutdown final : public leviathan::core::IGameState {
public:
    explicit GameStateShutdown(leviathan::LeviathanDevice& gameEngine);
    virtual ~GameStateShutdown();
    GameStateShutdown(const GameStateShutdown&) = delete;
    GameStateShutdown& operator=(const GameStateShutdown&) = delete;

    void update(const float elapsedSeconds);

    void draw();

    void setActive();

    void setInactive();

private:
    leviathan::LeviathanDevice& gameEngine_;
};

#endif
