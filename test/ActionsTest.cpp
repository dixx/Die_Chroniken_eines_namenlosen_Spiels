#include <catch.hpp>
#include "leviathan.h"
#include "helpers/Testhelper.h"
#include "helpers/TesthelperLeviathanDevice.h"

TEST_CASE("Action Mapping") {
    Testhelper testhelper;
    const irr::io::path mappingsFileName = "testactionmappings.yml";
    irr::core::stringc content = "---\n";
    content += "customizable:\n";
    content += "  - name: talk\n";
    content += "    id: 1\n";
    content += "    description: initiate communication\n";
    content += "    input_mappings:\n";
    content += "      primary:\n";
    content += "        name: left mouse button\n";
    content += "        type: mouse\n";
    content += "        id: 0x01\n";
    content += "      secondary:\n";
    content += "        name: <E>\n";
    content += "        type: keyboard\n";
    content += "        id: 0x45\n";
    content += "  - name: attack\n";
    content += "    id: 2\n";
    content += "    description: main hand attack\n";
    content += "    input_mappings:\n";
    content += "internal:\n";
    content += "  - name: select\n";
    content += "    id: 100\n";
    content += "    description: select a menu entry\n";
    content += "    input_mappings:\n";
    content += "      primary:\n";
    content += "        name: <SPACE>\n";
    content += "        type: keyboard\n";
    content += "        id: 0x20\n";
    testhelper.writeFile(mappingsFileName, content);
    leviathan::input::Actions subject;

    SECTION("can subscribe to an event receiver") {

    }
    SECTION("client can subscribe to the action mapping") {

    }
    SECTION("no input mappings exist") {

    }
    SECTION("mappings can be loaded from file") {
        subject.mergeFromFile(mappingsFileName);
        enum { TALK = 1, ATTACK, SELECT = 100 };

        SECTION("") {
            
        }
    }
}
