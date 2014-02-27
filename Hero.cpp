#include "Hero.h"
#include "Logfile.h"
#include "HeroPunk.h"



Hero& Hero::getInstance( scene::ISceneManager* sceneManager )
{
    static Hero _instance( sceneManager );
    return _instance;
}



void Hero::load()
{
    core::stringc heroData = "ONAMEder edle Testheld@OTYPEPUNK";
    heroData += "@MOFFS0.0x14.2x0.0@MROTA0.0x-90.0x0.0@MSCAL0.6x0.6x0.6";
    heroData += "@POSXZ20.0x20.0";
    heroData += "@MTEX0GFX/sydney.bmp@MFILEGFX/OBJECTS/sydney.md2";
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



Hero::Hero( scene::ISceneManager* sceneManager )
: smgr_(sceneManager),
  hero_(0)
{
    if ( smgr_ == 0 )
        Logfile::getInstance().emergencyExit(
                "SceneManager in [Hero] nicht mehr gefunden! Abbruch." );
}



Hero::~Hero()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
}
