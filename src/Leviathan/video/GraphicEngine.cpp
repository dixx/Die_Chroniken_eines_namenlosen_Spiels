#include "GraphicEngine.h"
#include "../core/Configuration.h"
#include "../core/Logger.h"
#include <exception>
#include <irrlicht.h>

namespace leviathan {
    namespace video {
        irr::IrrlichtDevice* GraphicEngine::graphicEngine_;
        bool GraphicEngine::useExternalGraphicEngine;

        GraphicEngine::GraphicEngine(
            irr::IEventReceiver& receiver, core::Logger& logger, const core::Configuration& config) {
            if (!useExternalGraphicEngine && graphicEngine_ == nullptr) {
                graphicEngine_ = irr::createDeviceEx(config.getGraphicEngineParams());
                if (graphicEngine_ == nullptr) {
                    logger.text << "could not initialize Irrlicht Engine!";
                    logger.write(core::Logger::Level::INFO);
                    throw std::runtime_error("could not initialize Irrlicht Engine!");
                }
            } else {
                logger.text << "using external Irrlicht Engine.";
                logger.write(core::Logger::Level::INFO);
            }
            graphicEngine_->setEventReceiver(&receiver);
        }

        GraphicEngine::~GraphicEngine() {
            if (!useExternalGraphicEngine && graphicEngine_) {
                graphicEngine_->drop();
                graphicEngine_ = nullptr;
            }
        }

        void GraphicEngine::closeDevice() {
            graphicEngine_->closeDevice();
        }

        irr::gui::ICursorControl* GraphicEngine::getCursorControl() {
            return graphicEngine_->getCursorControl();
        }

        irr::gui::IGUIEnvironment* GraphicEngine::getGUIEnvironment() {
            return graphicEngine_->getGUIEnvironment();
        }

        irr::scene::ISceneManager* GraphicEngine::getSceneManager() {
            return graphicEngine_->getSceneManager();
        }

        uint32_t GraphicEngine::getTime() {
            return graphicEngine_->getTimer()->getTime();
        }

        irr::video::IVideoDriver* GraphicEngine::getVideoDriver() {
            return graphicEngine_->getVideoDriver();
        }

        bool GraphicEngine::isWindowActive() {
            return graphicEngine_->isWindowActive();
        }

        bool GraphicEngine::run() {
            return graphicEngine_->run();
        }

        void GraphicEngine::yield() {
            graphicEngine_->yield();
        }

        void GraphicEngine::overrideGraphicEngine(irr::IrrlichtDevice* otherEngine) {
            if (graphicEngine_ == nullptr && otherEngine != nullptr) {
                graphicEngine_ = otherEngine;
                useExternalGraphicEngine = true;
            }
            if (useExternalGraphicEngine && graphicEngine_ != nullptr && otherEngine == nullptr) {
                graphicEngine_ = otherEngine;
                useExternalGraphicEngine = false;
            }
        }
    }
}
