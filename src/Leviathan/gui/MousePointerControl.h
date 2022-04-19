/*! \file MousePointerControl.h
 *  \brief Bietet Zugriff auf die Darstellung des Mauszeigers.
 *  \note Bestandteil der Leviathan Engine
 */
#ifndef LEVIATHAN_GUI_MOUSEPOINTER_H
#define LEVIATHAN_GUI_MOUSEPOINTER_H

#include "../input/IEventConsumer.h"
#include "../video/GraphicEngine.h"
#include "SColor.h"
#include "rect.h"
#include "vector2d.h"
#include <cstdint>
#include <gui/IMousePointerControl.h>
#include <unordered_map>

namespace irr {
    namespace video {
        class ITexture;
        struct PPosition2D;
    }
}

namespace leviathan {
    namespace core {
        struct ILogger;
    }
    namespace input {
        struct IEventProducer;
    }
    namespace video {
        class GraphicEngine;
        class Textures;
    }

    namespace gui {

        /*! \class MousePointerControl
         *  \brief Bietet Zugriff auf die Darstellung des Mauszeigers
         */
        class MousePointerControl final : public IMousePointerControl, public input::IEventConsumer {
        public:
            /*! \brief Konstruktor.
             *  \param producer: produziert (versendet) Events
             *  \param graphicDevice: initialisiertes Irrlicht Device
             *  \param logger: Instanz eines Loggers
             *  \param textures: Instanz der Texturenverwaltung
             */
            MousePointerControl(leviathan::input::IEventProducer& producer, video::GraphicEngine& graphicDevice,
                leviathan::core::ILogger& logger, leviathan::video::Textures& textures);

            ~MousePointerControl() = default;

            MousePointerControl() = delete;
            MousePointerControl(const MousePointerControl&) = delete;
            MousePointerControl(const MousePointerControl&&) = delete;
            MousePointerControl& operator=(const MousePointerControl&) = delete;
            MousePointerControl& operator=(const MousePointerControl&&) = delete;

            /*! \brief Reagiert auf Events vom Producer.
             *  \param event: Input-Event
             *  \return `true` wenn der Event behandelt werden konnte, ansonsten `false`
             */
            bool onEvent(const irr::SEvent& event);

            void addMousePointer(const uint32_t id, const MousePointerConfiguration& configuration) override;

            void setActiveMousPointer(const uint32_t id) override;

            const video::Position2D getPosition() const override;

            void draw() override;

        private:
            leviathan::core::ILogger& mLogger;
            leviathan::video::Textures& mTextures;
            uint32_t mActiveMousePointer = 0;
            const irr::video::SColor mBackgroundColor = irr::video::SColor(255, 255, 255, 255);
            irr::core::vector2di mPosition = irr::core::vector2di(0, 0);
            video::GraphicEngine mGraphicDevice;
            std::unordered_map<uint32_t, irr::video::ITexture*> mBaseImage =
                std::unordered_map<uint32_t, irr::video::ITexture*>({{0, nullptr}});
            std::unordered_map<uint32_t, irr::core::recti> mImageArea = std::unordered_map<uint32_t, irr::core::recti>(
                {{0, irr::core::recti(0, 0, 0, 0)}});
            std::unordered_map<uint32_t, irr::core::vector2di> mHotSpot =
                std::unordered_map<uint32_t, irr::core::vector2di>({{0, irr::core::vector2di(0, 0)}});
        };
    }
}

#endif
