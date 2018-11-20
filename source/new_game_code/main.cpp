#include "GameStatePlay.h"
#include "GameStateShutdown.h"
#include "defines.h"
#include "leviathan.h"

int main() {
    leviathan::LeviathanDevice gameEngine;
    gameEngine.init("config.ini");
    gameEngine.Actions().loadFromFile("./game_state_play_action_mappings.yaml");
    GameStatePlay play(gameEngine);
    GameStateShutdown shutdown(gameEngine);

    leviathan::core::GameStateManager& game = gameEngine.GameStateManager();
    game.add(play, STATE_PLAY);
    game.add(shutdown, STATE_SHUTDOWN);

    game.transitTo(STATE_PLAY);
    gameEngine.run();
    return gameEngine.exitStatus();
}
