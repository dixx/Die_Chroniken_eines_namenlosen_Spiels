#ifndef _DEBUGSHAPE_HEADER
#define _DEBUGSHAPE_HEADER

#include <irrlicht.h>

using namespace irr;

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
    DebugCircle( video::IVideoDriver* driver, core::vector3df position, f32 radius );
    ~DebugCircle();
    void draw();
    void drop();

private:
    video::IVideoDriver* driver_;
    core::vector3df position_;
    f32 radius_;
    scene::SMeshBuffer* circleMeshBuffer_;
    DebugCircle( const DebugCircle& );
    DebugCircle& operator=( const DebugCircle& );
    void createCircleFan();

};

class DebugEllipsoid : public DebugShape
{

public:
    DebugEllipsoid( video::IVideoDriver* driver, core::vector3df position, core::vector3df radien );
    ~DebugEllipsoid();
    void draw();
    void drop();

private:
    video::IVideoDriver* driver_;
    core::vector3df position_;
    core::vector3df radien_;
    scene::SMeshBuffer* ellipsoidMeshBuffer_;
    DebugEllipsoid( const DebugEllipsoid& );
    DebugEllipsoid& operator=( const DebugEllipsoid& );
    void createEllipsoid();

};

#endif
