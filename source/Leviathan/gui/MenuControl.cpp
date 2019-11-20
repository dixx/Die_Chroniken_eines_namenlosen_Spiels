#include "MenuControl.h"

namespace leviathan {
    namespace gui {
        MenuControl::MenuControl(irr::gui::IGUIEnvironment* guiEnv, input::IEventProducer& producer)
        : _guiEnv(guiEnv), _producer(producer)
        {
            _producer.subscribe(*this, irr::EET_GUI_EVENT);
        }

        MenuControl::~MenuControl() {
            _producer.unsubscribe(*this, irr::EET_GUI_EVENT);
        }

        bool MenuControl::onEvent(const irr::SEvent& event) {
            (void)event;
            return false;
        }

        irr::gui::IGUIElement* MenuControl::add(const char* name) {
            (void)name;
            return _guiEnv->addModalScreen(_guiEnv->getRootGUIElement());
        }
    }
}
