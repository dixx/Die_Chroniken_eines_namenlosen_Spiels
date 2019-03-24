#include "GameStatePlay.h"
#include "GameStateShutdown.h"
#include "defines.h"
#include "leviathan.h"
#include <exception>

int main() {
    try {
        leviathan::LeviathanDevice gameEngine("config.ini");
        gameEngine.Actions().loadFromFile("./game_state_play_action_mappings.yaml");
        GameStatePlay play(gameEngine);
        GameStateShutdown shutdown(gameEngine);

        leviathan::core::GameStateManager& game = gameEngine.GameStateManager();
        game.add(play, STATE_PLAY);
        game.add(shutdown, STATE_SHUTDOWN);

        game.transitTo(STATE_PLAY);
        gameEngine.run();
    } catch (std::runtime_error) {
        return 1;
    }
    return 0;
}
