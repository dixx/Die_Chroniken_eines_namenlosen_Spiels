/*! \file Menu.h
 *  \brief Ein Menü.
 *  \note Bestandteil der Leviathan Engine.
 *        Wird nur intern benutzt.
 */

#ifndef LEVIATHAN_GUI_MENU_H
#define LEVIATHAN_GUI_MENU_H

#include <memory>
#include "irrlicht.h"

namespace leviathan {
    namespace gui {
        class Menu {
          Menu() = delete;
          Menu(const Menu&) = delete;
          Menu& operator=(const Menu&) = delete;

        public:
            explicit Menu(irr::gui::IGUIEnvironment* guiEnv);
            ~Menu() {};
            void enable();
            void disable();
            void draw();

        private:
            irr::gui::IGUIEnvironment* _guiEnv = nullptr;
            irr::gui::IGUIElement* _menuElement = nullptr;
        };
    }
}
#endif
