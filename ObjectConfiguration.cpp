#include "ObjectConfiguration.h"
#include "Logfile.h"

// these defines are for better readability only
#define UNKNOWN_FILE_FORMAT "Unbekanntes Dateiformat! Abbruch."
#define BROKEN_STREAM "Schreiben in Datei fehlgeschlagen! Abbruch."



ObjectConfiguration::ObjectConfiguration()
:   CURRENT_VERSION(0)
{
    object = new ObjectConfigurationContextForObject;
    node = new ObjectConfigurationContextForNode;
    mesh = new ObjectConfigurationContextForMesh;
    materials = new ObjectConfigurationContextForMaterials;
    files = new ObjectConfigurationContextForFiles;
}



void ObjectConfiguration::readFrom( io::IReadFile* stream, u32 version )
{
    // we now read a certain amount of entities from the stream, in a specific order
    if ( version == 0 )
    {
        object->type = static_cast<ObjectConfigurationContextForObject::ObjectType>( read<u8>( stream ) );
        node->name = readString( stream );
        mesh->position = read<core::vector3df>( stream );
        mesh->offset = read<core::vector3df>( stream );
        mesh->scale = read<core::vector3df>( stream );
        mesh->rotation = read<core::vector3df>( stream );
        mesh->materialCount = read<u32>( stream );
        for ( register u32 i = 0; i < mesh->materialCount; ++i )
        {
            materials->isTransparent.push_back( read<bool>( stream ) );
            materials->isBackFaceCulled.push_back( read<bool>( stream ) );
            files->mainTexture.push_back( readString( stream ) );
            files->secondTexture.push_back( readString( stream ) );
        }
        files->mesh = readString( stream );
    }
    else if ( version > 0 )
    {
        // handle in next version ;)
    }
    else
    {
        core::stringc errorMessage = "Dateiversion ";
        errorMessage += version;
        errorMessage += " unbekannt! Abbruch." ;
        Logfile::getInstance().emergencyExit( errorMessage );
    }
}



void ObjectConfiguration::writeTo( io::IWriteFile* stream )
{
    write<u8>( stream, object->type );
    writeString( stream, node->name );
    write<core::vector3df>( stream, mesh->position );
    write<core::vector3df>( stream, mesh->offset );
    write<core::vector3df>( stream, mesh->scale );
    write<core::vector3df>( stream, mesh->rotation );
    write<u32>( stream, mesh->materialCount );
    for ( register u32 i = 0; i < mesh->materialCount; ++i )
    {
        write<bool>( stream, materials->isTransparent[ i ] );
        write<bool>( stream, materials->isBackFaceCulled[ i ] );
        writeString( stream, files->mainTexture[ i ] );
        writeString( stream, files->secondTexture[ i ] );
    }
    writeString( stream, files->mesh );
}



ObjectConfiguration::~ObjectConfiguration()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    delete files;
    delete materials;
    delete mesh;
    delete node;
    delete object;
}



/* private */


// TODO File-Methoden auslagern nach eigener Klasse!
template <typename T> T ObjectConfiguration::read( io::IReadFile* stream )
{
    T buffer;
    u32 bytes = sizeof( typeof( buffer ) );
    if ( stream->read( &buffer, bytes ) < static_cast<s32>( bytes ) )
        Logfile::getInstance().emergencyExit( UNKNOWN_FILE_FORMAT );
    return buffer;
}



core::stringc ObjectConfiguration::readString( io::IReadFile* stream )
{
    u32 count = read<u32>( stream );
    u8* buffer = new u8[count];
    if ( stream->read( buffer, count ) < static_cast<s32>( count ) )
        Logfile::getInstance().emergencyExit( UNKNOWN_FILE_FORMAT );
    core::stringc ret = core::stringc( buffer );
    delete[] buffer;
    return ret;
}



template <typename T> void ObjectConfiguration::write( io::IWriteFile* stream, const T& number )
{
    if ( stream->write( &number, sizeof( T ) ) < static_cast<s32>( sizeof( T ) ) )
        Logfile::getInstance().emergencyExit( BROKEN_STREAM );
}
// explicit instantiations:
template void ObjectConfiguration::write<bool>( io::IWriteFile* stream, const bool& number );
template void ObjectConfiguration::write<u8>( io::IWriteFile* stream, const u8& number );
template void ObjectConfiguration::write<u32>( io::IWriteFile* stream, const u32& number );
template void ObjectConfiguration::write<core::vector3df>( io::IWriteFile* stream, const core::vector3df& number );



void ObjectConfiguration::writeString( io::IWriteFile* stream, const core::stringc& text )
{
    u32 count = text.size() + 1; // + 1 == trailing \0
    if ( stream->write( &count, sizeof( u32 ) ) < static_cast<s32>( sizeof( u32 ) ) )
        Logfile::getInstance().emergencyExit( BROKEN_STREAM );
    if ( stream->write( text.c_str(), count ) < static_cast<s32>( count ) )
        Logfile::getInstance().emergencyExit( BROKEN_STREAM );
}



template <typename T> void ObjectConfiguration::skip( io::IReadFile* stream )
{
    if ( !stream->seek( sizeof( T ), true ) )
        Logfile::getInstance().emergencyExit( UNKNOWN_FILE_FORMAT );
}
// explicit instantiations:
template void ObjectConfiguration::skip<u32>( io::IReadFile* stream );
