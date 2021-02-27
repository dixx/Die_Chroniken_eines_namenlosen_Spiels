#include "../../source/Leviathan/core/Randomizer.h"
#include "catch.hpp"
#include <chrono>

const uint32_t SEED = static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count());

TEST_CASE("Randomizer: seeding", "[unit]") {
    leviathan::core::Randomizer subject;

    SECTION("seed evolves internally") {
        subject.start(42);
        REQUIRE(subject.getInt() == 1331530);
        REQUIRE(subject.getInt() != 1331530);
    }

    SECTION("different seed produces different result") {
        subject.start(43);
        REQUIRE(subject.getInt() != 1331530);
    }

    SECTION("same seed produces same result every time") {
        subject.start(42);
        REQUIRE(subject.getInt() == 1331530);
        subject.start(42);
        REQUIRE(subject.getInt() == 1331530);
    }
}

TEST_CASE("Randomizer: get random Float", "[unit]") {
    leviathan::core::Randomizer subject;
    subject.start(SEED);
    REQUIRE(subject.getFloat() >= 0.0f);
    REQUIRE(subject.getFloat() < 1.0f);
}

TEST_CASE("Randomizer: get random float within range", "[unit]") {
    leviathan::core::Randomizer subject;
    subject.start(SEED);
    REQUIRE(subject.getFloat(3.0f, 5.0f) >= 3.0f);
    REQUIRE(subject.getFloat(3.0f, 5.0f) <= 5.0f);
    REQUIRE(subject.getFloat(3.0f, 3.0f) == Approx(3.0f));
    REQUIRE(subject.getFloat(0.0f, 0.0f) == Approx(0.0f));

    SECTION("switched values are auto-corrected") {
        REQUIRE_NOTHROW(subject.getFloat(5.0f, 3.0f));
        REQUIRE(subject.getFloat(5.0f, 3.0f) >= 3.0f);
        REQUIRE(subject.getFloat(5.0f, 3.0f) <= 5.0f);
    }

    SECTION("negative values are valid") {
        REQUIRE_NOTHROW(subject.getFloat(-5.0f, -3.0f));
        REQUIRE(subject.getFloat(-5.0f, -3.0f) >= -5.0f);
        REQUIRE(subject.getFloat(-5.0f, -3.0f) <= -3.0f);
    }

    SECTION("limits") {
        REQUIRE(subject.getFloat(0.0f, 0.0f) == Approx(0.0f));
        REQUIRE(subject.getFloat(1.0f, 1.0f) == Approx(1.0f));
    }
}

TEST_CASE("Randomizer: get random Int", "[unit]") {
    leviathan::core::Randomizer subject;
    subject.start(SEED);
    REQUIRE(subject.getInt() <= UINT32_MAX);
}

TEST_CASE("Randomizer: get random int within range", "[unit]") {
    leviathan::core::Randomizer subject;
    subject.start(SEED);
    REQUIRE(subject.getInt(3, 5) >= 3);
    REQUIRE(subject.getInt(3, 5) <= 5);
    REQUIRE(subject.getInt(3, 3) == 3);
    REQUIRE(subject.getInt(0, 0) == 0);

    SECTION("switched values are auto-corrected") {
        REQUIRE_NOTHROW(subject.getInt(5, 3));
        REQUIRE(subject.getInt(5, 3) >= 3);
        REQUIRE(subject.getInt(5, 3) <= 5);
    }

    SECTION("limits") {
        REQUIRE(subject.getInt(0, 0) == 0);
        REQUIRE(subject.getInt(UINT32_MAX, UINT32_MAX) == UINT32_MAX);
    }

    SECTION("probability") {
        bool first, second, third, invalid = false;
        for (int i = 0; i < 100; ++i) {
            switch (subject.getInt(123456, 123458)) {
            case 123456:
                first = true;
                break;
            case 123457:
                second = true;
                break;
            case 123458:
                third = true;
                break;
            default:
                invalid = true;
                break;
            }
        }
        REQUIRE(first);
        REQUIRE(second);
        REQUIRE(third);
        REQUIRE_FALSE(invalid);
    }
}
