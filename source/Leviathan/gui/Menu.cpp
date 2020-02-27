#include "Menu.h"

namespace leviathan {
    namespace gui {
        Menu::Menu(irr::gui::IGUIEnvironment* guiEnv) : _guiEnv(guiEnv) {
            // this only acts as a root element for a menu
            menuElement = _guiEnv->addModalScreen(_guiEnv->getRootGUIElement());
            menuElement->setEnabled(false); // ignore clicks and buttons
        }

        void Menu::enable() {
            menuElement->setVisible(true);
        }

        void Menu::disable() {
            menuElement->setVisible(false);
        }

        void Menu::draw() {
            menuElement->draw();
        }
    }
}
