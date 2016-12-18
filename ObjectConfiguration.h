/*! \file ObjectConfiguration.h
 *  \brief Informationen zur Erstellung eines 3D-Objektes.
 */

#ifndef _OBJECTCONFIGURATION_HEADER
#define _OBJECTCONFIGURATION_HEADER

#include <irrlicht.h>
#include "ObjectConfigurationContext.hpp"

/*! \class ObjectConfiguration ObjectConfiguration.h "ObjectConfiguration.h"
 *  \brief Informationen zur Erstellung eines 3D-Objektes.
 *  \note Instanzierung: `ObjectConfiguration* myObjectConfiguration = new ObjectConfiguration();`
 *  \n Benutzen: `myObjectConfiguration->node->name;`
 */
class ObjectConfiguration
{

public:

    const irr::u8 CURRENT_VERSION;

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
    void readFrom( irr::io::IReadFile* stream, irr::u32 version );

    /*! \brief Schreibt ein Konfigurationsobjekt neuester Version auf einen Datei-Stream.
     *  \param stream (\a io::IWriteFile*) Zeiger auf den offenen Datei-Stream
     *  \return -
     */
    void writeTo( irr::io::IWriteFile* stream );

private:

    ObjectConfiguration( const ObjectConfiguration& );
    ObjectConfiguration& operator=( const ObjectConfiguration& );

    template <typename T> inline T read( irr::io::IReadFile* stream );
    irr::core::stringc readString( irr::io::IReadFile* stream );
    template <typename T> inline void write( irr::io::IWriteFile* stream, const T& number );
    void writeString( irr::io::IWriteFile* stream, const irr::core::stringc& text );
    template <typename T> inline void skip( irr::io::IReadFile* stream );
};

#endif
