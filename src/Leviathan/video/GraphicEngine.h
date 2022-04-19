/*  \file GraphicEngine.h
 *  \brief Wrapper für die Graphic Engine hinter Leviathan.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_VIDEO_GRAPHIC_ENGINE_H
#define LEVIATHAN_VIDEO_GRAPHIC_ENGINE_H

#include <cstdint>

namespace irr {
    class IEventReceiver;
    class IrrlichtDevice;

    namespace gui {
        class ICursorControl;
        class IGUIEnvironment;
    }

    namespace scene {
        class ISceneManager;
        class ISceneCollisionManager;
    }

    namespace video {
        class IVideoDriver;
    }
}

namespace leviathan {
    namespace core {
        class Configuration;
        struct ILogger;
    }

    namespace video {
        /*  \class GraphicEngine
         *  \brief Wrapper für die Graphic Engine hinter Leviathan.
         *         Momentan wird Irrlicht benutzt.
         */
        class GraphicEngine {
        public:
            explicit GraphicEngine(
                irr::IEventReceiver& receiver, core::ILogger& logger, const core::Configuration& config);

            ~GraphicEngine();

            GraphicEngine(const GraphicEngine&) = default;

            GraphicEngine() = delete;
            GraphicEngine(const GraphicEngine&&) = delete;
            GraphicEngine& operator=(const GraphicEngine&) = delete;
            GraphicEngine& operator=(const GraphicEngine&&) = delete;

            void closeDevice();

            irr::gui::ICursorControl* getCursorControl();

            irr::gui::IGUIEnvironment* getGUIEnvironment();

            irr::scene::ISceneManager* getSceneManager();

            irr::scene::ISceneCollisionManager* getCollisionManager();

            uint32_t getTime();

            irr::video::IVideoDriver* getVideoDriver();

            bool isWindowActive();

            bool run();

            void yield();

            static void overrideGraphicEngine(irr::IrrlichtDevice* otherEngine);

        private:
            static irr::IrrlichtDevice* graphicEngine_;
            static bool useExternalGraphicEngine;
        };
    }
}

#endif
