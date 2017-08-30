#include "Configuration.h"

namespace leviathan
{
    namespace core
    {
        Configuration::Configuration()
        : content_(),
          params_(),
          farValue_(300.0f),
          loggingLevel_(Logger::Level::INFO),
          maxFPS_(125)
        {
            params_.DriverType = irr::video::EDT_NULL;
            params_.LoggingLevel = irr::ELL_WARNING;
        }

        Configuration::~Configuration()
        {
            // nothing to do here
        }

        void Configuration::readFromFile( const irr::io::path& fileName, irr::io::IFileSystem* fileSystem )
        {
            content_.clear();
            if ( fileSystem && fileSystem->existFile( fileName ) )
            {
                fileSystem->grab();
                generateContent( fileName, fileSystem );
                fileSystem->drop();
            }
            else
            {
                content_.push_back( "" );
            }
            params_.WindowSize.Width = irr::core::strtoul10( getItem( "video", "screen_x", "800" ).c_str() );
            params_.WindowSize.Height = irr::core::strtoul10( getItem( "video", "screen_y", "600" ).c_str() );
            params_.Bits = static_cast<uint8_t>(
                    irr::core::strtoul10( getItem( "video", "color_depth", "16" ).c_str() ) );
            params_.Fullscreen = getItem( "video", "fullscreen", "false" ).equals_ignore_case( "true" );
            if ( getItem( "video", "driver" ).equals_ignore_case( "DIRECT3D9" ) ) // TODO refactor with map
                params_.DriverType = irr::video::EDT_DIRECT3D9;
            else if ( getItem( "video", "driver" ).equals_ignore_case( "DIRECT3D8" ) )
                params_.DriverType = irr::video::EDT_DIRECT3D8;
            else if ( getItem( "video", "driver" ).equals_ignore_case( "OPENGL" ) )
                params_.DriverType = irr::video::EDT_OPENGL;
            else if ( getItem( "video", "driver" ).equals_ignore_case( "BURNINGSVIDEO" ) )
                params_.DriverType = irr::video::EDT_BURNINGSVIDEO;
            else if ( getItem( "video", "driver" ).equals_ignore_case( "NULL" ) )
                params_.DriverType = irr::video::EDT_NULL;
            else
                params_.DriverType = irr::video::EDT_SOFTWARE;
            farValue_ = irr::core::strtof10( getItem( "camera", "far_value", "300.0" ).c_str() );
            if ( getItem( "general", "logging_level" ).equals_ignore_case( "ALL" ) ) // TODO refactor with map
                loggingLevel_ = Logger::Level::ALL;
            else if ( getItem( "general", "logging_level" ).equals_ignore_case( "DEBUG" ) )
                loggingLevel_ = Logger::Level::DEBUG;
            else if ( getItem( "general", "logging_level" ).equals_ignore_case( "DETAIL" ) )
                loggingLevel_ = Logger::Level::DETAIL;
            else
                loggingLevel_ = Logger::Level::INFO;
            maxFPS_ = irr::core::strtoul10( getItem( "video", "max_fps", "125" ).c_str() );
        }

        const irr::SIrrlichtCreationParameters& Configuration::getGraphicEngineParams() const
        {
            return params_;
        }

        float Configuration::getFarValue() const
        {
            return farValue_;
        }

        Logger::Level Configuration::getLoggingLevel() const
        {
            return loggingLevel_;
        }

        uint32_t Configuration::getMaxFPS() const
        {
            return maxFPS_;
        }

        int Configuration::getInt( const irr::core::stringc& section, const irr::core::stringc& key )
        {
            return static_cast<int>( irr::core::strtol10( getItem( section, key ).c_str() ) );
        }


        /* private */

        void Configuration::generateContent( const irr::io::path& fileName, irr::io::IFileSystem* fileSystem )
        {
            irr::io::IReadFile* file = fileSystem->createAndOpenFile( fileName );
            uint32_t size = static_cast<uint32_t>( file->getSize() ); // TODO add error check!
            irr::core::array<uint8_t> buffer( size + 4 );
            file->read( buffer.pointer(), size );
            file->drop();
            irr::core::stringc rawContent = buffer.const_pointer();
            rawContent.split( content_, "\n", 1, /* ignoreEmptyTokens = */ false );
        }

        const irr::core::stringc Configuration::getItem(
            const irr::core::stringc& section,
            const irr::core::stringc& key,
            const irr::core::stringc& defaultValue
        )
        {
            bool sectionFound = false;
            irr::core::stringc result;
            irr::core::stringc sectionIdent = "[";
            sectionIdent.append( section ).append( "]" );
            for ( auto& line : content_ )
            {
                if ( !sectionFound )
                {
                    if ( line.find( sectionIdent.c_str() ) == 0 )
                        sectionFound = true;
                }
                else
                {
                    if ( line[0] == '[' )
                        break;
                    if ( line[0] == '#' || line[0] == ';' )
                        continue;
                    if ( line.find( key.c_str() ) == -1 )
                        continue;
                    uint32_t valueStart = static_cast<uint32_t>( line.findFirstChar( "=" ) + 1 );
                    result = line.subString( valueStart, static_cast<int32_t>( line.size() - valueStart ) ).trim();
                    break;
                }
            }
            return result.empty() ? defaultValue : result;
        }
    }
}
