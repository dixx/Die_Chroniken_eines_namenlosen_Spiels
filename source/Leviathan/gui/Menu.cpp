#include "Menu.h"

namespace leviathan {
    namespace gui {
        Menu::Menu(irr::gui::IGUIEnvironment* guiEnv) : _guiEnv(guiEnv) {
            _menuElement = _guiEnv->addModalScreen(_guiEnv->getRootGUIElement());
        }

        void Menu::enable() {
          _menuElement->setEnabled(true);
          _menuElement->setVisible(true);
        }

        void Menu::disable() {
          _menuElement->setEnabled(false);
          _menuElement->setVisible(false);
        }

        void Menu::draw() {
            _menuElement->draw();
        }
    }
}
