/*! \file ObjectConfiguration.h
 *  \brief Informationen zur Erstellung eines 3D-Objektes.
 */

#ifndef _OBJECTCONFIGURATION_HEADER
#define _OBJECTCONFIGURATION_HEADER

#include <irrlicht.h>
#include "ObjectConfigurationContext.hpp"

using namespace irr;

/*! \class ObjectConfiguration ObjectConfiguration.h "ObjectConfiguration.h"
 *  \brief Informationen zur Erstellung eines 3D-Objektes.
 *  \note Instanzierung: `ObjectConfiguration* myObjectConfiguration = new ObjectConfiguration();`
 *  \n Benutzen: `myObjectConfiguration->node->name;`
 */
class ObjectConfiguration
{

public:

    const u8 CURRENT_VERSION;

    ObjectConfigurationContextForObject* object;
    ObjectConfigurationContextForNode* node;
    ObjectConfigurationContextForMesh* mesh;
    ObjectConfigurationContextForMaterials* materials;
    ObjectConfigurationContextForFiles* files;

    /*! \brief Konstruktor.
     *  \param -
     *  \return Zeiger auf das instanzierte Klassenobjekt
     */
    ObjectConfiguration();

    /*! \brief Destruktor
     */
    ~ObjectConfiguration();

    /*! \brief Erstellt ein Konfigurationsobjekt mittels eines (versionsabhängigen) Datei-Streams.
     *  \param stream (\a io::IReadFile*) Zeiger auf den offenen Datei-Stream
     *  \param version (\a u32) Version der Datei
     *  \return -
     */
    void readFrom( io::IReadFile* stream, u32 version );

    /*! \brief Schreibt ein Konfigurationsobjekt neuester Version auf einen Datei-Stream.
     *  \param stream (\a io::IWriteFile*) Zeiger auf den offenen Datei-Stream
     *  \return -
     */
    void writeTo( io::IWriteFile* stream );

private:

    ObjectConfiguration( const ObjectConfiguration& );
    ObjectConfiguration& operator=( const ObjectConfiguration& );

    template <typename T> inline T read( io::IReadFile* stream );
    core::stringc readString( io::IReadFile* stream );
    template <typename T> inline void write( io::IWriteFile* stream, const T& number );
    void writeString( io::IWriteFile* stream, const core::stringc& text );
    template <typename T> inline void skip( io::IReadFile* stream );
};

#endif
