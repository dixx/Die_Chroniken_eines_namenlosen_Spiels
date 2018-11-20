#include "../source/chroniken_alt/Zufall.h"  // TODO change to engine randomizer later
#include "catch.hpp"
#include <chrono>
#include <cstdint>

const uint32_t SEED = static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count());

TEST_CASE("Zufall: architecture") {
    SECTION("it exists only one instance") {
        Zufall& subject = Zufall::getInstance();
        REQUIRE(&subject == &(Zufall::getInstance()));
    }
}

TEST_CASE("Zufall: seeding") {
    Zufall& subject = Zufall::getInstance();

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

        SECTION("resetting the seed with same value produces still the same result") {
            subject.start(42);
            REQUIRE(subject.getInt() == 1331530);
        }
    }
}

TEST_CASE("Zufall: get random Int") {
    Zufall& subject = Zufall::getInstance();
    subject.start(SEED);
    // REQUIRE(subject.getInt() >= 0); // comparison of unsigned expression >= 0 is always true
    REQUIRE(subject.getInt() <= 4294967295UL);

    SECTION("different seed, different result") {
        subject.start(42);
        uint32_t sample = subject.getInt();
        subject.start(43);
        REQUIRE(subject.getInt() != sample);
    }
}

TEST_CASE("Zufall: get random Float") {
    Zufall& subject = Zufall::getInstance();
    subject.start(SEED);
    REQUIRE(subject.getFloat() >= 0.0f);
    REQUIRE(subject.getFloat() < 1.0f);

    SECTION("different seed, different result") {
        subject.start(42);
        float sample = subject.getFloat();
        subject.start(43);
        REQUIRE(subject.getFloat() != Approx(sample).epsilon(0.00000001f));
    }
}

TEST_CASE("Zufall: get random int within range") {
    Zufall& subject = Zufall::getInstance();
    subject.start(SEED);
    REQUIRE(subject.getIntBetween(3, 5) >= 3);
    REQUIRE(subject.getIntBetween(3, 5) <= 5);
    REQUIRE(subject.getIntBetween(3, 3) == 3);
    REQUIRE(subject.getIntBetween(0, 0) == 0);

    SECTION("switched values are auto-corrected") {
        REQUIRE_NOTHROW(subject.getIntBetween(5, 3));
        REQUIRE(subject.getIntBetween(5, 3) >= 3);
        REQUIRE(subject.getIntBetween(5, 3) <= 5);
    }

    SECTION("probability") {
        bool first, second, third, invalid = false;
        // uint32_t value = 0;
        for (int i = 0; i < 100; ++i) {
            // value = subject.getIntBetween(123456, 123458);
            switch (subject.getIntBetween(123456, 123458)) {
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

TEST_CASE("Zufall: get random float within range") {
    Zufall& subject = Zufall::getInstance();
    subject.start(SEED);
    REQUIRE(subject.getFloatBetween(3.0f, 5.0f) >= 3.0f);
    REQUIRE(subject.getFloatBetween(3.0f, 5.0f) <= 5.0f);
    REQUIRE(subject.getFloatBetween(3.0f, 3.0f) == Approx(3.0f));
    REQUIRE(subject.getFloatBetween(0.0f, 0.0f) == Approx(0.0f));

    SECTION("switched values are auto-corrected") {
        REQUIRE_NOTHROW(subject.getFloatBetween(5.0f, 3.0f));
        REQUIRE(subject.getFloatBetween(5.0f, 3.0f) >= 3.0f);
        REQUIRE(subject.getFloatBetween(5.0f, 3.0f) <= 5.0f);
    }
}

TEST_CASE("Zufall: let an event occur or not, using one probability") {
    Zufall& subject = Zufall::getInstance();
    subject.start(SEED);
    REQUIRE(subject.doesOccur(100.0f));
    REQUIRE_FALSE(subject.doesOccur(0.0f));

    SECTION("values are auto-corrected") {
        REQUIRE(subject.doesOccur(1000.0f));
        REQUIRE_FALSE(subject.doesOccur(-1000.0f));
    }

    SECTION("probability") {
        bool occured = false;
        for (int16_t i = 0; i < 1000; ++i) {
            if (subject.doesOccur(1.0f)) {
                occured = true;
            }
        }
        REQUIRE(occured);

        occured = true;
        for (int16_t i = 0; i < 1000; ++i) {
            if (!subject.doesOccur(99.0f)) {
                occured = false;
            }
        }
        REQUIRE_FALSE(occured);
    }
}

TEST_CASE("Zufall: let one out of two events occur, using ratio of both") {
    Zufall& subject = Zufall::getInstance();
    subject.start(SEED);
    REQUIRE(subject.doesAoccur(0.001f, 0.0f));
    REQUIRE(subject.doesAoccur(100.0f, 0.0f));
    REQUIRE(subject.doesAoccur(1000.0f, 0.0f));
    REQUIRE_FALSE(subject.doesAoccur(0.0f, 0.001f));
    REQUIRE_FALSE(subject.doesAoccur(0.0f, 100.0f));
    REQUIRE_FALSE(subject.doesAoccur(0.0f, 1000.0f));
    REQUIRE_FALSE(subject.doesAoccur(0.0f, 0.0f));

    SECTION("negative values") {  // TODO bug#61
        // REQUIRE(subject.doesAoccur(100.0f, -100.0f));
        // REQUIRE_FALSE(subject.doesAoccur(-100.0f, 0.0f));
    }
}

TEST_CASE("Zufall: let one out of two events occur, using limited probabilities for both") {
    Zufall& subject = Zufall::getInstance();
    subject.start(SEED);
    // REQUIRE(subject.doesAoccur100(100, 0)); // TODO bug#61
    // REQUIRE_FALSE(subject.doesAoccur100(0, 100)); // TODO bug#61
    // REQUIRE_FALSE(subject.doesAoccur100(0, 0)); // TODO bug#61

    SECTION("values are auto-corrected") {
        // REQUIRE(subject.doesAoccur100(1000, 0)); // TODO bug#61
        // REQUIRE_FALSE(subject.doesAoccur100(0, 1000)); // TODO bug#61
    }
}

TEST_CASE("Zufall: ...okay. If you insist. It is 4. Always 4. There. All the fun is gone.") {
    Zufall& subject = Zufall::getInstance();
    REQUIRE(subject.getRandomNumber() == 4);

    subject.start(42);
    REQUIRE(subject.getRandomNumber() == 4);
}
