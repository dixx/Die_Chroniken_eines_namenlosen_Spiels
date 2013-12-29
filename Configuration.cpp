#include "Configuration.h"
#include "Logfile.h"



Configuration& Configuration::getInstance( io::IFileSystem* fs )
{
    static Configuration instance_( fs );
    return instance_;
}



void Configuration::setNewFilesystem( io::IFileSystem* fs )
{
    if ( fs == 0 )
    {
        Logfile::getInstance().emergencyExit(
                "Dateisystem in [setNewFilesystem] nicht mehr gefunden!" \
                " Abbruch."
        );
    }
    fs_ = fs;
}



void Configuration::readConfigFile( const c8* filename )
{
    Logfile& logfile = Logfile::getInstance();
    if ( fs_->existFile( filename ) == false )
    {
        logfile.write( Logfile::INFO, "Konfigdatei ", filename );
        logfile.writeLine( Logfile::INFO,
                " existiert nicht, wird jetzt mit Standardwerten erstellt." );
        writeConfigFile( filename );
    }
    io::IReadFile* configfile = fs_->createAndOpenFile( filename );
    if ( configfile == 0 )
    {
        logfile.write( Logfile::INFO, "Konfigdatei ", filename );
        logfile.emergencyExit( " konnte nicht geöffnet werden!" );
    }
    u32 size = configfile->getSize();
    // 8bit Integer-Array nehmen, da read() nur in Byte-Schritten einliest!
    u8 buffer[ size + 4 ];
    if ( configfile->read( &buffer, size ) != static_cast<s32>( size ) )
    {
        configfile->drop();
        logfile.write(
                Logfile::INFO,
                "Fehler beim Lesen von Konfigdatei ",
                filename
        );
        logfile.emergencyExit( "! Buffer überschritten!" );
    }
    configfile->drop();
    configfile = 0;
    core::stringc inhalt = buffer;
    colorDepht_ = (u16)core::strtol10(
            getItem( inhalt, "video", "farbtiefe", "16" ).c_str() );
    screenSizeX_ = (u16)core::strtol10(
            getItem( inhalt, "video", "screen_x", "640" ).c_str() );
    screenSizeY_ = (u16)core::strtol10(
            getItem( inhalt, "video", "screen_y", "480" ).c_str() );
    fullscreen_ = getItem(
            inhalt, "video", "fullscreen", "false"
    ).equals_ignore_case( "true" );
    core::stringc rendermode = getItem(
            inhalt, "video", "rendermode", "SOFTWARE" );
    if ( rendermode.equals_ignore_case( "DIRECT3D9" ) )
        rendermode_ = video::EDT_DIRECT3D9;
    else if ( rendermode.equals_ignore_case( "DIRECT3D8" ) )
        rendermode_ = video::EDT_DIRECT3D8;
    else if ( rendermode.equals_ignore_case( "OPENGL" ) )
        rendermode_ = video::EDT_OPENGL;
    else if ( rendermode.equals_ignore_case( "SOFTWARE" ) )
        rendermode_ = video::EDT_SOFTWARE;
    else if ( rendermode.equals_ignore_case( "BURNINGSVIDEO" ) )
        rendermode_ = video::EDT_BURNINGSVIDEO;
    else if ( rendermode.equals_ignore_case( "NULL" ) )
        rendermode_ = video::EDT_NULL;
    else
    {
        logfile.emergencyExit( "\nKein passender Treiber gewählt! Abbruch." );
    }
    farValue_ = core::strtof10(
            getItem( inhalt, "video", "sichtweite", "300.0" ).c_str() );
//    printf("\nms:%f\n", core::fast_atof(
//            this->getItem( inhalt, "input", "mouse_sensitivity", "1.0f" ).c_str() )
//            );
}



void Configuration::writeConfigFile( const c8* filename )
{
    core::stringc inhalt = "";
    inhalt += "##############################################################";
    inhalt += "########\r\n#\r\n";
    inhalt += "#  Konfig-Datei. Werte nach Belieben ändern (ausser die Bezei";
    inhalt += "chner\r\n";
    inhalt += "#  in eckigen Klammern und jene vor dem '='),\r\n";
    inhalt += "#  aber dann auch die Konsequenzen tragen.     ---Spass haben!";
    inhalt += "---\r\n#\r\n";
    inhalt += "##############################################################";
    inhalt += "########\r\n#\r\n";
    inhalt += "#  - Kommentare müssen in einer eigenen Zeile stehen.\r\n";
    inhalt += "#  - ACHTUNG: '=' darf in einer Zeichenkette nicht verwendet ";
    inhalt += "werden.\r\n";
    inhalt += "#    (außer natürlich in Kommentaren ;-)\r\n";
    inhalt += "#  - Bei FLOAT und INT auf Komma (den Punkt) achten.\r\n";
    inhalt += "#  - Auf Groß- und Kleinschreibung achten.\r\n";
    inhalt += "#  - Verzeichnis-Trenner: '/'\r\n";
    inhalt += "#  - relative und absolute Pfadangaben möglich\r\n";
    inhalt += "#\r\n\r\n\r\n";
    inhalt += "# Bildschirm-Auflösung\r\n";
    inhalt += "video.screen_x = ";
    inhalt += screenSizeX_;
    inhalt += "\r\nvideo.screen_y = ";
    inhalt += screenSizeY_;
    inhalt += "\r\n# Farbtiefe: 16bit, 32bit\r\n";
    inhalt += "video.farbtiefe = ";
    inhalt += colorDepht_;
    inhalt += "\r\nvideo.fullscreen = ";
    inhalt += ( fullscreen_ == true ) ? "true" : "false";
    inhalt += "\r\n# modi: DIRECT3D8, DIRECT3D9, OPENGL, SOFTWARE (slow!), ";
    inhalt += "BURNINGSVIDEO, NULL\r\n";
    inhalt += "video.rendermode = ";
    switch ( rendermode_ )
    {
        case video::EDT_DIRECT3D9:      inhalt += "DIRECT3D9"; break;
        case video::EDT_DIRECT3D8:      inhalt += "DIRECT3D8"; break;
        case video::EDT_OPENGL:         inhalt += "OPENGL"; break;
        case video::EDT_SOFTWARE:       inhalt += "SOFTWARE"; break;
        case video::EDT_BURNINGSVIDEO:  inhalt += "BURNINGSVIDEO"; break;
        case video::EDT_NULL:           inhalt += "NULL"; break;
        default:                        inhalt += "SOFTWARE"; break;
    }
    inhalt += "\r\nvideo.sichtweite = ";
    inhalt += farValue_;
    inhalt += "\r\n\r\n\r\n# Maus.Sensibilität\r\n";
    inhalt += "# input.mouse_sensitivity = 1.442\r\n";
    io::IWriteFile* configfile = fs_->createAndWriteFile( filename );
    if ( configfile == 0 )
    {
        Logfile::getInstance().write(
                Logfile::INFO, "Konfigdatei ", filename );
        Logfile::getInstance().emergencyExit(
                " konnte nicht geöffnet werden!" );
    }
    configfile->write( inhalt.c_str(), inhalt.size() );
    configfile->drop();
    configfile = 0;
}



core::dimension2du Configuration::getScreenSize() const
{
    return core::dimension2du( screenSizeX_, screenSizeY_ );
}



u16 Configuration::getColorDepht() const
{
    return colorDepht_;
}



bool Configuration::isFullScreen() const
{
    return fullscreen_;
}



video::E_DRIVER_TYPE Configuration::getRenderMode() const
{
    return rendermode_;
}



f32 Configuration::getFarValue() const
{
    return farValue_;
}



/* private */



Configuration::Configuration( io::IFileSystem* fs )
: fs_(fs),
  screenSizeX_(640),
  screenSizeY_(480),
  colorDepht_(16),
  fullscreen_(false),
  farValue_(300.0f),
  rendermode_(video::EDT_SOFTWARE)
{
    if ( fs_ == 0 )
    {
        Logfile::getInstance().emergencyExit(
                "Dateisystem in [Configuration] nicht mehr gefunden! Abbruch."
        );
    }
}



Configuration::~Configuration()
{
    // nothing to do here
}



const core::stringc Configuration::getItem( const core::stringc& content,
        const c8* topic, const c8* varname, const c8* origin )
{
    core::stringc line;
    s32 startindex = 0;
    s32 eqindex = 0;
    s32 lastindex = content.size() - 1;
    core::stringc searchset = "";
    searchset += topic;
    searchset += '.';
    searchset += varname;
    // startindex wird jetzt immer weiter geschoben, bis das Ende von "inhalt"
    // erreicht ist
    while ( startindex < static_cast<s32>( content.size() ) )
    {
        lastindex = content.findNext( '\n', startindex + 1 );
        if ( lastindex == -1 )
            lastindex = content.size() - 1;
        line = content.subString( startindex, lastindex - startindex );
        startindex = lastindex;
        if ( line.find( searchset.c_str() ) == -1 )
            continue;
        eqindex = line.findFirst( '=' );
        if ( eqindex == -1 )
            continue;
        if ( line.findFirst( '#' ) != -1 && line.findFirst( '#' ) < eqindex )
            continue;
        return line.subString( eqindex + 1, lastindex - eqindex  ).trim();
    }
    return origin;
}
