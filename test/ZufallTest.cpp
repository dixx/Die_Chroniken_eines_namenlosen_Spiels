#include "catch.hpp"
#include "../Zufall.h"
#include <time.h>
#include <irrlicht.h>

TEST_CASE( "architecture" ) {
    SECTION( "it exists only one instance" ) {
        Zufall& subject = Zufall::getInstance();

        REQUIRE( &subject == &(Zufall::getInstance()) );
    }
}

TEST_CASE( "seeding" ) {
    Zufall& subject = Zufall::getInstance();

    SECTION( "seed evolves internally" ) {
        subject.start( 42 );

        REQUIRE( subject.getInt() == 1331530 );
        REQUIRE( subject.getInt() != 1331530 );
    }

    SECTION( "different seed produces different result" ) {
        subject.start( 43 );

        REQUIRE( subject.getInt() != 1331530 );
    }

    SECTION( "same seed produces same result every time" ) {
        subject.start( 42 );

        REQUIRE( subject.getInt() == 1331530 );

        SECTION( "resetting the seed with same value produces still the same result" ) {
            subject.start( 42 );

            REQUIRE( subject.getInt() == 1331530 );
        }
    }
}

TEST_CASE( "get random Int" ) {
    Zufall& subject = Zufall::getInstance();
    subject.start( (irr::u32)time( NULL ) );

    //REQUIRE( subject.getInt() >= 0 ); // comparison of unsigned expression >= 0 is always true
    REQUIRE( subject.getInt() <= (irr::u32)( 4294967295UL ) );

    SECTION( "different seed, different result" ) {
        subject.start( 42 );
        irr::u32 sample = subject.getInt();
        subject.start( 43 );

        REQUIRE( subject.getInt() != sample );
    }
}

TEST_CASE( "get random Float" ) {
    Zufall& subject = Zufall::getInstance();
    subject.start( (irr::u32)time( NULL ) );

    REQUIRE( subject.getFloat() >= 0.0f );
    REQUIRE( subject.getFloat() < 1.0f );

    SECTION( "different seed, different result" ) {
        subject.start( 42 );
        irr::f32 sample = subject.getFloat();
        subject.start( 43 );

        REQUIRE( subject.getFloat() != Approx( sample ).epsilon( 0.00000001 ) );
    }
}

TEST_CASE( "get random int within range" ) {
    Zufall& subject = Zufall::getInstance();
    subject.start( (irr::u32)time( NULL ) );

    REQUIRE( subject.getIntBetween(3, 5) >= 3 );
    REQUIRE( subject.getIntBetween(3, 5) <= 5 );
    REQUIRE( subject.getIntBetween(3, 3) == 3 );
    REQUIRE( subject.getIntBetween(0, 0) == 0 );

    SECTION( "switched values are auto-corrected" ) {
        REQUIRE_NOTHROW( subject.getIntBetween(5, 3) );
        REQUIRE( subject.getIntBetween(5, 3) >= 3 );
        REQUIRE( subject.getIntBetween(5, 3) <= 5 );
    }

    SECTION( "probability" ) {
        bool first, second, third, invalid = false;
        irr::u32 value = 0;
        for( int i = 0; i < 100; ++i ) {
            value = subject.getIntBetween(123456, 123458);
            switch (value) {
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

        REQUIRE( first );
        REQUIRE( second );
        REQUIRE( third );
        REQUIRE_FALSE( invalid );
    }
}

TEST_CASE( "get random float within range" ) {
    Zufall& subject = Zufall::getInstance();
    subject.start( (irr::u32)time( NULL ) );

    REQUIRE( subject.getFloatBetween(3.0f, 5.0f) >= 3.0f );
    REQUIRE( subject.getFloatBetween(3.0f, 5.0f) <= 5.0f );
    REQUIRE( subject.getFloatBetween(3.0f, 3.0f) == Approx( 3.0f ) );
    REQUIRE( subject.getFloatBetween(0.0f, 0.0f) == Approx( 0.0f ) );

    SECTION( "switched values are auto-corrected" ) {
        REQUIRE_NOTHROW( subject.getFloatBetween(5.0f, 3.0f) );
        REQUIRE( subject.getFloatBetween(5.0f, 3.0f) >= 3.0f );
        REQUIRE( subject.getFloatBetween(5.0f, 3.0f) <= 5.0f );
    }
}

TEST_CASE( "let an event occur or not, using one probability" ) {
    Zufall& subject = Zufall::getInstance();
    subject.start( (irr::u32)time( NULL ) );

    REQUIRE( subject.doesOccur(100.0f) );
    REQUIRE_FALSE( subject.doesOccur(0.0f) );

    SECTION( "values are auto-corrected" ) {
        REQUIRE( subject.doesOccur(1000.0f) );
        REQUIRE_FALSE( subject.doesOccur(-1000.0f) );
    }

    SECTION( "probability" ) {
        bool occured = false;
        for( int i = 0; i < 1000; ++i ) {
            if ( subject.doesOccur( 1.0f ) ) {
                occured = true;
            }
        }

        REQUIRE( occured );

        occured = true;
        for( int i = 0; i < 1000; ++i ) {
            if ( !subject.doesOccur( 99.0f ) ) {
                occured = false;
            }
        }

        REQUIRE_FALSE( occured );
    }
}

TEST_CASE( "let one out of two events occur, using ratio of both" ) {
    Zufall& subject = Zufall::getInstance();
    subject.start( (irr::u32)time( NULL ) );

    REQUIRE( subject.doesAoccur(0.001f, 0.0f) );
    REQUIRE( subject.doesAoccur(100.0f, 0.0f) );
    REQUIRE( subject.doesAoccur(1000.0f, 0.0f) );
    REQUIRE_FALSE( subject.doesAoccur(0.0f, 0.001f) );
    REQUIRE_FALSE( subject.doesAoccur(0.0f, 100.0f) );
    REQUIRE_FALSE( subject.doesAoccur(0.0f, 1000.0f) );
    REQUIRE_FALSE( subject.doesAoccur(0.0f, 0.0f) );

    SECTION( "negative values" ) {
        REQUIRE( subject.doesAoccur(100.0f, -100.0f) );
        REQUIRE_FALSE( subject.doesAoccur(-100.0f, 0.0f) );
    }
}

TEST_CASE( "let one out of two events occur, using limited probabilities for both" ) {
    Zufall& subject = Zufall::getInstance();
    subject.start( (irr::u32)time( NULL ) );

    REQUIRE( subject.doesAoccur100(100, 0) );
    REQUIRE_FALSE( subject.doesAoccur100(0, 100) );
    REQUIRE_FALSE( subject.doesAoccur100(0, 0) );

    SECTION( "values are auto-corrected" ) {
        REQUIRE( subject.doesAoccur100(1000, 0) );
        REQUIRE_FALSE( subject.doesAoccur100(0, 1000) );
    }
}

TEST_CASE( "...okay. If you insist. It is 4. Always 4. There. All the fun is gone." ) {
    Zufall& subject = Zufall::getInstance();

    REQUIRE( subject.getRandomNumber() == 4 );
    subject.start(42);
    REQUIRE( subject.getRandomNumber() == 4 );
}
