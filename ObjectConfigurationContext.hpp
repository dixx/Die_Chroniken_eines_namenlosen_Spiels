/*! \file ObjectConfigurationContext.hpp
 *  \brief Untergruppen für ein Konfigurationsobjekt.
 */

#ifndef _OBJECTCONFIGURATIONCONTEXT_HEADER
#define _OBJECTCONFIGURATIONCONTEXT_HEADER

#include <irrlicht.h>
#include "Constants.h"

using namespace irr;

/*! \class ObjectConfigurationContextForObject
 *  \brief High-Level-Informationen über das zu erstellende 3D-Object.
 */
class ObjectConfigurationContextForObject
{

public:

    enum ObjectType {
        DEKORATION = 0,
        GESCHOSS,
        WETTER,
        HINDERNIS,
        INTERAKTIV,
        INVENTAR,
        LEBEWESEN,
        LEICHE,
        BEGEHBAR,
        MAUSPFEILREAKTIV
    }; // TODO auslagern nach Constants.h und ersetzen aller Vorkommen von `core::stringc type`

    ObjectType type;

    ObjectConfigurationContextForObject() : type(DEKORATION) {}

};

/*! \class ObjectConfigurationContextForNode
 *  \brief Informationen über den zu erstellenden Szenenknoten.
 */
class ObjectConfigurationContextForNode
{

public:

    core::stringc name;

    ObjectConfigurationContextForNode() : name("<noname>") {}

};

/*! \class ObjectConfigurationContextForMesh
 *  \brief Informationen über das zu erstellende Mesh.
 */
class ObjectConfigurationContextForMesh
{

public:

    core::vector3df position, offset, scale, rotation;
    u32 materialCount;

    ObjectConfigurationContextForMesh()
    : position(VEC_3DF_NULL),
      offset(VEC_3DF_NULL),
      scale(core::vector3df( 1.0f )),
      rotation(VEC_3DF_NULL),
      materialCount(0)
    {}

};

/*! \class ObjectConfigurationContextForMaterials
 *  \brief Informationen über die Materialien des zu erstellenden 3D-Objects.
 */
class ObjectConfigurationContextForMaterials
{

public:

    core::array<bool> isTransparent, isBackFaceCulled, isLighted;

    ObjectConfigurationContextForMaterials()
    {
        isTransparent.clear();
        isBackFaceCulled.clear();
    }

};

/*! \class ObjectConfigurationContextForFiles
 *  \brief Dateipfade des 3D-Objects.
 */
class ObjectConfigurationContextForFiles
{

public:

    io::path mesh;
    core::array<io::path> mainTexture, secondTexture;

    ObjectConfigurationContextForFiles() : mesh("")
    {
        mainTexture.clear();
        secondTexture.clear();
    }

};

#endif
