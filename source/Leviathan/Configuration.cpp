#include "Configuration.h"
#include "Logger.h"

namespace leviathan
{
    namespace core
    {
        Configuration::Configuration( irr::io::IFileSystem* fileSystem )
        : fileSystem_(fileSystem),
          content_(),
          params_(),
          farValue_(300.0f)
        {
            if ( fileSystem_ == 0 )
                exit( 1 );
            fileSystem_->grab();
            params_.DriverType = irr::video::EDT_SOFTWARE;
        }

        Configuration::~Configuration()
        {
            fileSystem_->drop();
        }

        void Configuration::readFromFile( const irr::io::path& fileName )
        {
            content_.clear();
            if ( fileSystem_->existFile( fileName ) )
                generateContent( fileName );
            else
                content_.push_back( "" );
            params_.WindowSize.Width = irr::core::strtoul10( getItem( "video", "screen_x", "800" ).c_str() );
            params_.WindowSize.Height = irr::core::strtoul10( getItem( "video", "screen_y", "600" ).c_str() );
            params_.Bits = static_cast<irr::u8>(
                    irr::core::strtoul10( getItem( "video", "color_depth", "16" ).c_str() ) );
            params_.Fullscreen = getItem( "video", "fullscreen", "false" ).equals_ignore_case( "true" );
            if ( getItem( "video", "driver" ).equals_ignore_case( "DIRECT3D9" ) )
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
        }

        const irr::SIrrlichtCreationParameters& Configuration::getGraphicEngineParams() const
        {
            return params_;
        }

        irr::f32 Configuration::getFarValue() const
        {
            return farValue_;
        }

        int Configuration::getInt( const irr::core::stringc& section, const irr::core::stringc& key )
        {
            return static_cast<int>( irr::core::strtol10( getItem( section, key ).c_str() ) );
        }


        /* private */

        void Configuration::generateContent( const irr::io::path& fileName )
        {
            irr::io::IReadFile* file = fileSystem_->createAndOpenFile( fileName );
            irr::u32 size = (irr::u32)file->getSize();
            irr::u8 buffer[ size + 4 ];
            file->read( &buffer, size );
            file->drop();
            irr::core::stringc rawContent = buffer;
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
            for ( irr::core::list<irr::core::stringc>::Iterator it = content_.begin(); it != content_.end(); ++it )
            {
                irr::core::stringc line = *it;
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
                    irr::u32 valueStart = static_cast<irr::u32>( line.findFirstChar( "=" ) + 1 );
                    result = line.subString( valueStart, static_cast<irr::s32>( line.size() - valueStart ) ).trim();
                    break;
                }
            }
            return result.empty() ? defaultValue : result;
        }
    }
}
