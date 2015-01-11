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



DebugEllipsoid::DebugEllipsoid( video::IVideoDriver* driver, core::vector3df position, core::vector3df radien )
: driver_(driver),
  position_(position),
  radien_(radien),
  ellipsoidMeshBuffer_(0)
{
    createEllipsoid();
}



DebugEllipsoid::~DebugEllipsoid()
{
}



void DebugEllipsoid::draw()
{
    driver_->setTransform( video::ETS_WORLD, core::matrix4() );
    driver_->draw3DLine( ellipsoidMeshBuffer_->Vertices[ 42 ].Pos, ellipsoidMeshBuffer_->Vertices[ 1 ].Pos );
    driver_->draw3DLine( ellipsoidMeshBuffer_->Vertices[ 85 ].Pos, ellipsoidMeshBuffer_->Vertices[ 44 ].Pos );
    driver_->draw3DLine( ellipsoidMeshBuffer_->Vertices[ 128 ].Pos, ellipsoidMeshBuffer_->Vertices[ 87 ].Pos );
    for ( u32 i = 1; i < 42; ++i )
    {
        driver_->draw3DLine( ellipsoidMeshBuffer_->Vertices[ i ].Pos, ellipsoidMeshBuffer_->Vertices[ i + 1 ].Pos );
        driver_->draw3DLine( ellipsoidMeshBuffer_->Vertices[ 43 + i ].Pos, ellipsoidMeshBuffer_->Vertices[ 44 + i ].Pos );
        driver_->draw3DLine( ellipsoidMeshBuffer_->Vertices[ 86 + i ].Pos, ellipsoidMeshBuffer_->Vertices[ 87 + i ].Pos );
    }
}



void DebugEllipsoid::drop()
{
    delete this;
}



void DebugEllipsoid::createEllipsoid()
{
    ellipsoidMeshBuffer_ = new scene::SMeshBuffer;
    video::S3DVertex vertex;
    ellipsoidMeshBuffer_->getMaterial().Lighting = false;
    f32 theta = 2 * core::PI / 42.f;
    // draw XZ circle
    vertex.Normal.set( 0.0f, 1.0f, 0.0f);
    vertex.Pos.set( position_ );
    ellipsoidMeshBuffer_->Vertices.push_back( vertex );
    ellipsoidMeshBuffer_->Indices.push_back( 0 );
    for ( s32 n = 42; n > 0; --n )
    {
        const f32 rad = theta * static_cast<f32>( n );
        vertex.Pos.set(
                static_cast<f32>( sinf( rad ) ) * radien_.X + position_.X,
                position_.Y,
                static_cast<f32>( cosf( rad ) ) * radien_.Z + position_.Z
        );
        ellipsoidMeshBuffer_->Vertices.push_back( vertex );
        ellipsoidMeshBuffer_->Indices.push_back( static_cast<u16>( n ) );
    }
    // draw XY circle
    vertex.Normal.set( 0.0f, 0.0f, 1.0f);
    vertex.Pos.set( position_ );
    ellipsoidMeshBuffer_->Vertices.push_back( vertex );
    ellipsoidMeshBuffer_->Indices.push_back( 43 );
    for ( s32 n = 42; n > 0; --n )
    {
        const f32 rad = theta * static_cast<f32>( n );
        vertex.Pos.set(
                static_cast<f32>( sinf( rad ) ) * radien_.X + position_.X,
                static_cast<f32>( cosf( rad ) ) * radien_.Y + position_.Y,
                position_.Z
        );
        ellipsoidMeshBuffer_->Vertices.push_back( vertex );
        ellipsoidMeshBuffer_->Indices.push_back( static_cast<u16>( 43 + n ) );
    }
    // draw YZ circle
    vertex.Normal.set( 1.0f, 0.0f, 0.0f);
    vertex.Pos.set( position_ );
    ellipsoidMeshBuffer_->Vertices.push_back( vertex );
    ellipsoidMeshBuffer_->Indices.push_back( 86 );
    for ( s32 n = 42; n > 0; --n )
    {
        const f32 rad = theta * static_cast<f32>( n );
        vertex.Pos.set(
                position_.X,
                static_cast<f32>( sinf( rad ) ) * radien_.Y + position_.Y,
                static_cast<f32>( cosf( rad ) ) * radien_.Z + position_.Z
        );
        ellipsoidMeshBuffer_->Vertices.push_back( vertex );
        ellipsoidMeshBuffer_->Indices.push_back( static_cast<u16>( 86 + n ) );
    }
}
