/*! \file MapTile.h
 *  \brief Ein Kartenteil.
 */

#ifndef _MAPTILE_HEADER
#define _MAPTILE_HEADER

#include <irrlicht.h>
#include "BasicStaticObject.h"

/*! \class MapTile MapTile.h "MapTile.h"
 *  \brief Ein Kartenteil.
 */
class MapTile : public BasicStaticObject
{

public:

    /*! \brief Konstruktor. Erstellt ein komplettes Objekt aus der textuellen Beschreibung des Kartenteils.
     *  \attention Ist die Beschreibung leer oder fehlerhaft, wird ein leeres Kartenteil generiert,
     *             dessen 3D-Knoten 0 ist.
     *  \param objectData (\a const \a core::stringc&) textuelle Beschreibung des Kartenteils
     *  \param smgr (\a scene::ISceneManager*) Zeiger auf den SceneManager
     *  \param sectorDimension (\a const \a core::dimension2df&) Ausdehnung eines Sektors (eines Kartenteils)
     *         in virtuellen Einheiten
     */
    MapTile( const irr::core::stringc& objectData, irr::scene::ISceneManager* smgr, const irr::core::dimension2df& sectorDimension );

    /*! \brief Destruktor.
     */
    ~MapTile();

    /*! \brief Liefert die X-Position des Kartenteils im Karten-Grid.
     *  \param -
     *  \return \a s32 X-Position
     */
    irr::s32 getX() const;

    /*! \brief Liefert die Z-Position des Kartenteils im Karten-Grid.
     *  \param -
     *  \return \a s32 Z-Position
     */
    irr::s32 getZ() const;

private:

    irr::s32 tileX_;
    irr::s32 tileZ_;
    irr::core::dimension2df sectorDimension_;

    MapTile( const MapTile& );
    void operator=( const MapTile& );

    void init();

};

#endif
