#include <irrlicht.h>
#include "Logfile.h"
#include "Configuration.h"

using namespace irr;

s32 main()
{
    // Wir erstellen ein temporaeres Entchen ohne Grafik, um auf das Dateisystem
    // zugreifen zu koennen.
    IrrlichtDevice* device = createDevice( video::EDT_NULL );
    Logfile::getInstance( device->getFileSystem(),
#ifdef _DEBUG_MODE
    "debug.log", Logfile::DEBUG );
#else
    "game.log", Logfile::INFO );
#endif
    Configuration::getInstance( device->getFileSystem() );
    Configuration::getInstance().readConfigFile( "CONFIG.CFG" );
    // Das temporaere Entchen wird jetzt nicht mehr benoetigt,
    // deshalb zerstoeren wir es und geben den benutzten Speicher wieder frei.
    device->drop();
    device = 0;


    return 0;
}
