/*! \file GenericHelperMethods.h
 * \brief Klasse (Singleton) stellt Schnittstelle für allgemeine Hilfsmethoden bereit.
 */

#ifndef _GENERICHELPERMETHODS_HEADER
#define _GENERICHELPERMETHODS_HEADER

#include <irrlicht.h>

using namespace irr;

/*! \class GenericHelperMethods GenericHelperMethods.h "GenericHelperMethods.h"
 *  \brief  Schnittstelle für allgemeine Hilfsmethoden.
 *  \attention Klasse ist `Singleton`.
 *  \note Instanzierung: `GenericHelperMethods& myGenericHelperMethods = GenericHelperMethods::getInstance();`
 *        \n Oder: `GenericHelperMethods::getInstance();`
 *        \n Benutzen: `myGenericHelperMethods.validateFileExistence(...);`
 *        \n Oder: `GenericHelperMethods::getInstance().pushMeshToVRAM(...);`
 */
class GenericHelperMethods
{

public:

    /*! \brief Ersatz für den Konstruktor.
     *
     *  Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
     *  \param device (\a IrrlichtDevice*) Zeiger auf das Entchen
     *  \return Referenz auf die einzige Instanz dieser Klasse
     */
    static GenericHelperMethods& getInstance( IrrlichtDevice* device = 0 );

    /*! \brief Prüft ob die angegebene Datei vorhanden ist und beendet das Programm wenn nicht.
     *  \param filename (\a core::string<fschar_t>&) Dateiname
     *  \return -
     */
    void validateFileExistence( const core::string<fschar_t>& filename ) const;

    /*! \brief Schreibt alle Vertices direkt in den Grafikkartenspeicher.
     *  \param mesh (\a scene::IMesh*) Mesh
     *  \return -
     */
    void pushMeshToVRAM( scene::IMesh* mesh );

private:

    io::IFileSystem* fs_;
    u32 bufferCount_;
    scene::IMeshBuffer* buffer_;

    GenericHelperMethods( IrrlichtDevice* device );
    GenericHelperMethods( const GenericHelperMethods& );
    GenericHelperMethods& operator=( const GenericHelperMethods& );
    ~GenericHelperMethods();

};

#endif
