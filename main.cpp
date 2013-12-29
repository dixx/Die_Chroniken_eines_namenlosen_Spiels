#include <irrlicht.h>
#include "Configuration.h"
#include "Eventreceiver.h"
#include "Logfile.h"

using namespace irr;

s32 main()
{
    // Wir erstellen ein temporäres Entchen ohne Grafik, um auf das Dateisystem
    // zugreifen zu können.
    IrrlichtDevice* device = createDevice( video::EDT_NULL );
    if ( device == 0 )
        return 1;
    Logfile& logfile = Logfile::getInstance( device->getFileSystem(),
#ifdef _DEBUG_MODE
    "debug.log", Logfile::DEBUG );
#else
    "game.log", Logfile::INFO );
#endif
    Configuration& config = Configuration::getInstance(
            device->getFileSystem() );
    config.readConfigFile( "CONFIG.CFG" );
    // Das hässliche temporäre Entchen wird jetzt nicht mehr benötigt,
    // deshalb zerstören wir es und geben den benutzten Speicher wieder frei.
    device->drop();
    // Nun können wir das eigentliche Entchen mit den Config-Werten erstellen.
    Eventreceiver& eventreceiver = Eventreceiver::getInstance();
    eventreceiver.setEventReactionActive( false, false, false );
    device = createDevice(
            config.getRenderMode(),
            config.getScreenSize(),
            config.getColorDepht(),
            config.isFullScreen(),
            true,
            config.isFullScreen(),
            &eventreceiver
    );
    if ( device == 0 )
        return 1;
    io::IFileSystem* filesystem = device->getFileSystem();
    video::IVideoDriver* driver = device->getVideoDriver();
//    scene::ISceneManager* scenemanager = device->getSceneManager();
    logfile.setNewFilesystem( filesystem );
    config.setNewFilesystem( filesystem );
    logfile.writeLine( Logfile::DETAIL, "3D-Entchen erfolgreich erstellt." );
    logfile.writeLine( Logfile::DETAIL, "    Version: IrrLicht ",
            device->getVersion() );
    logfile.writeLine( Logfile::DETAIL, "    Treiber: ", driver->getName() );


    return 0;
}
