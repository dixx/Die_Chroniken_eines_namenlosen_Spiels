#ifndef GAMESTATESHUTDOWN_H
#define GAMESTATESHUTDOWN_H

#include <ILeviathanDevice.h>
#include <core/IGameState.h>

class GameStateShutdown final : public leviathan::core::IGameState {
public:
    explicit GameStateShutdown(leviathan::ILeviathanDevice& gameEngine);
    virtual ~GameStateShutdown();
    GameStateShutdown(const GameStateShutdown&) = delete;
    GameStateShutdown& operator=(const GameStateShutdown&) = delete;

    void update(const float elapsedSeconds);

    void draw();

private:
    leviathan::ILeviathanDevice& gameEngine_;
};

#endif
