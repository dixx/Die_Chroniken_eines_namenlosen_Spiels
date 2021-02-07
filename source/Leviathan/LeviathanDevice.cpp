#include "LeviathanDevice.h"
#include "video/constants.h"
#include <chrono>
#include <cstdint>
#include <exception>

namespace leviathan {
    LeviathanDevice::LeviathanDevice(const char* fileName)
    : configuration_(fileName), logger_(LOG_FILE_NAME, configuration_.getLoggingLevel()), gameStateManager_(logger_),
      actions_(eventReceiver_, logger_) {
        randomizer_.start(static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count()));
        initializeGraphicEngine();
        graphicEngine_->setEventReceiver(&eventReceiver_);
        textures_ = std::make_unique<video::Textures>(graphicEngine_->getVideoDriver(), logger_);
        mousePointerControl_ = std::make_unique<gui::MousePointerControl>(eventReceiver_, graphicEngine_, logger_);
        menuControl_ = std::make_unique<gui::MenuControl>(
            graphicEngine_->getGUIEnvironment(), graphicEngine_->getVideoDriver(), eventReceiver_);
        camera_ = std::make_unique<video::Camera>(graphicEngine_->getSceneManager(), configuration_);
        heroes_ = std::make_unique<characters::Heroes>(graphicEngine_->getSceneManager());
        ground_ = std::make_unique<world::Ground>(graphicEngine_->getSceneManager());
    }

    void LeviathanDevice::initializeGraphicEngine() {
        graphicEngine_ = irr::createDeviceEx(configuration_.getGraphicEngineParams());
        if (graphicEngine_ == nullptr) {
            logger_.text << "could not initialize Irrlicht Engine!";
            logger_.write(core::Logger::Level::INFO);
            throw std::runtime_error("could not initialize Irrlicht Engine!");
        }
    }

    LeviathanDevice::~LeviathanDevice() {
        if (graphicEngine_) {
            graphicEngine_->drop();
            graphicEngine_ = nullptr;
        }
    }

    void LeviathanDevice::run() {
        const float FRAME_DELTA_TIME = 1.f / static_cast<float>(configuration_.getMaxFPS());
        const uint32_t FRAME_DELTA_TIME_IN_MILLISECONDS = 1000 / configuration_.getMaxFPS();  // for performance.
        uint32_t nextDrawingTime = graphicEngine_->getTimer()->getTime();

        while (graphicEngine_->run()) {
            handleWindowInactivity();
            uint32_t loops = 0;
            bool drawNextFrame = false;
            while (graphicEngine_->getTimer()->getTime() > nextDrawingTime
                   && loops < 10)  // in-game time will slow down if framerate drops below 10% of maxFPS // FIXME for
                                   // FPS > 250
            {
                updateGame(FRAME_DELTA_TIME);
                if (!graphicEngine_->run()) {
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
        if (!graphicEngine_->isWindowActive()) graphicEngine_->yield();
    }

    void LeviathanDevice::updateGame(const float frameDeltaTime) {
        timeControl_.tick(frameDeltaTime);
        gameStateManager_.update(frameDeltaTime);
    }

    void LeviathanDevice::drawGame() {
        graphicEngine_->getVideoDriver()->beginScene(true, true, leviathan::video::COL_GREEN);
        graphicEngine_->getSceneManager()->drawAll();
        gameStateManager_.draw();
        graphicEngine_->getVideoDriver()->endScene();
    }

    void LeviathanDevice::halt() {
        graphicEngine_->closeDevice();
    }

    core::Logger& LeviathanDevice::Logger() {
        return logger_;
    }

    core::TimeControl& LeviathanDevice::TimeControl() {
        return timeControl_;
    }

    core::Configuration& LeviathanDevice::Configuration() {
        return configuration_;
    }

    core::GameStateManager& LeviathanDevice::GameStateManager() {
        return gameStateManager_;
    }

    core::Randomizer& LeviathanDevice::Randomizer() {
        return randomizer_;
    }

    characters::Heroes& LeviathanDevice::Heroes() {
        return *heroes_;
    }

    gui::MenuControl& LeviathanDevice::MenuControl() {
        return *menuControl_;
    }

    gui::MousePointerControl& LeviathanDevice::MousePointerControl() {
        return *mousePointerControl_;
    }

    input::Actions& LeviathanDevice::Actions() {
        return actions_;
    }

    input::EventReceiver& LeviathanDevice::EventReceiver() {
        return eventReceiver_;
    }

    video::Camera& LeviathanDevice::Camera() {
        return *camera_;
    }

    world::Ground& LeviathanDevice::Ground() {
        return *ground_;
    }
}
