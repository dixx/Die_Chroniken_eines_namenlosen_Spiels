#ifndef GAMESTATESHUTDOWN_H
#define GAMESTATESHUTDOWN_H

#include "leviathan.h"

class GameStateShutdown final : public leviathan::core::GameState {

public:

    explicit GameStateShutdown(leviathan::LeviathanDevice& gameEngine);

    virtual ~GameStateShutdown() final;

    GameStateShutdown(const GameStateShutdown&) = delete;
    GameStateShutdown& operator=(const GameStateShutdown&) = delete;

    void update(const float elapsedSeconds) final;

    void draw() final;

private:
    leviathan::LeviathanDevice& gameEngine_;
};

#endif