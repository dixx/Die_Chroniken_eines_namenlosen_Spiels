#ifndef GAMESTATE_LOAD_GAME_H
#define GAMESTATE_LOAD_GAME_H

#include <core/IGameState.h>

namespace leviathan {
    struct ILeviathanDevice;
}

class GameStateLoadGame final : public leviathan::core::IGameState {
public:
    explicit GameStateLoadGame(leviathan::ILeviathanDevice& gameEngine);
    ~GameStateLoadGame();

    GameStateLoadGame() = delete;
    GameStateLoadGame(const GameStateLoadGame&) = delete;
    GameStateLoadGame(const GameStateLoadGame&&) = delete;
    GameStateLoadGame& operator=(const GameStateLoadGame&) = delete;
    GameStateLoadGame& operator=(const GameStateLoadGame&&) = delete;

    void update(const float elapsedSeconds);

    void draw();

private:
    leviathan::ILeviathanDevice& gameEngine_;
    bool fullyLoaded = false;
};

#endif
