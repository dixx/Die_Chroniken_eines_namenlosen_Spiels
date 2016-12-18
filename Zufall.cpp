#include "Zufall.h"



Zufall& Zufall::getInstance()
{
    static Zufall instance;
    return instance;
}



void Zufall::start( const irr::u32 seed )
{
    seed_ = seed;
    if ( seed_ > 100 )
    {
        seed2_ = seed_ / 2 - 1;
        seed3_ = seed2_ / 2 - 3;
        seed4_ = seed3_ / 2 - 8;
    }
    else
    {
        seed2_ = seed_ * 2 + 1;
        seed3_ = seed2_ * 2 + 3;
        seed4_ = seed3_ * 2 + 8;
    }
}



irr::f32 Zufall::getFloat()
{
    return ( static_cast<irr::f32>( getInt() ) / 4294967295.0f );
}



irr::u32 Zufall::getInt()
{
    tmp_   = ( seed_ ^ ( seed_ << 15 ) );
    seed_  = seed2_;
    seed2_ = seed3_;
    seed3_ = seed4_;
    seed4_ = ( seed4_ ^ ( seed4_ >> 21 ) ) ^ ( tmp_ ^ ( tmp_ >> 4 ) );
    return seed4_;
}



irr::u32 Zufall::getIntBetween( const irr::u32 min, const irr::u32 max )
{
    if ( min == max )
    {
        return min;
    }
    else
    {
        // Ersetzen des Modulo durch schnellere Rechenoperationen
        // max + rand() % ( min - max + 1 ) :
        // min + rand() % ( max - min + 1 );
        return ( min > max )
                ? max + static_cast<irr::u32>( getFloat() * static_cast<irr::f32>( min - max + 1 ) )
                : min + static_cast<irr::u32>( getFloat() * static_cast<irr::f32>( max - min + 1 ) );
    }
}



irr::f32 Zufall::getFloatBetween( const irr::f32 min, const irr::f32 max )
{
    if ( irr::core::equals( min, max ) )
    {
        return min;
    }
    else
    {
        return ( min > max ) ? max + getFloat() * ( min - max ) : min + getFloat() * ( max - min );
    }
}



bool Zufall::doesOccur( const irr::f32 p )
{
    if ( p <= 0.0f )
        return false;
    else if ( p >= 100.0f )
        return true;
    else
        return ( ( getFloat() * 100.0f ) <= p );
}



bool Zufall::doesAoccur( const irr::f32 A, const irr::f32 B )
{
    if ( irr::core::equals( A + B, 0.0f ) )
        return false;
    else
        return doesOccur( ( A / ( A + B ) ) * 100.0f );
}



bool Zufall::doesAoccur100( const irr::u32 A, const irr::u32 B )
{
    irr::u32 Ax = irr::core::clamp( A, static_cast<irr::u32>( 1 ), static_cast<irr::u32>( 99 ) );
    irr::u32 Bx = irr::core::clamp( B, static_cast<irr::u32>( 1 ), static_cast<irr::u32>( 99 ) );
    return ( getInt() % ( Ax + Bx ) + 1 <= Ax );
}



irr::u8 Zufall::getRandomNumber() const
{
    return 4;
}



/* private */



Zufall::Zufall()
: seed_(0),
  seed2_(0),
  seed3_(0),
  seed4_(0),
  tmp_(0)
{
    //
}



Zufall::Zufall( const Zufall& )
: seed_(0),
  seed2_(0),
  seed3_(0),
  seed4_(0),
  tmp_(0)
{
    //
}



Zufall& Zufall::operator=( const Zufall& )
{
    return this->getInstance();
}
