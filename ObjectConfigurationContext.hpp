/*! \file ObjectConfigurationContext.h
 *  \brief Untergruppen für ein Konfigurationsobjekt.
 */

#ifndef _OBJECTCONFIGURATIONCONTEXT_HEADER
#define _OBJECTCONFIGURATIONCONTEXT_HEADER

#include <irrlicht.h>
#include "Constants.h"

using namespace irr;

/*! \class ObjectConfigurationContextForObject ObjectConfigurationContextForObject.h "ObjectConfigurationContextForObject.h"
 *  \brief High-Level-Informationen über das zu erstellende 3D-Object.
 */
class ObjectConfigurationContextForObject
{

public:

    enum ObjectType {
        DEKORATION,
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

/*! \class ObjectConfigurationContextForNode ObjectConfigurationContextForNode.h "ObjectConfigurationContextForNode.h"
 *  \brief Informationen über den zu erstellenden Szenenknoten.
 */
class ObjectConfigurationContextForNode
{

public:

    core::stringc name;

    ObjectConfigurationContextForNode() : name("<noname>") {}

};

/*! \class ObjectConfigurationContextForMesh ObjectConfigurationContextForMesh.h "ObjectConfigurationContextForMesh.h"
 *  \brief Informationen über das zu erstellende Mesh.
 */
class ObjectConfigurationContextForMesh
{

public:

    core::vector3df position, offset, scale, rotation;

    ObjectConfigurationContextForMesh()
    : position(VEC_3DF_NULL), offset(VEC_3DF_NULL), scale(core::vector3df( 1.0f )), rotation(VEC_3DF_NULL)
    {}

};

/*! \class ObjectConfigurationContextForMaterials ObjectConfigurationContextForMaterials.h "ObjectConfigurationContextForMaterials.h"
 *  \brief Informationen über die Materialien des zu erstellenden 3D-Objects.
 */
class ObjectConfigurationContextForMaterials
{

public:

    core::array<bool> isTransparent, isBackFaceCulled;

    ObjectConfigurationContextForMaterials() {
        isTransparent.clear();
        isBackFaceCulled.clear();
    }

};

/*! \class ObjectConfigurationContextForFiles ObjectConfigurationContextForFiles.h "ObjectConfigurationContextForFiles.h"
 *  \brief Dateipfade des 3D-Objects.
 */
class ObjectConfigurationContextForFiles
{

public:

    io::path mesh;

    ObjectConfigurationContextForFiles() : mesh("") {}

};

#endif
