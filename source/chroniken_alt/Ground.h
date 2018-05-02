/*! \file Ground.h
 *  \brief Klasse (Singleton) stellt Schnittstelle für den Fußboden bereit.
 */

#ifndef _GROUND_HEADER
#define _GROUND_HEADER

#include <irrlicht.h>
#include "MapTile.h"
#include "leviathan.h"

/*! \class Ground Ground.h "Ground.h"
 *  \brief  Schnittstelle zum Fußboden der Spielewelt.
 *  \attention Klasse ist `Singleton`.
 *  \note Instanzierung: `Ground& myGround = Ground::getInstance();` \n Oder: `Ground::getInstance();`
 *        \n Benutzen: `myGround.load();` \n Oder: `Ground::getInstance().unload();`
 */
class Ground
{

public:

    /*! \brief Ersatz für den Konstruktor.
     *
     *  Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
     *  \param device (\a IrrlichtDevice*) Zeiger auf das Entchen
     *  \return Referenz auf die einzige Instanz dieser Klasse
     */
    static Ground& getInstance( irr::IrrlichtDevice* device = 0 );

    /*! \brief Lädt einen Spielewelt-Fußboden.
     *  \param mapfilename (\a const \a char*) Dateiname der Spielewelt-Karte
     *  \return -
     */
    void load( const char* mapfilename );

    /*! \brief Entlädt den geladenen Spielewelt-Fußboden.
     *  \param -
     *  \return -
     */
    void unload();

    /*! \brief Macht Spielewelt-Fußboden-Teile sichtbar oder unsichtbar.
     *  \param -
     *  \return -
     */
    void update();

    /*! \brief Gibt die Höhe des Fußbodens an der gefragen Stelle zurück.
     *  \param x (\a const\a f32) X-Koordinate, horizontale
     *  \param z (\a const\a f32) Z-Koordinate, Tiefe
     *  \return \a f32 Y-Koordinate, vertikal
     */
    irr::f32 getHeight( const irr::f32 x, const irr::f32 z );

    /*! \brief Komplettiert die übergebene Position mit der Höhe des Fußbodens an der gefragen Stelle und gibt die
     *         neue Position zurück.
     *  \param position (\a const \a core::vector3df&) Position
     *  \param heightOffset (\a f32) Y-Offset oberhalb von "Position"
     *  \return \a core::vector3df komplettierte Position
     */
    irr::core::vector3df& getHeightFromPosition( const irr::core::vector3df& position, irr::f32 heightOffset = 0.0f );

    /*! \brief Gibt die Höhe des Fußbodens an der gefragen Stelle zurück.
     *  \attention Schneller als getHeight(), aber funktioniert nur innerhalb des Sichtradius des Helden!
     *  \param x (\a const \a f32) X-Koordinate, horizontale
     *  \param z (\a const \a f32) Z-Koordinate, Tiefe
     *  \return \a f32 Y-Koordinate, vertikal
     */
    irr::f32 getHeightRanged( const irr::f32 x, const irr::f32 z );

    /*! \brief Komplettiert die übergebene Position mit der Höhe des Fußbodens an der gefragen Stelle und gibt die
     *         neue Position zurück.
     *  \attention Schneller als getHeightFromPosition(), aber funktioniert nur innerhalb des Sichtradius des Helden!
     *  \param position (\a const \a core::vector3df&) Position
     *  \param heightOffset (\a f32) Y-Offset oberhalb von "Position"
     *  \return \a core::vector3df komplettierte Position
     */
    irr::core::vector3df& getHeightFromPositionRanged( const irr::core::vector3df& position, irr::f32 heightOffset = 0.0f );

#ifdef _DEBUG_MODE
    /*! \brief Schaltet verschiedene Debugmodi durch.
     *  \param -
     *  \return -
     */
    void switchDebugMode();
#endif

private:

    irr::IrrlichtDevice* device_;
    irr::scene::ISceneManager* smgr_;
    irr::core::array<MapTile*> mapTiles_;
    irr::core::dimension2df SECTORDIMENSION;
    irr::u32 gridWidth_;
    irr::u32 gridDepth_;
    irr::core::line3df ray_;
    irr::f32 minHeight_;
    irr::f32 maxHeight_;
    leviathan::core::Timer* updateTimer_;
    irr::s32 updateSectorX_;
    irr::s32 updateSectorZ_;
    irr::core::vector3df endPosition_;
#ifdef _DEBUG_MODE
    irr::u32 visibleNodeCount_;
    irr::u32 debugCounter_;
#endif

    Ground( irr::IrrlichtDevice* device );
    Ground( const Ground& );
    Ground& operator=( const Ground& );
    ~Ground();

    inline void clearArrays();
    void exitWithLogEntry( const irr::core::stringc& message, const char* affectedFile );

};

#endif
