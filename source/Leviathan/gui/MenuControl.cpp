#include "MenuControl.h"

namespace leviathan {
    namespace gui {
        MenuControl::MenuControl(irr::gui::IGUIEnvironment* guiEnv, input::IEventProducer& producer)
        : _guiEnv(guiEnv)
        {
            producer.subscribe(*this, irr::EET_GUI_EVENT);
        }

        bool MenuControl::onEvent(const irr::SEvent& event) {
            (void)event;
            return false;
        }
    }
}
