#include "Menu.h"
#include "IGUIElement.h"
#include "IGUIEnvironment.h"

namespace leviathan {
    namespace gui {
        Menu::Menu(irr::gui::IGUIEnvironment* guiEnv) : mGuiEnv(guiEnv) {
            // this only acts as a root element for a menu
            menuElement = mGuiEnv->addModalScreen(mGuiEnv->getRootGUIElement());
            if (!menuElement) return;
            menuElement->setEnabled(false);  // ignore clicks and buttons
        }

        void Menu::enable() {
            if (!menuElement) return;
            menuElement->setVisible(true);
        }

        void Menu::disable() {
            if (!menuElement) return;
            menuElement->setVisible(false);
        }

        void Menu::draw() {
            if (!menuElement) return;
            menuElement->draw();
        }
    }
}
