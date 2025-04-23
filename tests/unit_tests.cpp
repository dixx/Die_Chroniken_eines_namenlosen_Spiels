#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_CONSOLE_WIDTH 120
#include "../../src/Leviathan/video/GraphicEngine.h"
#include "catch.hpp"

struct MyTestEventListener : Catch::TestEventListenerBase {
    using Catch::TestEventListenerBase::TestEventListenerBase;  // inherit constructor

    void sectionEnded(Catch::SectionStats const&) override {
        // reset overridden graphic engine after each single test
        leviathan::video::GraphicEngine::overrideGraphicEngine(nullptr);
    }
};
CATCH_REGISTER_LISTENER(MyTestEventListener)
