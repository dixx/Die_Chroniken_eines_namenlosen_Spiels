#include "HeroPunk.h"
#include "Logfile.h"



HeroPunk::HeroPunk( const irr::core::stringc& punkData, irr::scene::ISceneManager* smgr )
: BasicHero( punkData, smgr, true )
{
    if ( smgr_ == 0 )
        Logfile::getInstance().emergencyExit( "SceneManager in [HeroPunk] nicht mehr gefunden! Abbruch." );
    init();
    deleteExtractor();
}



HeroPunk::~HeroPunk()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
}



irr::core::stringc HeroPunk::getObjectData()
{
    return "";
}



/* private */



void HeroPunk::init()
{
    ;
}
