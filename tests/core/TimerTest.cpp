#include "../../source/Leviathan/core/Timer.h"
#include "catch.hpp"
#include "irrlicht.h"
#include <cfloat>

TEST_CASE("Timer: architecture", "[unit]") {
    leviathan::core::Timer subject(2.0f);

    SECTION("tick() starts chains") {
        subject.start();
        REQUIRE(subject.tick(1.1f).tick(1.1f).isFull());
    }
}

TEST_CASE("Timer: max value", "[unit]") {
    SECTION("zero is not forbidden") {
        leviathan::core::Timer subject(0.0f);
        REQUIRE(irr::core::equals(subject.getMaxValue(), 0.0f));
        REQUIRE(subject.isFull());
    }

    SECTION("negative values are not forbidden") {
        leviathan::core::Timer subject(-10.0f);
        REQUIRE(irr::core::equals(subject.getMaxValue(), -10.0f));
        REQUIRE(subject.isFull());
    }

    SECTION("values are exactly met") {
        leviathan::core::Timer subject(1.0f);
        subject.start();
        REQUIRE(irr::core::equals(subject.getMaxValue(), 1.0f));
        REQUIRE_FALSE(subject.isFull());

        subject.tick(1.0f - irr::core::ROUNDING_ERROR_f32);
        REQUIRE_FALSE(subject.isFull());

        subject.tick(irr::core::ROUNDING_ERROR_f32);
        REQUIRE(subject.isFull());
    }

    SECTION("it can handle overflow") {
        leviathan::core::Timer subject(FLT_MAX);
        subject.start();
        subject.tick(FLT_MAX);
        subject.tick(1.0e+038f);
        REQUIRE(subject.isFull());
    }
}

TEST_CASE("Timer: ticking", "[unit]") {
    leviathan::core::Timer subject(2.0f);

    SECTION("it does not tick") {
        SECTION("when it is not started") {
            subject.tick(2.2f);
            REQUIRE_FALSE(subject.isFull());
        }

        SECTION("when it is paused") {
            subject.start();
            subject.pause();
            subject.tick(2.2f);
            REQUIRE_FALSE(subject.isFull());
        }

        SECTION("when it is stopped") {
            subject.start();
            subject.stop();
            subject.tick(2.2f);
            REQUIRE_FALSE(subject.isFull());
        }
    }

    SECTION("it does tick") {
        SECTION("when it is started") {
            subject.start();
            subject.tick(2.2f);
            REQUIRE(subject.isFull());
        }

        SECTION("when it is resumed") {
            subject.start();
            subject.pause();
            subject.resume();
            subject.tick(2.2f);
            REQUIRE(subject.isFull());
        }

        SECTION("when it is restarted") {
            subject.start();
            subject.restart();
            subject.tick(2.2f);
            REQUIRE(subject.isFull());
        }
    }

    SECTION("it can tick more than once") {
        subject.start();
        subject.tick(0.6f);
        subject.tick(0.6f);
        REQUIRE_FALSE(subject.isFull());

        subject.tick(0.6f);
        subject.tick(0.6f);
        REQUIRE(subject.isFull());
    }

    SECTION("it can tick backwards") {
        subject.start();
        subject.tick(-10.0f);
        REQUIRE_FALSE(subject.isFull());

        subject.tick(11.9f);
        REQUIRE_FALSE(subject.isFull());

        subject.tick(0.2f);
        REQUIRE(subject.isFull());

        SECTION("but it stays full if once reached") {
            subject.tick(-10.0f);
            REQUIRE(subject.isFull());
        }
    }
}

TEST_CASE("Timer: states", "[unit]") {
    leviathan::core::Timer subject(2.0f);

    SECTION("it is not running") {
        SECTION("when it is newly created") {
            REQUIRE_FALSE(subject.isRunning());
        }

        SECTION("when it is stopped") {
            subject.start();
            subject.stop();
            REQUIRE_FALSE(subject.isRunning());
        }
    }

    SECTION("it is running") {
        SECTION("when it is started") {
            subject.start();
            REQUIRE(subject.isRunning());

            SECTION("and when it is paused") {
                subject.pause();
                REQUIRE(subject.isRunning());

                SECTION("and when it is resumed") {
                    subject.resume();
                    REQUIRE(subject.isRunning());
                }
            }

            SECTION("and when it is restarted") {
                subject.restart();
                REQUIRE(subject.isRunning());
            }
        }
    }

    SECTION("it is paused") {
        SECTION("when it is paused after being started") {
            subject.start();
            subject.pause();
            REQUIRE(subject.isPaused());
        }
    }

    SECTION("it is not paused") {
        SECTION("when it is newly created") {
            REQUIRE_FALSE(subject.isPaused());
        }

        SECTION("when it is started") {
            subject.start();
            REQUIRE_FALSE(subject.isPaused());
        }

        SECTION("when it is restarted") {
            subject.start();
            subject.restart();
            REQUIRE_FALSE(subject.isPaused());
        }

        SECTION("when it is resumed") {
            subject.start();
            subject.pause();
            subject.resume();
            REQUIRE_FALSE(subject.isPaused());
        }

        SECTION("when it is stopped") {
            subject.start();
            subject.stop();
            REQUIRE_FALSE(subject.isPaused());
        }
    }
}
