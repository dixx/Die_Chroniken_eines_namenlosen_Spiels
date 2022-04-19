#include "GraphicEngine.h"
#include "../core/Configuration.h"
#include "ICursorControl.h"
#include "IEventReceiver.h"
#include "IGUIEnvironment.h"
#include "ISceneManager.h"
#include "IVideoDriver.h"
#include "IrrlichtDevice.h"
#include "irrlicht.h"
#include <core/ILogger.h>
#include <exception>

namespace leviathan {
    namespace video {
        irr::IrrlichtDevice* GraphicEngine::mGraphicEngine;
        bool GraphicEngine::mUseExternalGraphicEngine;

        GraphicEngine::GraphicEngine(
            irr::IEventReceiver& receiver, core::ILogger& logger, const core::Configuration& config) {
            if (!mUseExternalGraphicEngine && mGraphicEngine == nullptr) {
                mGraphicEngine = irr::createDeviceEx(config.getGraphicEngineParams());
                if (mGraphicEngine == nullptr) {
                    logger.text << "could not initialize Irrlicht Engine!";
                    logger.write(logger.Level::INFO);
                    throw std::runtime_error("could not initialize Irrlicht Engine!");
                }
            } else {
                logger.text << "using external Irrlicht Engine.";
                logger.write(logger.Level::INFO);
            }
            mGraphicEngine->setEventReceiver(&receiver);
        }

        GraphicEngine::~GraphicEngine() {
            if (!mUseExternalGraphicEngine && mGraphicEngine) {
                // With the current static LeviathanDevice instance, when using DIRECT3D driver,
                // the graphicEngine->drop() call does not return and prevents the application from closing.
                // TODO: try again with irrlicht > 1.8.4
                if (getVideoDriver()->getDriverType() != irr::video::EDT_DIRECT3D9) mGraphicEngine->drop();
                mGraphicEngine = nullptr;
            }
        }

        void GraphicEngine::closeDevice() {
            mGraphicEngine->closeDevice();
        }

        irr::gui::ICursorControl* GraphicEngine::getCursorControl() {
            return mGraphicEngine->getCursorControl();
        }

        irr::gui::IGUIEnvironment* GraphicEngine::getGUIEnvironment() {
            return mGraphicEngine->getGUIEnvironment();
        }

        irr::scene::ISceneManager* GraphicEngine::getSceneManager() {
            return mGraphicEngine->getSceneManager();
        }

        irr::scene::ISceneCollisionManager* GraphicEngine::getCollisionManager() {
            return getSceneManager()->getSceneCollisionManager();
        }

        uint32_t GraphicEngine::getTime() {
            return mGraphicEngine->getTimer()->getTime();
        }

        irr::video::IVideoDriver* GraphicEngine::getVideoDriver() {
            return mGraphicEngine->getVideoDriver();
        }

        bool GraphicEngine::isWindowActive() {
            return mGraphicEngine->isWindowActive();
        }

        bool GraphicEngine::run() {
            return mGraphicEngine->run();
        }

        void GraphicEngine::yield() {
            mGraphicEngine->yield();
        }

        void GraphicEngine::overrideGraphicEngine(irr::IrrlichtDevice* otherEngine) {
            if (mGraphicEngine == nullptr && otherEngine != nullptr) {
                mGraphicEngine = otherEngine;
                mUseExternalGraphicEngine = true;
            }
            if (mUseExternalGraphicEngine && otherEngine == nullptr) {
                mGraphicEngine = nullptr;
                mUseExternalGraphicEngine = false;
            }
        }
    }
}
