#include "Hero.h"
#include "Logfile.h"
#include "HeroPunk.h"



Hero& Hero::getInstance( irr::scene::ISceneManager* sceneManager )
{
    static Hero instance( sceneManager );
    return instance;
}



void Hero::load()
{
    irr::core::stringc heroData = "ONAMEder edle Testheld@OTYPEPUNK@MOFFS0.0x0.6x0.0@MROTA0.0x-90.0x0.0";
    heroData += "@MSCAL0.025x0.025x0.025@POSXZ11.0x11.0@MTEX0GFX/sydney.bmp@MFILEGFX/OBJECTS/sydney.md2";
    hero_ = new HeroPunk( heroData, smgr_ );
}



void Hero::unload()
{
    delete hero_;
    hero_ = 0;
}



BasicHero* Hero::current()
{
    return hero_;
}



/* private */



Hero::Hero( irr::scene::ISceneManager* sceneManager )
: smgr_(sceneManager),
  hero_(0)
{
    if ( smgr_ == 0 )
        Logfile::getInstance().emergencyExit( "SceneManager in [Hero] nicht mehr gefunden! Abbruch." );
}



Hero::~Hero()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
}
