/*! \file Vegetation.h
 *  \brief Klasse stellt Schnittstelle für Vegetation bereit.
 */

#ifndef _VEGETATION_HEADER
#define _VEGETATION_HEADER

#include <irrlicht.h>
#include "BufferCullMeshSceneNode.h"

/*! \class Vegetation Vegetation.h "Vegetation.h"
 *  \brief Schnittstelle für Vegetation.
 *  \note Instanzierung: `Vegetation* myVegetation = new Vegetation();` \n Benutzen: `myVegetation->xxxx();`
 */
class Vegetation
{

public:

    /*! \brief Konstruktor.
     *  \param smgr (\a ISceneManager*) Zeiger auf en aktuellen Szenenmanager
     *  \return Zeiger auf das instanzierte Klassenobjekt
     */
    Vegetation( irr::scene::ISceneManager* smgr );

	/*! \brief Destruktor
     */
	~Vegetation();

    /*! \brief Erstellt die Vegetation für ein Level.
     *  \param -
     *  \return -
     */
    void create();

    /*! \brief Aktualisiert die Vegetation für ein Level, z.B. Bewegung oder Blütenstände.
     *  \param -
     *  \return -
     */
    void update();

private:

    irr::scene::ISceneManager* smgr_;
    irr::scene::IMeshManipulator* meshManipulator_;
    irr::scene::SMesh* grassMesh_;
    BufferCullMeshSceneNode* grassNode_;

    Vegetation( const Vegetation& );
    Vegetation& operator=( const Vegetation& );
};

#endif
