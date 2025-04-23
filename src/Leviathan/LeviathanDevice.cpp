#include "LeviathanDevice.h"
#include "ISceneManager.h"
#include "IVideoDriver.h"
#include "video/constants.h"
#include <characters/IHeroes.h>
#include <chrono>
#include <core/IConfiguration.h>
#include <core/IGameStateManager.h>
#include <cstdint>
#include <gui/IMenuControl.h>
#include <gui/IMousePointerControl.h>
#include <input/IActions.h>
#include <world/ICollider.h>
#include <world/IGround.h>
#include <world/ILevel.h>

namespace leviathan {
    LeviathanDevice::LeviathanDevice(const char* configFileName)
    : mConfiguration(configFileName), mLogger(LOG_FILE_NAME, mConfiguration.getLoggingLevel()), mTimeControl(),
      mGameStateManager(mLogger), mRandomizer(), mEventReceiver(), mActions(mEventReceiver, mLogger),
      mGraphicEngine(mEventReceiver, mLogger, mConfiguration) {
        mRandomizer.start(static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count()));
        mTextures = std::make_unique<video::Textures>(mGraphicEngine.getVideoDriver(), mLogger);
        mMousePointerControl = std::make_unique<gui::MousePointerControl>(
            mEventReceiver, mGraphicEngine, mLogger, *mTextures);
        mDebugWindow = std::make_unique<gui::DebugWindow>(
            mGraphicEngine.getGUIEnvironment(), mGraphicEngine.getVideoDriver());
        mMenuControl = std::make_unique<gui::MenuControl>(
            mGraphicEngine.getGUIEnvironment(), mGraphicEngine.getVideoDriver(), mEventReceiver, *mTextures);
        mCamera = std::make_unique<video::Camera>(mGraphicEngine.getSceneManager(), mConfiguration);
        mCollider = std::make_unique<world::Collider>(mGraphicEngine.getSceneManager());
        mNodeManager = std::make_unique<world::NodeManager>(mGraphicEngine.getSceneManager(), *mTextures);
        mGround = std::make_unique<world::Ground>(*mNodeManager);
        mLevel = std::make_unique<world::Level>(*mNodeManager, *mGround);
        mHeroes = std::make_unique<characters::Heroes>(*mNodeManager);
    }

    void LeviathanDevice::run() {
        const float FRAME_DELTA_TIME = 1.f / static_cast<float>(mConfiguration.getMaxFPS());
        const uint32_t FRAME_DELTA_TIME_IN_MILLISECONDS = 1000 / mConfiguration.getMaxFPS();  // for performance.
        uint32_t nextDrawingTime = mGraphicEngine.getTime();

        while (mGraphicEngine.run()) {
            handleWindowInactivity();
            uint32_t loops = 0;
            bool drawNextFrame = false;
            while (mGraphicEngine.getTime() > nextDrawingTime
                   && loops < 10)  // in-game time will slow down if framerate drops below 10% of maxFPS // FIXME for
                                   // FPS > 250
            {
                updateGame(FRAME_DELTA_TIME);
                if (!mGraphicEngine.run()) {
                    drawNextFrame = false;
                    break;
                }
                drawNextFrame = true;
                nextDrawingTime += FRAME_DELTA_TIME_IN_MILLISECONDS;
                ++loops;
            }
            if (drawNextFrame) drawGame();
        }
    }

    void LeviathanDevice::handleWindowInactivity() {
        if (!mGraphicEngine.isWindowActive()) mGraphicEngine.yield();
    }

    void LeviathanDevice::updateGame(const float frameDeltaTime) {
        mTimeControl.tick(frameDeltaTime);
        mGameStateManager.update(frameDeltaTime);
    }

    void LeviathanDevice::drawGame() {
        mDebugWindow->addEntry("FPS", mGraphicEngine.getVideoDriver()->getFPS());
        mGraphicEngine.getVideoDriver()->beginScene(true, true, video::COL_GREEN);
        mGraphicEngine.getSceneManager()->drawAll();
        mGameStateManager.draw();
        mDebugWindow->draw();
        mGraphicEngine.getVideoDriver()->endScene();
    }

    void LeviathanDevice::halt() {
        mGraphicEngine.closeDevice();
    }

    core::ILogger& LeviathanDevice::Logger() {
        return mLogger;
    }

    core::TimeControl& LeviathanDevice::TimeControl() {
        return mTimeControl;
    }

    core::IConfiguration& LeviathanDevice::Configuration() {
        return mConfiguration;
    }

    core::IGameStateManager& LeviathanDevice::GameStateManager() {
        return mGameStateManager;
    }

    core::Randomizer& LeviathanDevice::Randomizer() {
        return mRandomizer;
    }

    characters::IHeroes& LeviathanDevice::Heroes() {
        return *mHeroes;
    }

    gui::IMenuControl& LeviathanDevice::MenuControl() {
        return *mMenuControl;
    }

    gui::IMousePointerControl& LeviathanDevice::MousePointerControl() {
        return *mMousePointerControl;
    }

    input::IActions& LeviathanDevice::Actions() {
        return mActions;
    }

    input::EventReceiver& LeviathanDevice::EventReceiver() {
        return mEventReceiver;
    }

    video::ICamera& LeviathanDevice::Camera() {
        return *mCamera;
    }

    world::ICollider& LeviathanDevice::Collider() {
        return *mCollider;
    }

    world::IGround& LeviathanDevice::Ground() {
        return *mGround;
    }

    world::ILevel& LeviathanDevice::Level() {
        return *mLevel;
    }
}
