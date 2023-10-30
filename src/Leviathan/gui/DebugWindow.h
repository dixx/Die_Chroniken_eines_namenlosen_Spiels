/*! \file DebugWindow.h
 *  \brief Eine Anzeige für Debug-Daten.
 *  \note Bestandteil der Leviathan Engine.
 *        Wird nur intern genutzt.
 */

#ifndef LEVIATHAN_GUI_DEBUG_WINDOW_H
#define LEVIATHAN_GUI_DEBUG_WINDOW_H

#include "Menu.h"

namespace irr {
    namespace gui {
        class IGUIEnvironment;
    }
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

        private:
            irr::gui::IGUIEnvironment* mGuiEnv = nullptr;
            irr::video::IVideoDriver* mVideoDriver = nullptr;
            Menu mWindow;
        };
    }
}

#endif
