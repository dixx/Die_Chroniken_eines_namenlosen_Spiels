#include "MenuControl.h"
#include "../video/Constants.h"
#include <cstdint>

namespace leviathan {
    namespace gui {
        MenuControl::MenuControl(
            irr::gui::IGUIEnvironment* guiEnv, irr::video::IVideoDriver* videoDriver, input::IEventProducer& producer)
        : _guiEnv(guiEnv), _videoDriver(videoDriver), _producer(producer) {
            _producer.subscribe(*this, irr::EET_MOUSE_INPUT_EVENT);
            _producer.subscribe(*this, irr::EET_KEY_INPUT_EVENT);
            _producer.subscribe(*this, irr::EET_GUI_EVENT);
            _guiEnv->addEmptySpriteBank("virtual/buttonSprites");
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

        void MenuControl::addMenu(const wchar_t* name, const MenuConfiguration& config) {
            _menus[name] = std::make_unique<Menu>(_guiEnv);
            irr::core::dimension2du dimension(config.dimension.w, config.dimension.h);
            irr::core::position2di position(config.position.x, config.position.y);
            irr::core::position2di positionOnImage(config.positionOnImage.x, config.positionOnImage.y);
            irr::video::ITexture* textureCatalogue = loadTexture(config.imageFileName, config.hasImageTransparence);
            std::wstring virtualFileName(L"virtual/menuBackground - ");
            virtualFileName += name;
            irr::video::IImage* partialImage = _videoDriver->createImage(textureCatalogue, positionOnImage, dimension);
            irr::video::ITexture* texture = _videoDriver->addTexture(virtualFileName.c_str(), partialImage);
            partialImage->drop();
            irr::gui::IGUIImage* backgroundImage = _guiEnv->addImage(
                irr::core::recti(position, dimension), _menus[name]->menuElement);
            backgroundImage->setImage(texture);
        }

        void MenuControl::addButton(
            const wchar_t* menuName, const wchar_t* buttonName, const ButtonConfiguration& config) {
            irr::core::dimension2du buttonDimension(config.dimension.w, config.dimension.h);
            irr::core::position2di positionInMenu(config.relativePositionInMenu.x, config.relativePositionInMenu.y);
            irr::core::position2di inactivePosition(config.inactivePositionOnImage.x, config.inactivePositionOnImage.y);
            irr::core::position2di activePosition(config.activePositionOnImage.x, config.activePositionOnImage.y);
            irr::gui::IGUIButton* button = _guiEnv->addButton(
                irr::core::recti(positionInMenu, buttonDimension), _menus[menuName]->menuElement, -1, buttonName);
            button->setName(std::wstring(buttonName).c_str());
            button->setIsPushButton(false);
            button->setDrawBorder(false);
            button->setUseAlphaChannel(config.hasImageTransparence);
            irr::video::ITexture* textureCatalogue = loadTexture(config.imageFileName, config.hasImageTransparence);
            // normal button
            button->setImage(textureCatalogue, irr::core::recti(inactivePosition, buttonDimension));
            // pressed button
            button->setPressedImage(textureCatalogue, irr::core::recti(inactivePosition, buttonDimension));
            // hovered button
            std::wstring virtualFileName(L"virtual/buttonActiveSprite - ");
            virtualFileName += menuName;
            virtualFileName += buttonName;
            irr::video::IImage* partialImage = _videoDriver->createImage(
                textureCatalogue, activePosition, buttonDimension);
            irr::video::ITexture* texture = _videoDriver->addTexture(virtualFileName.c_str(), partialImage);
            partialImage->drop();
            irr::gui::IGUISpriteBank* sprites = _guiEnv->getSpriteBank("virtual/buttonSprites");
            button->setSpriteBank(sprites);
            int32_t index = sprites->addTextureAsSprite(texture);
            button->setSprite(irr::gui::EGBS_BUTTON_MOUSE_OVER, index);
        }

        void MenuControl::enable(const wchar_t* name) {
            _menus[name]->enable();
        }

        void MenuControl::disable(const wchar_t* name) {
            _menus[name]->disable();
        }

        void MenuControl::draw() {
            for (auto it = _menus.begin(); it != _menus.end(); ++it) {
                it->second->draw();
            }
        }

        /* private */

        irr::video::ITexture* MenuControl::loadTexture(const std::string& filename, bool makeTransparent) {
            // GenericHelperMethods& helper = GenericHelperMethods::getInstance();
            // helper.validateFileExistence( "GFX/menues1.bmp" );
            _videoDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);  // don't create LOD textures
            irr::video::ITexture* texture = _videoDriver->getTexture(filename.c_str());
            if (makeTransparent) {
                _videoDriver->makeColorKeyTexture(texture, video::COL_MAGICPINK);
            }
            return texture;
        }
    }
}
