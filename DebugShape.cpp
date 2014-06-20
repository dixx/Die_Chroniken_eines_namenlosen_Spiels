#include "DebugShape.h"



DebugShape::DebugShape()
{
}



DebugShape::~DebugShape()
{
}



DebugCircle::DebugCircle( video::IVideoDriver* driver, core::vector3df position, f32 radius )
: driver_(driver),
  position_(position),
  radius_(radius),
  circleMeshBuffer_(0)
{
    createCircleFan();
}



DebugCircle::~DebugCircle()
{
}



void DebugCircle::draw()
{
    driver_->setTransform( video::ETS_WORLD, core::matrix4() );
    driver_->draw3DLine( circleMeshBuffer_->Vertices[ 41 ].Pos, circleMeshBuffer_->Vertices[ 1 ].Pos );
    for ( u32 i = 1; i < circleMeshBuffer_->Vertices.size() - 1; ++i )
        driver_->draw3DLine( circleMeshBuffer_->Vertices[ i ].Pos, circleMeshBuffer_->Vertices[ i + 1 ].Pos );
}



void DebugCircle::drop()
{
    delete this;
}



void DebugCircle::createCircleFan()
{
    circleMeshBuffer_ = new scene::SMeshBuffer;
    video::S3DVertex vertex;
    vertex.Normal.set( 0.0f, 1.0f, 0.0f);
    vertex.Pos.set( position_.X, 0.2f, position_.Z );
    circleMeshBuffer_->Vertices.push_back( vertex );
    circleMeshBuffer_->Indices.push_back( 0 );
    circleMeshBuffer_->getMaterial().Lighting = false;
    for ( s32 n = 42; 0 <= n; --n )
    {
        const f32 x = ( core::PI * 2.0f ) * static_cast<f32>( n ) / static_cast<f32>( 42 );
        vertex.Pos.set(
                static_cast<f32>( sinf( x ) ) * radius_ + position_.X,
                0.2f,
                static_cast<f32>( cosf( x ) ) * radius_ + position_.Z
        );
        circleMeshBuffer_->Vertices.push_back( vertex );
        circleMeshBuffer_->Indices.push_back( static_cast<u16>( n + 1 ) );
    }
}
