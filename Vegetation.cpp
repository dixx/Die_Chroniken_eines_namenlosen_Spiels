#include "Vegetation.h"



Vegetation::Vegetation()
{
	grass_ = new scene::SMesh();
}



Vegetation::~Vegetation()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    if ( grass_->getReferenceCount() > 0 )
        grass_->drop();
}



void Vegetation::create()
{
    ;
}



void Vegetation::update()
{
    ;
}



/* private */
