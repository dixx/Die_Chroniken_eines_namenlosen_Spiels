/*! \file Constants.h
 *  \brief Konstanten und Defines
 *
 *  Hier werden einige Konstanten und Defines definiert, die von verschiedenen Stellen aus genutzt werden, vor allem
 *  für Variablen-Instanzierungen.
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <irrlicht.h>

//! @name Einige vorgewählte geometrische Größen, vorwiegend zum Instanzieren
//! \attention Multiplikation mit Vektoren dauert länger als neu Erstellen!
//! @{

//! Nulldimension 2D Float
const irr::core::dimension2df DIM_2DF_NULL = irr::core::dimension2df( 0.0f, 0.0f );
//! Nulldimension 2D Signed Integer
const irr::core::dimension2di DIM_2DI_NULL = irr::core::dimension2di();
//! Nulldimension 2D Unsigned Integer
const irr::core::dimension2du DIM_2DU_NULL = irr::core::dimension2du();
//! Nullvector 2D Float
const irr::core::vector2df VEC_2DF_NULL = irr::core::vector2df( 0.0f );
//! Nullvector 2D Signed Integer
const irr::core::vector2di VEC_2DI_NULL = irr::core::vector2di( 0 );
//! Nullvector 3D Float
const irr::core::vector3df VEC_3DF_NULL = irr::core::vector3df( 0.0f );
//! Nullvector 3D Signed Integer
const irr::core::vector3di VEC_3DI_NULL = irr::core::vector3di( 0 );
//! @}



//! @name Einige vorgewählte Farben
//! @{

//! Magic Pink wird NUR für Transparenz genutzt
const irr::video::SColor COL_MAGICPINK = irr::video::SColor( 255, 250,   0, 250 );
const irr::video::SColor COL_WHITE     = irr::video::SColor( 255, 255, 255, 255 );
const irr::video::SColor COL_LIGHTGREY = irr::video::SColor( 255, 175, 175, 175 );
const irr::video::SColor COL_DARKGREY  = irr::video::SColor( 255, 100, 100, 100 );
const irr::video::SColor COL_BLACK     = irr::video::SColor( 255,   0,   0,   0 );
const irr::video::SColor COL_RED       = irr::video::SColor( 255, 255,   0,   0 );
const irr::video::SColor COL_ORANGE    = irr::video::SColor( 255, 255, 170,   0 );
const irr::video::SColor COL_YELLOW    = irr::video::SColor( 255, 255, 255,   0 );
const irr::video::SColor COL_GREEN     = irr::video::SColor( 255,   0, 255,   0 );
const irr::video::SColor COL_BLUE      = irr::video::SColor( 255,   0,   0, 255 );
const irr::video::SColor COL_PURPLE    = irr::video::SColor( 255,  80,  30,  90 );
//! @}


//! \todo management of collision relevant IDs should be done by collisionmanager, right?
//! @name IDs und Flags für Szenenknoten, wichig für Kollisionsabfrage
//! @{
#define  ID_NICHT_VERWENDEN         0x0
#define  ID_ERSTE_BENUTZBARE        0x1
//... benutzbar, 4194285 IDs
#define  ID_LETZTE_BENUTZBARE       0x3fffef
#define  ID_FREE_1                  0x3ffff0
#define  ID_MAUSPFEILREAKTIV        0x3ffff1
#define  ID_HINDERNIS               0x3ffff2
#define  ID_WELTDEKORATION          0x3ffff3
#define  ID_BODEN                   0x3ffff4
#define  ID_WETTER                  0x3ffff5
#define  ID_WELTBELEUCHTUNG         0x3ffff6
#define  ID_LEBEWESEN               0x3ffff7
#define  ID_HELD                    0x3ffff8
#define  ID_LEICHEN                 0x3ffff9
#define  ID_INVENTAR                0x3ffffa
#define  ID_GESCHOSSE               0x3ffffb
#define  ID_INTERAKTIV              0x3ffffc
#define  ID_BEGEHBAR                0x3ffffd
#define  ID_KAMERA                  0x3ffffe
#define  ID_WELT                    0x3fffff
#define  ID_FLAG_FREE_5             0x800000    //Flag (Bit 24), ungenutzt
#define  ID_FLAG_FREE_4             0x1000000   //Flag (Bit 25), ungenutzt
#define  ID_FLAG_FREE_3             0x2000000   //Flag (Bit 26), ungenutzt
#define  ID_FLAG_FREE_2             0x4000000   //Flag (Bit 27), ungenutzt
#define  ID_FLAG_FREE_1             0x8000000   //Flag (Bit 28), ungenutzt
#define  ID_FLAG_MAUSPFEILREAKTIV   0x10000000  //Flag (Bit 29)
#define  ID_FLAG_KOLLIDIERBAR       0x20000000  //Flag (Bit 30)
#define  ID_FLAG_BEGEHBAR           0x40000000  //Flag (Bit 31)
//! @}


#endif /* CONSTANTS_H_ */
