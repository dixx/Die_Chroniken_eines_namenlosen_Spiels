#include "GameStateLoadGame.h"
#include "defines.h"
#include <ILeviathanDevice.h>
#include <characters/IHero.h>
#include <characters/IHeroes.h>
#include <core/IGameStateManager.h>
#include <video/ICamera.h>
#include <world/IDecorations.h>
#include <world/IGround.h>
#include <world/ILevel.h>
#include <world/Node3DConfiguration.h>

GameStateLoadGame::GameStateLoadGame(leviathan::ILeviathanDevice& gameEngine) : mGameEngine(gameEngine) {}

GameStateLoadGame::~GameStateLoadGame() {}

void GameStateLoadGame::update(const float elapsedSeconds) {
    (void)elapsedSeconds;
    if (!mFullyLoaded) {
        mGameEngine.Level().loadFromFile("gfx/levels/Level_Y.yaml");

        mGameEngine.Heroes().getActiveHero().setPosition(mGameEngine.Level().getSpawnPosition());

        mGameEngine.Decorations().add({"gfx/Fliegenpilz.3ds", "gfx/Fliegenpilz_Color.png",
            {10.8f, startingPosition.y, 10.8f}, {}, {}, {}, {.08f, .08f, .08f}});
        mGameEngine.Decorations().add({"gfx/Fliegenpilz.3ds", "gfx/Fliegenpilz_Color.png",
            {11.2f, startingPosition.y, 10.8f}, {}, {}, {}, {.09f, .09f, .09f}});
        mGameEngine.Decorations().add({"gfx/Fliegenpilz.3ds", "gfx/Fliegenpilz_Color.png",
            {10.8f, startingPosition.y, 11.2f}, {}, {}, {}, {.07f, .07f, .07f}});
        mGameEngine.Heroes().getActiveHero().setRotation({0.f, 0.f, 0.f});

        mGameEngine.Camera().setTargetPosition(mGameEngine.Level().getSpawnPosition());
        mGameEngine.Camera().update(0.f);  // TODO: why?

        mGameEngine.GameStateManager().transitTo(STATE_PLAY);
        mFullyLoaded = true;
    } else {
        mGameEngine.Decorations().unload();
        mGameEngine.Ground().unload();
        mGameEngine.GameStateManager().transitTo(STATE_MAIN_MENU);
        mFullyLoaded = false;
    }
}

void GameStateLoadGame::draw() {}
