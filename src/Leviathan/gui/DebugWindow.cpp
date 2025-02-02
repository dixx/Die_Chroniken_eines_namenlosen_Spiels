#include "DebugWindow.h"
#include "IGUIEnvironment.h"
#include "IGUIStaticText.h"

namespace leviathan {
    namespace gui {
        DebugWindow::DebugWindow(irr::gui::IGUIEnvironment* guiEnv, irr::video::IVideoDriver* videoDriver)
        : mGuiEnv(guiEnv), mVideoDriver(videoDriver), mWindow(mGuiEnv) {
            mWindow.enable();
        }

        void DebugWindow::draw() {
            mWindow.draw();
        }
    }
}
