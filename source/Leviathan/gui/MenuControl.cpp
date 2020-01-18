#include "MenuControl.h"

namespace leviathan {
    namespace gui {
        MenuControl::MenuControl(irr::gui::IGUIEnvironment* guiEnv, input::IEventProducer& producer)
        : _guiEnv(guiEnv), _producer(producer)
        {
            _producer.subscribe(*this, irr::EET_GUI_EVENT);
        }

        MenuControl::~MenuControl() {
            _menus.clear();
            _producer.unsubscribe(*this, irr::EET_GUI_EVENT);
        }

        bool MenuControl::onEvent(const irr::SEvent& event) {
            (void)event;
            return false;
        }

        void MenuControl::addMenu(const char* name) {
            _menus[name] = std::make_unique<Menu>(_guiEnv);
        }

        void MenuControl::enable(const char* name) {
            _menus[name]->enable();
        }

        void MenuControl::disable(const char* name) {
            _menus[name]->disable();
        }

        void MenuControl::draw() {
            std::map<std::string, std::unique_ptr<Menu>>::iterator it = _menus.begin();
            for (; it != _menus.end(); ++it ) {
                it->second->draw();
            }
        }
    }
}
