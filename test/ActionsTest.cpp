#include <catch.hpp>
#include "leviathan.h"
#include "helpers/Testhelper.h"
#include "helpers/TesthelperLeviathanDevice.h"

SCENARIO( "Leviathan Engine can map input to actions" ) {
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
    testhelper.writeFile( mappingsFileName, content );
    TesthelperLeviathanDevice::LeviathanDeviceWithIrrlichtMock device;
    //leviathan::input::Actions& subject = device.Actions();
    subject.mergeFromFile( mappingsFileName );
    enum { TALK = 1, ATTACK, SELECT = 100 };

    GIVEN( "I subscribe to Leviathan Engine Actions" ) {

        AND_WHEN( "there is input for my action" ) {
            device.sendKeyboardEvent( irr::KEY_KEY_Z, true, false, false );

            THEN( "I will be updated" ) {

            }
        }

        AND_WHEN( "there is input for any action but mine" ) {
            //device.sendMouseEvent( leviathan::input::Mouse::Button::MIDDLE, true, 12, 34, -2.4f );

            THEN( "I won't be updated" ) {

            }
        }

        WHEN( "I choose another input for an action" ) {

            AND_WHEN( "this input occurs" ) {
                //device.sendMouseEvent( leviathan::input::Mouse::Button::MIDDLE, true, 12, 34, -2.4f );

                THEN( "I will be updated" ) {

                }
            }

            AND_WHEN( "the old input occurs" ) {
                device.sendKeyboardEvent( irr::KEY_KEY_Z, true, false, false );

                THEN( "I won't be updated" ) {

                }
            }
        }
    }
}
