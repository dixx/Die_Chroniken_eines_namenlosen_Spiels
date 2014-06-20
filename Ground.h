/*! \file Ground.h
 *  \brief Klasse (Singleton) stellt Schnittstelle für den Fußboden bereit.
 */

#ifndef _GROUND_HEADER
#define _GROUND_HEADER

#include <irrlicht.h>
#include "MapTile.h"
#include "Timer.h"

using namespace irr;

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
    static Ground& getInstance( IrrlichtDevice* device = 0 );

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
    f32 getHeight( const f32 x, const f32 z );

    /*! \brief Komplettiert die übergebene Position mit der Höhe des Fußbodens an der gefragen Stelle und gibt die
     *         neue Position zurück.
     *  \param position (\a const \a core::vector3df&) Position
     *  \param heightOffset (\a f32) Y-Offset oberhalb von "Position"
     *  \return \a core::vector3df komplettierte Position
     */
    core::vector3df& getHeightFromPosition( const core::vector3df& position, f32 heightOffset = 0.0f );

    /*! \brief Gibt die Höhe des Fußbodens an der gefragen Stelle zurück.
     *  \attention Schneller als getHeight(), aber funktioniert nur innerhalb des Sichtradius des Helden!
     *  \param x (\a const \a f32) X-Koordinate, horizontale
     *  \param z (\a const \a f32) Z-Koordinate, Tiefe
     *  \return \a f32 Y-Koordinate, vertikal
     */
    f32 getHeightRanged( const f32 x, const f32 z );

    /*! \brief Komplettiert die übergebene Position mit der Höhe des Fußbodens an der gefragen Stelle und gibt die
     *         neue Position zurück.
     *  \attention Schneller als getHeightFromPosition(), aber funktioniert nur innerhalb des Sichtradius des Helden!
     *  \param position (\a const \a core::vector3df&) Position
     *  \param heightOffset (\a f32) Y-Offset oberhalb von "Position"
     *  \return \a core::vector3df komplettierte Position
     */
    core::vector3df& getHeightFromPositionRanged( const core::vector3df& position, f32 heightOffset = 0.0f );

#ifdef _DEBUG_MODE
    /*! \brief Schaltet verschiedene Debugmodi durch.
     *  \param -
     *  \return -
     */
    void switchDebugMode();
#endif

private:

    IrrlichtDevice* device_;
    scene::ISceneManager* smgr_;
    core::array<MapTile*> mapTiles_;
    core::dimension2df SECTORDIMENSION;
    u32 gridWidth_;
    u32 gridDepth_;
    core::line3df ray_;
    f32 minHeight_;
    f32 maxHeight_;
    Timer* updateTimer_;
    s32 updateSectorX_;
    s32 updateSectorZ_;
    core::vector3df endPosition_;
#ifdef _DEBUG_MODE
    u32 visibleNodeCount_;
    u32 debugCounter_;
#endif

    Ground( IrrlichtDevice* device );
    Ground( const Ground& );
    Ground& operator=( const Ground& );
    ~Ground();

    inline void clearArrays();
    void exitWithLogEntry( const core::stringc& message, const char* affectedFile );

};

#endif
