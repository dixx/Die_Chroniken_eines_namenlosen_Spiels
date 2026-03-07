/*! \file DebugWindow.h
 *  \brief Eine Anzeige für Debug-Daten.
 *  \note Bestandteil der Leviathan Engine.
 *        Wird nur intern genutzt.
 */

#ifndef LEVIATHAN_GUI_DEBUG_WINDOW_H
#define LEVIATHAN_GUI_DEBUG_WINDOW_H

#include "Menu.h"
#include <IGUIEnvironment.h>
#include <IGUIStaticText.h>
#include <SColor.h>
#include <irrString.h>
#include <rect.h>
#include <string>

namespace irr {
    namespace video {
        class IVideoDriver;
    }
}

namespace leviathan {
    namespace gui {
        class DebugWindow {
        public:
            DebugWindow(irr::gui::IGUIEnvironment* guiEnv, irr::video::IVideoDriver* videoDriver);

            ~DebugWindow() = default;

            DebugWindow() = delete;
            DebugWindow(const DebugWindow&) = delete;
            DebugWindow(const DebugWindow&&) = delete;
            DebugWindow& operator=(const DebugWindow&) = delete;
            DebugWindow& operator=(const DebugWindow&&) = delete;

            void draw();

            template<typename T>
            void addEntry(const std::string& label, T value) {
                irr::core::stringw message = L"";
                message += label.c_str();
                message += ": ";
                message += value;
                auto text = mGuiEnv->addStaticText(
                    message.c_str(), irr::core::recti(10, 10, 50, 50), true, true, mWindow.menuElement, -1, true);
                if (text) {
                    text->setBackgroundColor(irr::video::SColor(100, 0, 0, 0));
                    text->setOverrideColor(irr::video::SColor(255, 247, 139, 7));
                }
            }

        private:
            irr::gui::IGUIEnvironment* mGuiEnv = nullptr;
            irr::video::IVideoDriver* mVideoDriver = nullptr;
            Menu mWindow;
        };
    }
}

#endif
