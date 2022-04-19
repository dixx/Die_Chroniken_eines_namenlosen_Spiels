#ifndef GAMESTATESHUTDOWN_H
#define GAMESTATESHUTDOWN_H

#include <core/IGameState.h>

namespace leviathan {
    struct ILeviathanDevice;
}

class GameStateShutdown final : public leviathan::core::IGameState {
public:
    explicit GameStateShutdown(leviathan::ILeviathanDevice& gameEngine);
    ~GameStateShutdown();

    GameStateShutdown() = delete;
    GameStateShutdown(const GameStateShutdown&) = delete;
    GameStateShutdown(const GameStateShutdown&&) = delete;
    GameStateShutdown& operator=(const GameStateShutdown&) = delete;
    GameStateShutdown& operator=(const GameStateShutdown&&) = delete;

    void update(const float elapsedSeconds);

    void draw();

private:
    leviathan::ILeviathanDevice& gameEngine_;
};

#endif
