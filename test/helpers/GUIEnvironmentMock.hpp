#include "irrlicht.h"

// Fakeit keeps pointer to arguments beyond their lifetime and matches the given args too late, so we must implement
// our own mocks :(
namespace mocks {
    class GUIEnvironmentMock : public irr::gui::IGUIEnvironment {
    public:
        void drawAll() {}
        bool setFocus(irr::gui::IGUIElement* element) { (void)element; return false; }
        irr::gui::IGUIElement* getFocus() const { return nullptr; }
        irr::gui::IGUIElement* getHovered() const { return nullptr; }
        bool removeFocus(irr::gui::IGUIElement* element) { (void)element; return false; }
        bool hasFocus(irr::gui::IGUIElement* element) const { (void)element; return false; }
        irr::video::IVideoDriver* getVideoDriver() const { return nullptr; }
        irr::io::IFileSystem* getFileSystem() const { return nullptr; }
        irr::IOSOperator* getOSOperator() const { return nullptr; }
        void clear() {}
        bool postEventFromUser(const irr::SEvent& event) { (void)event; return false; }
        void setUserEventReceiver(irr::IEventReceiver* evr) { (void)evr; }
        irr::gui::IGUISkin* getSkin() const { return nullptr; }
        void setSkin(irr::gui::IGUISkin* skin) { (void)skin; }
        irr::gui::IGUISkin* createSkin(irr::gui::EGUI_SKIN_TYPE type) { (void)type; return nullptr; }
        irr::gui::IGUIImageList* createImageList(irr::video::ITexture* texture,
            irr::core::dimension2d<irr::s32> imageSize,
            bool useAlphaChannel ) { (void)texture; (void)imageSize; (void)useAlphaChannel; return nullptr; }
        irr::gui::IGUIFont* getFont(const irr::io::path& filename) { (void)filename; return nullptr; }
        irr::gui::IGUIFont* addFont(const irr::io::path& name, irr::gui::IGUIFont* font) { (void)name; (void)font; return nullptr; }
        void removeFont(irr::gui::IGUIFont* font) { (void)font; }
        irr::gui::IGUIFont* getBuiltInFont() const { return nullptr; }
        irr::gui::IGUISpriteBank* getSpriteBank(const irr::io::path& filename) { (void)filename; return nullptr; }
        irr::gui::IGUISpriteBank* addEmptySpriteBank(const irr::io::path& name) { (void)name; return nullptr; }
        irr::gui::IGUIElement* getRootGUIElement() { return nullptr; }
        irr::gui::IGUIButton* addButton(const irr::core::rect<irr::s32>& rectangle,
            irr::gui::IGUIElement* parent=0, irr::s32 id=-1, const wchar_t* text=0, const wchar_t* tooltiptext = 0) { (void)rectangle; (void)parent; (void)id; (void)text; (void)tooltiptext; return nullptr; }
        irr::gui::IGUIWindow* addWindow(const irr::core::rect<irr::s32>& rectangle, bool modal = false,
            const wchar_t* text=0, irr::gui::IGUIElement* parent=0, irr::s32 id=-1) { (void)rectangle; (void)modal; (void)text; (void)parent; (void)id; return nullptr; }
        irr::gui::IGUIElement* addModalScreen(irr::gui::IGUIElement* parent) { (void)parent; return nullptr; }
        irr::gui::IGUIWindow* addMessageBox(const wchar_t* caption, const wchar_t* text=0,
            bool modal = true, irr::s32 flags = irr::gui::EMBF_OK, irr::gui::IGUIElement* parent=0, irr::s32 id=-1, irr::video::ITexture* image=0) { (void)caption; (void)text; (void)modal; (void)flags; (void)parent; (void)id; (void)image; return nullptr; }
        irr::gui::IGUIScrollBar* addScrollBar(bool horizontal, const irr::core::rect<irr::s32>& rectangle,
            irr::gui::IGUIElement* parent=0, irr::s32 id=-1) { (void)horizontal; (void)rectangle; (void)parent; (void)id; return nullptr; }
        irr::gui::IGUIImage* addImage(irr::video::ITexture* image, irr::core::position2d<irr::s32> pos,
            bool useAlphaChannel=true, irr::gui::IGUIElement* parent=0, irr::s32 id=-1, const wchar_t* text=0) { (void)image; (void)pos; (void)useAlphaChannel; (void)parent; (void)id; (void)text; return nullptr; }
        irr::gui::IGUIImage* addImage(const irr::core::rect<irr::s32>& rectangle,
            irr::gui::IGUIElement* parent=0, irr::s32 id=-1, const wchar_t* text=0, bool useAlphaChannel=true) { (void)rectangle; (void)parent; (void)id; (void)text; (void)useAlphaChannel; return nullptr; }
        irr::gui::IGUICheckBox* addCheckBox(bool checked, const irr::core::rect<irr::s32>& rectangle,
            irr::gui::IGUIElement* parent=0, irr::s32 id=-1, const wchar_t* text=0) { (void)checked; (void)rectangle; (void)parent; (void)id; (void)text; return nullptr; }
        irr::gui::IGUIListBox* addListBox(const irr::core::rect<irr::s32>& rectangle,
            irr::gui::IGUIElement* parent=0, irr::s32 id=-1, bool drawBackground=false) { (void)rectangle; (void)parent; (void)id; (void)drawBackground; return nullptr; }
        irr::gui::IGUITreeView* addTreeView(const irr::core::rect<irr::s32>& rectangle,
            irr::gui::IGUIElement* parent=0, irr::s32 id=-1, bool drawBackground=false,
            bool scrollBarVertical = true, bool scrollBarHorizontal = false) { (void)rectangle; (void)parent; (void)id; (void)drawBackground; (void)scrollBarVertical; (void)scrollBarHorizontal; return nullptr; }
        irr::gui::IGUIMeshViewer* addMeshViewer(const irr::core::rect<irr::s32>& rectangle,
            irr::gui::IGUIElement* parent=0, irr::s32 id=-1, const wchar_t* text=0) { (void)rectangle; (void)parent; (void)id; (void)text; return nullptr; }
        irr::gui::IGUIFileOpenDialog* addFileOpenDialog(const wchar_t* title=0,
            bool modal=true, irr::gui::IGUIElement* parent=0, irr::s32 id=-1,
            bool restoreCWD=false, irr::io::path::char_type* startDir=0) { (void)title; (void)modal; (void)parent; (void)id; (void)restoreCWD; (void)startDir; return nullptr; }
        irr::gui::IGUIColorSelectDialog* addColorSelectDialog(const wchar_t* title = 0,
            bool modal=true, irr::gui::IGUIElement* parent=0, irr::s32 id=-1) { (void)title; (void)modal; (void)parent; (void)id; return nullptr; }
        irr::gui::IGUIStaticText* addStaticText(const wchar_t* text, const irr::core::rect<irr::s32>& rectangle,
            bool border=false, bool wordWrap=true, irr::gui::IGUIElement* parent=0, irr::s32 id=-1,
            bool fillBackground = false) { (void)text; (void)rectangle; (void)border; (void)wordWrap; (void)parent; (void)id; (void)fillBackground; return nullptr; }
        irr::gui::IGUIEditBox* addEditBox(const wchar_t* text, const irr::core::rect<irr::s32>& rectangle,
            bool border=true, irr::gui::IGUIElement* parent=0, irr::s32 id=-1) { (void)text; (void)rectangle; (void)border; (void)parent; (void)id; return nullptr; }
        irr::gui::IGUISpinBox* addSpinBox(const wchar_t* text, const irr::core::rect<irr::s32>& rectangle,
            bool border=true,irr::gui::IGUIElement* parent=0, irr::s32 id=-1) { (void)text; (void)rectangle; (void)border; (void)parent; (void)id; return nullptr; }
        irr::gui::IGUIInOutFader* addInOutFader(const irr::core::rect<irr::s32>* rectangle=0, irr::gui::IGUIElement* parent=0, irr::s32 id=-1) { (void)rectangle; (void)parent; (void)id; return nullptr; }
        irr::gui::IGUITabControl* addTabControl(const irr::core::rect<irr::s32>& rectangle,
            irr::gui::IGUIElement* parent=0, bool fillbackground=false,
            bool border=true, irr::s32 id=-1) { (void)rectangle; (void)parent; (void)fillbackground; (void)border; (void)id; return nullptr; }
        irr::gui::IGUITab* addTab(const irr::core::rect<irr::s32>& rectangle,
            irr::gui::IGUIElement* parent=0, irr::s32 id=-1) { (void)rectangle; (void)parent; (void)id; return nullptr; }
        irr::gui::IGUIContextMenu* addContextMenu(const irr::core::rect<irr::s32>& rectangle,
            irr::gui::IGUIElement* parent=0, irr::s32 id=-1) { (void)rectangle; (void)parent; (void)id; return nullptr; }
        irr::gui::IGUIContextMenu* addMenu(irr::gui::IGUIElement* parent=0, irr::s32 id=-1) { (void)parent; (void)id; return nullptr; }
        irr::gui::IGUIToolBar* addToolBar(irr::gui::IGUIElement* parent=0, irr::s32 id=-1) { (void)parent; (void)id; return nullptr; }
        irr::gui::IGUIComboBox* addComboBox(const irr::core::rect<irr::s32>& rectangle,
            irr::gui::IGUIElement* parent=0, irr::s32 id=-1) { (void)rectangle; (void)parent; (void)id; return nullptr; }
        irr::gui::IGUITable* addTable(const irr::core::rect<irr::s32>& rectangle,
            irr::gui::IGUIElement* parent=0, irr::s32 id=-1, bool drawBackground=false) { (void)rectangle; (void)parent; (void)id; (void)drawBackground; return nullptr; }
        irr::gui::IGUIElementFactory* getDefaultGUIElementFactory() const { return nullptr; }
        void registerGUIElementFactory(irr::gui::IGUIElementFactory* factoryToAdd) { (void)factoryToAdd; }
        irr::u32 getRegisteredGUIElementFactoryCount() const { return 0; }
        irr::gui::IGUIElementFactory* getGUIElementFactory(irr::u32 index) const { (void)index; return nullptr; }
        irr::gui::IGUIElement* addGUIElement(const irr::c8* elementName, irr::gui::IGUIElement* parent=0) { (void)elementName; (void)parent; return nullptr; }
        bool saveGUI(const irr::io::path& filename, irr::gui::IGUIElement* start=0) { (void)filename; (void)start; return false; }
        bool saveGUI(irr::io::IWriteFile* file, irr::gui::IGUIElement* start=0) { (void)file; (void)start; return false; }
        bool loadGUI(const irr::io::path& filename, irr::gui::IGUIElement* parent=0) { (void)filename; (void)parent; return false; }
        bool loadGUI(irr::io::IReadFile* file, irr::gui::IGUIElement* parent=0) { (void)file; (void)parent; return false; }
        void serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options=0) const { (void)out; (void)options; }
        void deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options=0) { (void)in; (void)options; }
        void writeGUIElement(irr::io::IXMLWriter* writer, irr::gui::IGUIElement* node) { (void)writer; (void)node; }
        void readGUIElement(irr::io::IXMLReader* reader, irr::gui::IGUIElement* node) { (void)reader; (void)node; }
    };
}
