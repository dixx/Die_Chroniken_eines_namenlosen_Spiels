#include <catch.hpp>
#include <fakeit.hpp>
#include <cstdint>
#include "irrlicht.h"
#include "../source/Leviathan/Actions.h"
#include "helpers/Testhelper.h"

using namespace fakeit;

TEST_CASE("Action Mapping") {
    Testhelper testhelper;
    const irr::io::path mappingsFileName = "testactionmappings.yml";
    irr::core::stringc content = "---\n" \
                                 "- name: talk\n" \
                                 "  id: 1\n" \
                                 "  description: initiate communication\n" \
                                 "  input_mappings:\n" \
                                 "    primary:\n" \
                                 "      name: left mouse button\n" \
                                 "      type: mouse\n" \
                                 "      id: 0x01\n" \
                                 "    secondary:\n" \
                                 "      name: <E>\n" \
                                 "      type: keyboard\n" \
                                 "      id: 0x45\n" \
                                 "- name: attack\n" \
                                 "  id: 2\n" \
                                 "  description: main hand attack\n" \
                                 "  input_mappings:\n" \
                                 "- name: select\n" \
                                 "  id: 100\n" \
                                 "  description: select a menu entry\n" \
                                 "  internal: true\n" \
                                 "  input_mappings:\n" \
                                 "    primary:\n" \
                                 "      name: <SPACE>\n" \
                                 "      type: keyboard\n" \
                                 "      id: 0x20\n";
    testhelper.writeFile(mappingsFileName, content);
    Mock<leviathan::input::IEventProducer> eventBrokerMock;
    Fake(Method(eventBrokerMock, subscribe));

    SECTION("subscribes to an event producer for input event types") {
        leviathan::input::Actions subject(eventBrokerMock.get());
        // FIXME issue with the mock when .Using(subject, ...) instead of .Using(_, ...)
        Verify(Method(eventBrokerMock, subscribe).Using(_, irr::EET_MOUSE_INPUT_EVENT)).Exactly(Once);
        Verify(Method(eventBrokerMock, subscribe).Using(_, irr::EET_KEY_INPUT_EVENT)).Exactly(Once);
    }

    SECTION("mappings can be loaded from file") {
        leviathan::input::Actions subject(eventBrokerMock.get());
        // Mock<leviathan::input::Actions> spy(subject);
        // check mappings == empty
        subject.mergeFromFile(mappingsFileName);
        enum { TALK = 1, ATTACK, SELECT = 100 };
        // check mappings == 3

        SECTION("consumers can subscribe to certain actions") {
            Mock<leviathan::input::IActionConsumer> consumerMock;
            Mock<leviathan::input::IActionConsumer> anotherConsumerMock;
            Fake(Method(consumerMock, onAction), Method(anotherConsumerMock, onAction));
            subject.subscribe(consumerMock.get(), TALK);
            subject.subscribe(consumerMock.get(), ATTACK);
            subject.subscribe(anotherConsumerMock.get(), SELECT);

            SECTION("and receive only their subscribed actions") {
                irr::SEvent event;

                event.EventType = irr::EET_MOUSE_INPUT_EVENT;
                event.MouseInput.ButtonStates = irr::EMBSM_LEFT;
                event.MouseInput.Event = irr::EMIE_LMOUSE_PRESSED_DOWN;
                subject.onEvent(event);
                VerifyNoOtherInvocations(Method(anotherConsumerMock, onAction));
                Verify(
                    Method(consumerMock, onAction).Using(
                        [](uint32_t id, bool isActive){ return id == TALK && isActive; }
                    )
                ).Exactly(Once);
                VerifyNoOtherInvocations(Method(consumerMock, onAction));

                event.EventType = irr::EET_KEY_INPUT_EVENT;
                event.KeyInput.Key = irr::KEY_SPACE;
                event.KeyInput.PressedDown = false;
                subject.onEvent(event);
                VerifyNoOtherInvocations(Method(consumerMock, onAction));
                Verify(
                    Method(anotherConsumerMock, onAction).Using(
                        [](uint32_t id, bool isActive){ return id == SELECT && !isActive; }
                    )
                ).Exactly(Once);
                VerifyNoOtherInvocations(Method(anotherConsumerMock, onAction));
            }

            SECTION("and can unsubscribe from certain actions") {
                subject.unsubscribe(consumerMock.get(), TALK);

                irr::SEvent event;

                event.EventType = irr::EET_MOUSE_INPUT_EVENT;
                event.MouseInput.ButtonStates = irr::EMBSM_LEFT;
                event.MouseInput.Event = irr::EMIE_LMOUSE_PRESSED_DOWN;
                subject.onEvent(event);
                VerifyNoOtherInvocations(Method(consumerMock, onAction));
            }
        }
        SECTION("and can be changed by the user") {
            SECTION("except for internal actions") {}
        }
    }
}
