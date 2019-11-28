#include "MenuControl.h"

namespace leviathan {
    namespace gui {
        MenuControl::MenuControl(irr::gui::IGUIEnvironment* guiEnv, input::IEventProducer& producer)
        : _guiEnv(guiEnv), _producer(producer)
        {
            _producer.subscribe(*this, irr::EET_GUI_EVENT);
        }

        MenuControl::~MenuControl() {
            for (auto menu : _menus) {
                menu.second->drop();
            }
            _producer.unsubscribe(*this, irr::EET_GUI_EVENT);
        }

        bool MenuControl::onEvent(const irr::SEvent& event) {
            (void)event;
            return false;
        }

        irr::gui::IGUIElement* MenuControl::addMenu(const char* name) {
            auto menu = _guiEnv->addModalScreen(_guiEnv->getRootGUIElement());
            menu->grab();
            _menus[name] = menu;
            return menu;
        }

        void MenuControl::enable(const char* name) {
            auto menu = _menus[name];
            menu->setEnabled(true);
            menu->setVisible(true);
        }

        void MenuControl::disable(const char* name) {
            auto menu = _menus[name];
            menu->setEnabled(false);
            menu->setVisible(false);
        }

        void MenuControl::draw() {
            for (auto menu : _menus) {
                menu.second->draw();
            }
        }
    }
}
