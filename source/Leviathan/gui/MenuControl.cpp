#include "MenuControl.h"
#include "../video/Constants.h"

namespace leviathan {
    namespace gui {
        MenuControl::MenuControl(
            irr::gui::IGUIEnvironment* guiEnv,
            irr::video::IVideoDriver* videoDriver,
            input::IEventProducer& producer
        ) : _guiEnv(guiEnv), _videoDriver(videoDriver), _producer(producer)
        {
            _producer.subscribe(*this, irr::EET_MOUSE_INPUT_EVENT);
            _producer.subscribe(*this, irr::EET_KEY_INPUT_EVENT);
            _producer.subscribe(*this, irr::EET_GUI_EVENT);
        }

        MenuControl::~MenuControl() {
            _producer.unsubscribe(*this, irr::EET_MOUSE_INPUT_EVENT);
            _producer.unsubscribe(*this, irr::EET_KEY_INPUT_EVENT);
            _producer.unsubscribe(*this, irr::EET_GUI_EVENT);
            _menus.clear();
        }

        bool MenuControl::onEvent(const irr::SEvent& event) {
            // GUI Env needs these events to decide if they result in a GUI event
            return (_guiEnv->postEventFromUser(event));
        }

        void MenuControl::addMenu(const wchar_t* name) {
            _menus[name] = std::make_unique<Menu>(_guiEnv);
        }

        void MenuControl::addButton(
            const wchar_t* menuName,
            const wchar_t* buttonName,
            const ButtonConfiguration& config
        ) {
            irr::gui::IGUIButton* newButton = _guiEnv->addButton(
                irr::core::recti(
                    irr::core::position2di(config.relativePositionInMenu.x, config.relativePositionInMenu.y),
                    irr::core::dimension2du(config.dimension.w, config.dimension.h)
                ),
                _menus[menuName].get()->menuElement,
                -1,
                buttonName
            );
            newButton->setIsPushButton(false);
            newButton->setDrawBorder(false);
            newButton->setUseAlphaChannel(config.hasImageTransparence);
            irr::video::ITexture* imageCatalogue = loadTexture(config.imageFileName, config.hasImageTransparence);
            newButton->setImage(
                imageCatalogue,
                irr::core::recti(
                    irr::core::position2di(config.inactivePositionOnImage.x, config.inactivePositionOnImage.y),
                    irr::core::dimension2du(config.dimension.w, config.dimension.h)
                )
            );
            newButton->setPressedImage(
                imageCatalogue,
                irr::core::recti(
                    irr::core::position2di(config.activePositionOnImage.x, config.activePositionOnImage.y),
                    irr::core::dimension2du(config.dimension.w, config.dimension.h)
                )
            );
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

        /* private */

        irr::video::ITexture* MenuControl::loadTexture(const std::string& filename, bool makeTransparent)
        {
            // GenericHelperMethods& helper = GenericHelperMethods::getInstance();
            // helper.validateFileExistence( "GFX/menues1.bmp" );
            _videoDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);  // no LOD textures
            irr::video::ITexture* texture = _videoDriver->getTexture(filename.c_str());
            if (makeTransparent) {
                // if (!texture->hasAlpha()) {
                    _videoDriver->makeColorKeyTexture(texture, video::COL_MAGICPINK);
                // }
            }
            return texture;
        }
    }
}
