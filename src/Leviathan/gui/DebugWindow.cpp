#include "DebugWindow.h"
#include "IGUIEnvironment.h"
#include "IGUIStaticText.h"

namespace leviathan {
    namespace gui {
        DebugWindow::DebugWindow(irr::gui::IGUIEnvironment* guiEnv, irr::video::IVideoDriver* videoDriver)
        : mGuiEnv(guiEnv), mVideoDriver(videoDriver), mWindow(mGuiEnv) {
            auto text = mGuiEnv->addStaticText(
                L"FPS:", irr::core::recti(10, 10, 50, 50), true, true, mWindow.menuElement, -1, true);
            text->setBackgroundColor(irr::video::SColor(100, 0, 0, 0));
            text->setOverrideColor(irr::video::SColor(255, 247, 139, 7));
            mWindow.enable();
        }

        void DebugWindow::draw() {
            mWindow.draw();
        }
    }
}