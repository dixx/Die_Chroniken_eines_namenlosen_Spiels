#include "Menu.h"

namespace leviathan {
    namespace gui {
        Menu::Menu(irr::gui::IGUIEnvironment* guiEnv) : _guiEnv(guiEnv) {
            menuElement = _guiEnv->addModalScreen(_guiEnv->getRootGUIElement());
        }

        void Menu::enable() {
          menuElement->setEnabled(true);
          menuElement->setVisible(true);
        }

        void Menu::disable() {
          menuElement->setEnabled(false);
          menuElement->setVisible(false);
        }

        void Menu::draw() {
            menuElement->draw();
        }
    }
}
