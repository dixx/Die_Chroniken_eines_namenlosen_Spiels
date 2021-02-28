#ifndef GAMESTATE_LOAD_GAME_H
#define GAMESTATE_LOAD_GAME_H

#include "leviathan.h"

class GameStateLoadGame final : public leviathan::core::IGameState {
public:
    explicit GameStateLoadGame(leviathan::LeviathanDevice& gameEngine);
    virtual ~GameStateLoadGame();
    GameStateLoadGame(const GameStateLoadGame&) = delete;
    GameStateLoadGame& operator=(const GameStateLoadGame&) = delete;

    void update(const float elapsedSeconds);

    void draw();

    void setActive();

    void setInactive();

private:
    leviathan::LeviathanDevice& gameEngine_;
    bool fullyLoaded = false;
};

#endif
