#include "Configuration.h"
#include "Logger.h"

namespace leviathan
{
    namespace core
    {
        Configuration::Configuration( irr::io::IFileSystem* fileSystem )
        : fileSystem_(fileSystem),
          params_(),
          farValue_(300.0f)
        {
            if ( fileSystem_ == 0 )
                exit( 1 );
        }

        Configuration::~Configuration()
        {
            // nothing to do here
        }

        void Configuration::readFromFile( const irr::io::path& fileName )
        {
            (void)fileName;
            // Logfile& logfile = Logfile::getInstance();
            // if ( fileSystem_->existFile( filename ) == false )
            // {
            //     logfile.write( Logfile::INFO, "Konfigdatei ", filename );
            //     logfile.writeLine( Logfile::INFO, " existiert nicht, wird jetzt mit Standardwerten erstellt." );
            //     writeConfigFile( filename );
            // }
            // irr::io::IReadFile* configfile = fileSystem_->createAndOpenFile( filename );
            // if ( configfile == 0 )
            // {
            //     logfile.write( Logfile::INFO, "Konfigdatei ", filename );
            //     logfile.emergencyExit( " konnte nicht geöffnet werden!" );
            // }
            // irr::u32 size = (irr::u32)configfile->getSize();
            // // 8bit Integer-Array nehmen, da read() nur in Byte-Schritten einliest!
            // irr::u8 buffer[ size + 4 ];
            // if ( configfile->read( &buffer, size ) != static_cast<irr::s32>( size ) )
            // {
            //     configfile->drop();
            //     logfile.write( Logfile::INFO, "Fehler beim Lesen von Konfigdatei ", filename );
            //     logfile.emergencyExit( "! Buffer überschritten!" );
            // }
            // configfile->drop();
            // configfile = 0;
            // irr::core::stringc inhalt = buffer;
            // colorDepht_ = (irr::u16)irr::core::strtol10( getItem( inhalt, "video", "farbtiefe", "16" ).c_str() );
            // screenSizeX_ = (irr::u16)irr::core::strtol10( getItem( inhalt, "video", "screen_x", "640" ).c_str() );
            // screenSizeY_ = (irr::u16)irr::core::strtol10( getItem( inhalt, "video", "screen_y", "480" ).c_str() );
            // fullscreen_ = getItem( inhalt, "video", "fullscreen", "false" ).equals_ignore_case( "true" );
            // irr::core::stringc rendermode = getItem( inhalt, "video", "rendermode", "SOFTWARE" );
            // if ( rendermode.equals_ignore_case( "DIRECT3D9" ) )
            //     rendermode_ = irr::video::EDT_DIRECT3D9;
            // else if ( rendermode.equals_ignore_case( "DIRECT3D8" ) )
            //     rendermode_ = irr::video::EDT_DIRECT3D8;
            // else if ( rendermode.equals_ignore_case( "OPENGL" ) )
            //     rendermode_ = irr::video::EDT_OPENGL;
            // else if ( rendermode.equals_ignore_case( "SOFTWARE" ) )
            //     rendermode_ = irr::video::EDT_SOFTWARE;
            // else if ( rendermode.equals_ignore_case( "BURNINGSVIDEO" ) )
            //     rendermode_ = irr::video::EDT_BURNINGSVIDEO;
            // else if ( rendermode.equals_ignore_case( "NULL" ) )
            //     rendermode_ = irr::video::EDT_NULL;
            // else
            //     logfile.emergencyExit( "\nKein passender Treiber gewählt! Abbruch." );
            // farValue_ = irr::core::strtof10( getItem( inhalt, "video", "sichtweite", "300.0" ).c_str() );
        //    printf("\nms:%f\n", core::fast_atof(
        //            this->getItem( inhalt, "input", "mouse_sensitivity", "1.0f" ).c_str() ) );
        }

        void Configuration::writeToFile( const irr::io::path& fileName )
        {
            (void)fileName;
            // irr::core::stringc inhalt = "";
            // inhalt += "######################################################################\r\n#\r\n";
            // inhalt += "#  Konfig-Datei. Werte nach Belieben ändern (ausser die Bezeichner\r\n";
            // inhalt += "#  in eckigen Klammern und jene vor dem '='),\r\n";
            // inhalt += "#  aber dann auch die Konsequenzen tragen.     ---Spass haben!---\r\n#\r\n";
            // inhalt += "######################################################################\r\n#\r\n";
            // inhalt += "#  - Kommentare müssen in einer eigenen Zeile stehen.\r\n";
            // inhalt += "#  - ACHTUNG: '=' darf in einer Zeichenkette nicht verwendet werden.\r\n";
            // inhalt += "#    (außer natürlich in Kommentaren ;-)\r\n";
            // inhalt += "#  - Bei FLOAT und INT auf Komma (den Punkt) achten.\r\n";
            // inhalt += "#  - Auf Groß- und Kleinschreibung achten.\r\n";
            // inhalt += "#  - Verzeichnis-Trenner: '/'\r\n";
            // inhalt += "#  - relative und absolute Pfadangaben möglich\r\n";
            // inhalt += "#\r\n\r\n\r\n";
            // inhalt += "# Bildschirm-Auflösung\r\n";
            // inhalt += "video.screen_x = ";
            // inhalt += screenSizeX_;
            // inhalt += "\r\nvideo.screen_y = ";
            // inhalt += screenSizeY_;
            // inhalt += "\r\n# Farbtiefe: 16bit, 32bit\r\n";
            // inhalt += "video.farbtiefe = ";
            // inhalt += colorDepht_;
            // inhalt += "\r\nvideo.fullscreen = ";
            // inhalt += ( fullscreen_ == true ) ? "true" : "false";
            // inhalt += "\r\n# modi: DIRECT3D8, DIRECT3D9, OPENGL, SOFTWARE (slow!), BURNINGSVIDEO, NULL\r\n";
            // inhalt += "video.rendermode = ";
            // switch ( rendermode_ )
            // {
            //     case irr::video::EDT_DIRECT3D9:      inhalt += "DIRECT3D9"; break;
            //     case irr::video::EDT_DIRECT3D8:      inhalt += "DIRECT3D8"; break;
            //     case irr::video::EDT_OPENGL:         inhalt += "OPENGL"; break;
            //     case irr::video::EDT_SOFTWARE:       inhalt += "SOFTWARE"; break;
            //     case irr::video::EDT_BURNINGSVIDEO:  inhalt += "BURNINGSVIDEO"; break;
            //     case irr::video::EDT_NULL:           inhalt += "NULL"; break;
            //     default:                        inhalt += "SOFTWARE"; break;
            // }
            // inhalt += "\r\nvideo.sichtweite = ";
            // inhalt += farValue_;
            // inhalt += "\r\n\r\n\r\n# Maus.Sensibilität\r\n";
            // inhalt += "# input.mouse_sensitivity = 1.442\r\n";
            // irr::io::IWriteFile* configfile = fileSystem_->createAndWriteFile( filename );
            // if ( configfile == 0 )
            // {
            //     Logfile::getInstance().write( Logfile::INFO, "Konfigdatei ", filename );
            //     Logfile::getInstance().emergencyExit( " konnte nicht geöffnet werden!" );
            // }
            // configfile->write( inhalt.c_str(), inhalt.size() );
            // configfile->drop();
            // configfile = 0;
        }

        irr::f32 Configuration::getFarValue() const
        {
            return farValue_;
        }

        /* private */

        // TODO refactor!
        const irr::core::stringc Configuration::getItem(
                const irr::core::stringc& content,
                const irr::c8* topic,
                const irr::c8* itemName,
                const irr::c8* origin
        )
        {
            if ( content.size() == 0 )
                return origin;
            irr::core::stringc line;
            irr::s32 startindex = 0;
            irr::s32 eqindex = 0;
            irr::s32 lastindex = static_cast<irr::s32>( content.size() ) - 1;
            irr::core::stringc searchset = "";
            searchset += topic;
            searchset += '.';
            searchset += itemName;
            // startindex wird jetzt immer weiter geschoben, bis das Ende von "inhalt" erreicht ist
            while ( startindex < static_cast<irr::s32>( content.size() ) )
            {
                lastindex = content.findNext( '\n', static_cast<irr::u32>( startindex + 1 ) );
                if ( lastindex == -1 )
                    lastindex = static_cast<irr::s32>( content.size() ) - 1;
                line = content.subString( static_cast<irr::u32>( startindex ), lastindex - startindex );
                startindex = lastindex;
                if ( line.find( searchset.c_str() ) == -1 )
                    continue;
                eqindex = line.findFirst( '=' );
                if ( eqindex == -1 )
                    continue;
                if ( line.findFirst( '#' ) != -1 && line.findFirst( '#' ) < eqindex )
                    continue;
                return line.subString( static_cast<irr::u32>( eqindex + 1 ), lastindex - eqindex  ).trim();
            }
            return origin;
        }
    }
}
