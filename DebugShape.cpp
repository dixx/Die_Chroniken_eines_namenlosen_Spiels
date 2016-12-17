#include "DebugShape.h"



DebugShape::DebugShape()
{
}



DebugShape::~DebugShape()
{
}



DebugCircle::DebugCircle( irr::video::IVideoDriver* driver, irr::core::vector3df position, irr::f32 radius )
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
    driver_->setTransform( irr::video::ETS_WORLD, irr::core::matrix4() );
    driver_->draw3DLine( circleMeshBuffer_->Vertices[ 41 ].Pos, circleMeshBuffer_->Vertices[ 1 ].Pos );
    for ( irr::u32 i = 1; i < circleMeshBuffer_->Vertices.size() - 1; ++i )
        driver_->draw3DLine( circleMeshBuffer_->Vertices[ i ].Pos, circleMeshBuffer_->Vertices[ i + 1 ].Pos );
}



void DebugCircle::drop()
{
    delete this;
}



void DebugCircle::createCircleFan()
{
    circleMeshBuffer_ = new irr::scene::SMeshBuffer;
    irr::video::S3DVertex vertex;
    vertex.Normal.set( 0.0f, 1.0f, 0.0f);
    vertex.Pos.set( position_.X, 0.2f, position_.Z );
    circleMeshBuffer_->Vertices.push_back( vertex );
    circleMeshBuffer_->Indices.push_back( 0 );
    circleMeshBuffer_->getMaterial().Lighting = false;
    for ( irr::s32 n = 42; 0 <= n; --n )
    {
        const irr::f32 x = ( irr::core::PI * 2.0f ) * static_cast<irr::f32>( n ) / static_cast<irr::f32>( 42 );
        vertex.Pos.set(
                static_cast<irr::f32>( sinf( x ) ) * radius_ + position_.X,
                0.2f,
                static_cast<irr::f32>( cosf( x ) ) * radius_ + position_.Z
        );
        circleMeshBuffer_->Vertices.push_back( vertex );
        circleMeshBuffer_->Indices.push_back( static_cast<irr::u16>( n + 1 ) );
    }
}



DebugEllipsoid::DebugEllipsoid( irr::video::IVideoDriver* driver, irr::core::vector3df position, irr::core::vector3df radien )
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
    driver_->setTransform( irr::video::ETS_WORLD, irr::core::matrix4() );
    driver_->draw3DLine( ellipsoidMeshBuffer_->Vertices[ 42 ].Pos, ellipsoidMeshBuffer_->Vertices[ 1 ].Pos );
    driver_->draw3DLine( ellipsoidMeshBuffer_->Vertices[ 85 ].Pos, ellipsoidMeshBuffer_->Vertices[ 44 ].Pos );
    driver_->draw3DLine( ellipsoidMeshBuffer_->Vertices[ 128 ].Pos, ellipsoidMeshBuffer_->Vertices[ 87 ].Pos );
    for ( irr::u32 i = 1; i < 42; ++i )
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
    ellipsoidMeshBuffer_ = new irr::scene::SMeshBuffer;
    irr::video::S3DVertex vertex;
    ellipsoidMeshBuffer_->getMaterial().Lighting = false;
    irr::f32 theta = 2 * irr::core::PI / 42.f;
    // draw XZ circle
    vertex.Normal.set( 0.0f, 1.0f, 0.0f);
    vertex.Pos.set( position_ );
    ellipsoidMeshBuffer_->Vertices.push_back( vertex );
    ellipsoidMeshBuffer_->Indices.push_back( 0 );
    for ( irr::s32 n = 42; n > 0; --n )
    {
        const irr::f32 rad = theta * static_cast<irr::f32>( n );
        vertex.Pos.set(
                static_cast<irr::f32>( sinf( rad ) ) * radien_.X + position_.X,
                position_.Y,
                static_cast<irr::f32>( cosf( rad ) ) * radien_.Z + position_.Z
        );
        ellipsoidMeshBuffer_->Vertices.push_back( vertex );
        ellipsoidMeshBuffer_->Indices.push_back( static_cast<irr::u16>( n ) );
    }
    // draw XY circle
    vertex.Normal.set( 0.0f, 0.0f, 1.0f);
    vertex.Pos.set( position_ );
    ellipsoidMeshBuffer_->Vertices.push_back( vertex );
    ellipsoidMeshBuffer_->Indices.push_back( 43 );
    for ( irr::s32 n = 42; n > 0; --n )
    {
        const irr::f32 rad = theta * static_cast<irr::f32>( n );
        vertex.Pos.set(
                static_cast<irr::f32>( sinf( rad ) ) * radien_.X + position_.X,
                static_cast<irr::f32>( cosf( rad ) ) * radien_.Y + position_.Y,
                position_.Z
        );
        ellipsoidMeshBuffer_->Vertices.push_back( vertex );
        ellipsoidMeshBuffer_->Indices.push_back( static_cast<irr::u16>( 43 + n ) );
    }
    // draw YZ circle
    vertex.Normal.set( 1.0f, 0.0f, 0.0f);
    vertex.Pos.set( position_ );
    ellipsoidMeshBuffer_->Vertices.push_back( vertex );
    ellipsoidMeshBuffer_->Indices.push_back( 86 );
    for ( irr::s32 n = 42; n > 0; --n )
    {
        const irr::f32 rad = theta * static_cast<irr::f32>( n );
        vertex.Pos.set(
                position_.X,
                static_cast<irr::f32>( sinf( rad ) ) * radien_.Y + position_.Y,
                static_cast<irr::f32>( cosf( rad ) ) * radien_.Z + position_.Z
        );
        ellipsoidMeshBuffer_->Vertices.push_back( vertex );
        ellipsoidMeshBuffer_->Indices.push_back( static_cast<irr::u16>( 86 + n ) );
    }
}
