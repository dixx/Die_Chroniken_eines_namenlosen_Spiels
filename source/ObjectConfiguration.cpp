#include "ObjectConfiguration.h"
#include "Logfile.h"

// these defines are for better readability only
#define UNKNOWN_FILE_FORMAT "Unbekanntes Dateiformat! Abbruch."
#define BROKEN_STREAM "Schreiben in Datei fehlgeschlagen! Abbruch."



ObjectConfiguration::ObjectConfiguration()
: CURRENT_VERSION(0),
  object(0),
  node(0),
  mesh(0),
  materials(0),
  files(0)
{
    object = new ObjectConfigurationContextForObject;
    node = new ObjectConfigurationContextForNode;
    mesh = new ObjectConfigurationContextForMesh;
    materials = new ObjectConfigurationContextForMaterials;
    files = new ObjectConfigurationContextForFiles;
}



void ObjectConfiguration::readFrom( irr::io::IReadFile* stream, irr::u32 version )
{
    // we now read a certain amount of entities from the stream, in a specific order
    if ( version == 0 )
    {
        object->type = static_cast<ObjectConfigurationContextForObject::ObjectType>( read<irr::u8>( stream ) );
        node->name = readString( stream );
        mesh->position = read<irr::core::vector3df>( stream );
        mesh->offset = read<irr::core::vector3df>( stream );
        mesh->scale = read<irr::core::vector3df>( stream );
        mesh->rotation = read<irr::core::vector3df>( stream );
        mesh->materialCount = read<irr::u32>( stream );
        for ( irr::u32 i = 0; i < mesh->materialCount; ++i )
        {
            materials->isTransparent.push_back( read<bool>( stream ) );
            materials->isBackFaceCulled.push_back( read<bool>( stream ) );
            materials->isLighted.push_back( read<bool>( stream ) );
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
        irr::core::stringc errorMessage = "Dateiversion ";
        errorMessage += version;
        errorMessage += " unbekannt! Abbruch." ;
        Logfile::getInstance().emergencyExit( errorMessage );
    }
}



void ObjectConfiguration::writeTo( irr::io::IWriteFile* stream )
{
    write<irr::u8>( stream, object->type );
    writeString( stream, node->name );
    write<irr::core::vector3df>( stream, mesh->position );
    write<irr::core::vector3df>( stream, mesh->offset );
    write<irr::core::vector3df>( stream, mesh->scale );
    write<irr::core::vector3df>( stream, mesh->rotation );
    write<irr::u32>( stream, mesh->materialCount );
    for ( irr::u32 i = 0; i < mesh->materialCount; ++i )
    {
        write<bool>( stream, materials->isTransparent[ i ] );
        write<bool>( stream, materials->isBackFaceCulled[ i ] );
        write<bool>( stream, materials->isLighted[ i ] );
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
template <typename T> T ObjectConfiguration::read( irr::io::IReadFile* stream )
{
    T buffer;
    irr::u32 bytes = sizeof( T );//typeof( buffer ) );
    if ( stream->read( &buffer, bytes ) < static_cast<irr::s32>( bytes ) )
        Logfile::getInstance().emergencyExit( UNKNOWN_FILE_FORMAT );
    return buffer;
}



irr::core::stringc ObjectConfiguration::readString( irr::io::IReadFile* stream )
{
    irr::u32 count = read<irr::u32>( stream );
    irr::u8* buffer = new irr::u8[count];
    if ( stream->read( buffer, count ) < static_cast<irr::s32>( count ) )
        Logfile::getInstance().emergencyExit( UNKNOWN_FILE_FORMAT );
    irr::core::stringc ret = irr::core::stringc( buffer );
    delete[] buffer;
    return ret;
}



template <typename T> void ObjectConfiguration::write( irr::io::IWriteFile* stream, const T& number )
{
    if ( stream->write( &number, sizeof( T ) ) < static_cast<irr::s32>( sizeof( T ) ) )
        Logfile::getInstance().emergencyExit( BROKEN_STREAM );
}
// explicit instantiations:
template void ObjectConfiguration::write<bool>( irr::io::IWriteFile* stream, const bool& number );
template void ObjectConfiguration::write<irr::u8>( irr::io::IWriteFile* stream, const irr::u8& number );
template void ObjectConfiguration::write<irr::u32>( irr::io::IWriteFile* stream, const irr::u32& number );
template void ObjectConfiguration::write<irr::core::vector3df>( irr::io::IWriteFile* stream, const irr::core::vector3df& number );



void ObjectConfiguration::writeString( irr::io::IWriteFile* stream, const irr::core::stringc& text )
{
    irr::u32 count = text.size() + 1; // + 1 == trailing \0
    if ( stream->write( &count, sizeof( irr::u32 ) ) < static_cast<irr::s32>( sizeof( irr::u32 ) ) )
        Logfile::getInstance().emergencyExit( BROKEN_STREAM );
    if ( stream->write( text.c_str(), count ) < static_cast<irr::s32>( count ) )
        Logfile::getInstance().emergencyExit( BROKEN_STREAM );
}



template <typename T> void ObjectConfiguration::skip( irr::io::IReadFile* stream )
{
    if ( !stream->seek( sizeof( T ), true ) )
        Logfile::getInstance().emergencyExit( UNKNOWN_FILE_FORMAT );
}
// explicit instantiations:
template void ObjectConfiguration::skip<irr::u32>( irr::io::IReadFile* stream );
