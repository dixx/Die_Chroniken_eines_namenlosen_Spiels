/*! \file Menu.h
 *  \brief Ein Menü.
 *  \note Bestandteil der Leviathan Engine.
 *        Wird nur intern benutzt.
 */

#ifndef LEVIATHAN_GUI_MENU_H
#define LEVIATHAN_GUI_MENU_H

#include <memory>

namespace irr {
    namespace gui {
        class IGUIElement;
        class IGUIEnvironment;
    }
}

namespace leviathan {
    namespace gui {
        class Menu {
        public:
            irr::gui::IGUIElement* menuElement = nullptr;

            explicit Menu(irr::gui::IGUIEnvironment* guiEnv);

            ~Menu() = default;

            Menu() = delete;
            Menu(const Menu&) = delete;
            Menu(const Menu&&) = delete;
            Menu& operator=(const Menu&) = delete;
            Menu& operator=(const Menu&&) = delete;

            void enable();
            void disable();
            void draw();

        private:
            irr::gui::IGUIEnvironment* mGuiEnv = nullptr;
        };
    }
}
#endif
