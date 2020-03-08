#include "GameStateMainMenu.h"
#include "GameStatePlay.h"
#include "GameStateShutdown.h"
#include "defines.h"
#include "leviathan.h"
#include <exception>

int main() {
    try {
        leviathan::LeviathanDevice gameEngine("./config.ini");
        gameEngine.Actions().loadFromFile("./action_mappings.yaml");

        leviathan::core::GameStateManager& game = gameEngine.GameStateManager();
        GameStateMainMenu mainMenu(gameEngine);
        game.add(mainMenu, STATE_MAIN_MENU);
        GameStatePlay play(gameEngine);
        game.add(play, STATE_PLAY);
        GameStateShutdown shutdown(gameEngine);
        game.add(shutdown, STATE_SHUTDOWN);

        game.transitTo(STATE_MAIN_MENU);
        gameEngine.run();
    } catch (std::runtime_error& _) { return 1; }
    return 0;
}
