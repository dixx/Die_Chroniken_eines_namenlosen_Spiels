/*! \file MousePointerControl.h
 *  \brief Bietet Zugriff auf die Darstellung des Mauszeigers.
 *  \note Bestandteil der Leviathan Engine
 */
#ifndef LEVIATHAN_GUI_MOUSEPOINTER_H
#define LEVIATHAN_GUI_MOUSEPOINTER_H

#include "../core/Logger.h"
#include "../input/IEventConsumer.h"
#include "../input/IEventProducer.h"
#include "../video/GraphicEngine.h"
#include "../video/Textures.h"
#include "irrlicht.h"
#include <cstdint>
#include <gui/IMousePointerControl.h>
#include <unordered_map>

namespace leviathan {
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
                leviathan::core::Logger& logger, leviathan::video::Textures& textures);

            ~MousePointerControl() {};

            MousePointerControl() = delete;
            MousePointerControl(const MousePointerControl&) = delete;
            MousePointerControl& operator=(const MousePointerControl&) = delete;

            /*! \brief Reagiert auf Events vom Producer.
             *  \param event: Input-Event
             *  \return `true` wenn der Event behandelt werden konnte, ansonsten `false`
             */
            bool onEvent(const irr::SEvent& event);

            /*! \brief Erstellt einen anzeigbaren Mauszeiger aus einem Bild.
             *  \param id: ID des Mauszeigers
             *  \param imageFileName: Dateiname (mit Pfad) des Ausgangsbildes
             *  \param imageArea: zu verwendender Bildausschnitt
             *  \param hotSpot: Punkt innerhalb des resultierenden Bildausschnittes, der als "Mauszeiger-Spitze" dient
             */
            void addMousePointer(const uint32_t id, const irr::io::path& imageFileName,
                const irr::core::recti& imageArea, const irr::core::vector2di& hotSpot);

            /*! \brief Wählt den anzuzeigenden Mauspfeil aus.
             *  \param id: ID des anzuzeigenden Mauszeigers
             */
            void setActiveMousPointer(const uint32_t id);

            /*! \brief Zeichnet den Mauszeiger auf den Bildschirm
             */
            void draw();

        private:
            leviathan::core::Logger& logger_;
            leviathan::video::Textures& textures_;
            uint32_t activeMousePointer_ = 0;
            const irr::video::SColor backgroundColor_ = irr::video::SColor(255, 255, 255, 255);
            irr::core::vector2di position_ = irr::core::vector2di(0, 0);
            video::GraphicEngine graphicDevice_;
            std::unordered_map<uint32_t, irr::video::ITexture*> baseImage_ =
                std::unordered_map<uint32_t, irr::video::ITexture*>({{0, nullptr}});
            std::unordered_map<uint32_t, irr::core::recti> imageArea_ = std::unordered_map<uint32_t, irr::core::recti>(
                {{0, irr::core::recti(0, 0, 0, 0)}});
            std::unordered_map<uint32_t, irr::core::vector2di> hotSpot_ =
                std::unordered_map<uint32_t, irr::core::vector2di>({{0, irr::core::vector2di(0, 0)}});
        };
    }
}

#endif
