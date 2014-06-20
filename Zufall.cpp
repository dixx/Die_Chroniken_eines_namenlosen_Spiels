#include "Zufall.h"



Zufall& Zufall::getInstance() 
{ 
    static Zufall instance;
    return instance;
}



void Zufall::start( const u32 seed ) 
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



f32 Zufall::getFloat()
{
    return ( static_cast<f32>( getInt() ) / 4294967295.0f );
}



u32 Zufall::getInt()
{
    tmp_   = ( seed_ ^ ( seed_ << 15 ) );
    seed_  = seed2_;
    seed2_ = seed3_;
    seed3_ = seed4_;
    seed4_ = ( seed4_ ^ ( seed4_ >> 21 ) ) ^ ( tmp_ ^ ( tmp_ >> 4 ) );
    return seed4_;
}



u32 Zufall::getIntBetween( const u32 min, const u32 max )
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
                ? max + static_cast<u32>( getFloat() * static_cast<f32>( min - max + 1 ) )
                : min + static_cast<u32>( getFloat() * static_cast<f32>( max - min + 1 ) );
    }
}



f32 Zufall::getFloatBetween( const f32 min, const f32 max )
{
    if ( core::equals( min, max ) )
    {
        return min;
    }
    else
    {
        return ( min > max ) ? max + getFloat() * ( min - max ) : min + getFloat() * ( max - min );
    }
}



bool Zufall::doesOccur( const f32 p )
{
    if ( p <= 0.0f )
        return false;
    else if ( p >= 100.0f )
        return true;
    else
        return ( ( getFloat() * 100.0f ) <= p );
}



bool Zufall::doesAoccur( const f32 A, const f32 B )
{
    if ( core::equals( A + B, 0.0f ) )
        return false;
    else
        return doesOccur( ( A / ( A + B ) ) * 100.0f );
}



bool Zufall::doesAoccur100( const u32 A, const u32 B )
{
    u32 Ax = core::clamp( A, static_cast<u32>( 1 ), static_cast<u32>( 99 ) );
    u32 Bx = core::clamp( B, static_cast<u32>( 1 ), static_cast<u32>( 99 ) );
    return ( getInt() % ( Ax + Bx ) + 1 <= Ax );
}



u8 Zufall::getRandomNumber() const
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
