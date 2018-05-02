#ifndef _DEBUGSHAPESMANAGER_H_EADER
#define _DEBUGSHAPESMANAGER_H_EADER

#include <irrlicht.h>
#include "DebugShape.h"

class DebugShapesManager
{

public:

    static DebugShapesManager& getInstance( irr::video::IVideoDriver* driver = 0 );
    void createCircle( irr::core::vector3df position, irr::f32 radius );
    void createEllipsoid( irr::core::vector3df position, irr::core::vector3df radien );
    void drawAll();

private:

    irr::video::IVideoDriver* driver_;
    irr::core::list<DebugShape*> shapes_;
    irr::core::list<DebugShape*>::Iterator iter_;
    irr::video::SMaterial material_;
    DebugShapesManager( irr::video::IVideoDriver* driver );
    DebugShapesManager( const DebugShapesManager& );
    DebugShapesManager& operator=( const DebugShapesManager& );
    ~DebugShapesManager();

};

#endif
