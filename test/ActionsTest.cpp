#include <catch.hpp>
#include "leviathan.h"
#include "helpers/Testhelper.h"

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

    GIVEN( "Leviathan Engine provides Actions" ) {
        leviathan::input::Actions subject;

        THEN( "it provides convenience methods" ) {
            REQUIRE_FALSE( subject.inProgress( 0 ) );
            REQUIRE( subject.inactive( 0 ) );
            REQUIRE_FALSE( subject.justStarted( 0 ) );
            REQUIRE_FALSE( subject.justStopped( 0 ) );
        }

        WHEN( "action map is read from file" ) {
            subject.mergeFromFile( mappingsFileName );
            enum { TALK = 1, ATTACK, SELECTION = 100 };

            THEN( "it provides an action for each defined input mapping" ) {
                REQUIRE_FALSE( subject.inProgress( ATTACK ) );
                REQUIRE_FALSE( subject.inProgress( TALK ) );
                REQUIRE_FALSE( subject.inProgress( SELECTION ) );

                AND_THEN( "convenience methods are more helpfull" ) {
                    REQUIRE( subject.inactive( TALK ) );
                    // send keyboard event
                    REQUIRE( subject.justStarted( TALK ) );
                    REQUIRE( subject.inProgress( TALK ) );
                    // send keyboard event
                    REQUIRE_FALSE( subject.justStarted( TALK ) );
                    REQUIRE( subject.inProgress( TALK ) );
                    REQUIRE_FALSE( subject.inactive( TALK ) );
                    REQUIRE_FALSE( subject.justStopped( TALK ) );
                    // send keyboard event
                    REQUIRE( subject.justStopped( TALK ) );
                }
                // AND_THEN( "actions have a state" ) {/*input1 || input2*/}
            }
            THEN( "mappings can be overridden by custom values" ) {
            }
        }
    }
}
