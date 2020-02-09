#include "MenuControl.h"

namespace leviathan {
    namespace gui {
        MenuControl::MenuControl(
            irr::gui::IGUIEnvironment* guiEnv,
            irr::video::IVideoDriver* videoDriver,
            input::IEventProducer& producer
        ) : _guiEnv(guiEnv), _videoDriver(videoDriver), _producer(producer)
        {
            _producer.subscribe(*this, irr::EET_GUI_EVENT);
        }

        MenuControl::~MenuControl() {
            _producer.unsubscribe(*this, irr::EET_GUI_EVENT);
            _menus.clear();
        }

        bool MenuControl::onEvent(const irr::SEvent& event) {
            (void)event;
            return false;
        }

        void MenuControl::addMenu(const wchar_t* name) {
            _menus[name] = std::make_unique<Menu>(_guiEnv);
        }

        void MenuControl::enable(const wchar_t* name) {
            _menus[name]->enable();
        }

        void MenuControl::disable(const wchar_t* name) {
            _menus[name]->disable();
        }

        void MenuControl::draw() {
            std::map<std::wstring, std::unique_ptr<Menu>>::iterator it = _menus.begin();
            for (; it != _menus.end(); ++it ) {
                it->second->draw();
            }
        }
    }
}
