#include "HeroPunk.h"
#include "Logfile.h"



HeroPunk::HeroPunk( const core::stringc& punkData, scene::ISceneManager* smgr )
: BasicHero(punkData, smgr, true)
{
    if ( smgr_ == 0 )
    {
        Logfile::getInstance().emergencyExit(
                "SceneManager in [HeroPunk] nicht mehr gefunden! Abbruch." );
    }
    init();
    deleteExtractor();
}



HeroPunk::~HeroPunk()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
}



/* private */



void HeroPunk::init()
{
    ;
}
