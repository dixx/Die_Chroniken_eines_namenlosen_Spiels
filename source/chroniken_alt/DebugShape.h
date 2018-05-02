#ifndef _DEBUGSHAPE_HEADER
#define _DEBUGSHAPE_HEADER

#include <irrlicht.h>

class DebugShape
{

public:
    DebugShape();
	virtual ~DebugShape();
    virtual void draw() = 0;
    virtual void drop() = 0;

private:
    DebugShape( const DebugShape& );
    DebugShape& operator=( const DebugShape& );

};

class DebugCircle : public DebugShape
{

public:
    DebugCircle( irr::video::IVideoDriver* driver, irr::core::vector3df position, irr::f32 radius );
    ~DebugCircle();
    void draw();
    void drop();

private:
    irr::video::IVideoDriver* driver_;
    irr::core::vector3df position_;
    irr::f32 radius_;
    irr::scene::SMeshBuffer* circleMeshBuffer_;
    DebugCircle( const DebugCircle& );
    DebugCircle& operator=( const DebugCircle& );
    void createCircleFan();

};

class DebugEllipsoid : public DebugShape
{

public:
    DebugEllipsoid( irr::video::IVideoDriver* driver, irr::core::vector3df position, irr::core::vector3df radien );
    ~DebugEllipsoid();
    void draw();
    void drop();

private:
    irr::video::IVideoDriver* driver_;
    irr::core::vector3df position_;
    irr::core::vector3df radien_;
    irr::scene::SMeshBuffer* ellipsoidMeshBuffer_;
    DebugEllipsoid( const DebugEllipsoid& );
    DebugEllipsoid& operator=( const DebugEllipsoid& );
    void createEllipsoid();

};

#endif
