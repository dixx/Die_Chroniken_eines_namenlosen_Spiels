#include "DebugShapesManager.h"



DebugShapesManager& DebugShapesManager::getInstance( video::IVideoDriver* driver )
{
    static DebugShapesManager instance( driver );
    return instance;
}



void DebugShapesManager::createCircle( core::vector3df position, f32 radius )
{
    shapes_.push_back( new DebugCircle( driver_, position, radius ) );
}



void DebugShapesManager::drawAll()
{
    driver_->setMaterial( material_ );
    for ( iter_ = shapes_.begin(); iter_ != shapes_.end(); ++iter_ )
    {
        DebugShape* shape = *iter_;
        shape->draw();
        shape->drop();
    }
    shapes_.clear();
}



DebugShapesManager::DebugShapesManager( video::IVideoDriver* driver )
: driver_(driver)
{
    if ( driver_ == 0 )
        exit(1);
    shapes_.clear();
    iter_ = shapes_.end();
    material_ = video::SMaterial();
    material_.Thickness = 2.0f;
    material_.Lighting = false;
}



DebugShapesManager::~DebugShapesManager()
{
    for ( iter_ = shapes_.begin(); iter_ != shapes_.end(); ++iter_ )
    {
        DebugShape* shape = *iter_;
        shape->drop();
    }
    shapes_.clear();
}
