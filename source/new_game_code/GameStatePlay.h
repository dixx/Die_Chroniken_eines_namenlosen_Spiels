#ifndef GAMESTATEPLAY_H
#define GAMESTATEPLAY_H

#include "leviathan.h"

class GameStatePlay final : public leviathan::core::IGameState, leviathan::input::IActionConsumer {

public:
    enum actions { OPEN_IN_GAME_OPTIONS = 2 };

    explicit GameStatePlay(leviathan::LeviathanDevice& gameEngine);
    virtual ~GameStatePlay() final;
    GameStatePlay(const GameStatePlay&) = delete;
    GameStatePlay& operator=(const GameStatePlay&) = delete;

    void update(const float elapsedSeconds) final;

    void draw() final;

    void onAction(const uint32_t id, const bool isActive) final;

private:
    leviathan::LeviathanDevice& gameEngine_;
};

#endif
