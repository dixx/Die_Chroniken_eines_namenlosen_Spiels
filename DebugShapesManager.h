#ifndef _DEBUGSHAPESMANAGER_H_EADER
#define _DEBUGSHAPESMANAGER_H_EADER

#include <irrlicht.h>
#include "DebugShape.h"

using namespace irr;

class DebugShapesManager
{

public:

    static DebugShapesManager& getInstance( video::IVideoDriver* driver = 0 );
    void createCircle( core::vector3df position, f32 radius );
    void drawAll();

private:

    video::IVideoDriver* driver_;
    core::list<DebugShape*> shapes_;
    core::list<DebugShape*>::Iterator iter_;
    video::SMaterial material_;
    DebugShapesManager( video::IVideoDriver* driver );
    DebugShapesManager( const DebugShapesManager& );
    DebugShapesManager& operator=( const DebugShapesManager& );
    ~DebugShapesManager();

};

#endif
