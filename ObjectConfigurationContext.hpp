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

    /*! \brief Mögliche Typen eines Objektes, welche dessen internes Kollisions-Verhalten bestimmen.
     */
    enum ObjectType {
        DEKORATION = 0, //!< Objekt ist durchlässig für alles und reagiert auf nichts
        WETTER, //!< Ähnlich wie DEKORATION, wird aber anders aktualisiert
        INTERAKTIV, //!< Objekt ist nicht begehbar, aber klickbar und kollidierbar
        INVENTAR, //!< Wie INTERAKTIV, wird aber anders aktualisiert
        LEBEWESEN, //!< Wie INTERAKTIV, hat aber spezielle Kollisionserkennung für Lebewesen
        HINDERNIS, //!< Objekt ist nicht begehbar und nicht klickbar, aber kollidierbar
        MAUSPFEILREAKTIV, //!< Objekt ist nicht begehbar und nicht kollidierbar, aber klickbar
        LEICHE, //!< Wie MAUSPFEILREAKTIV, wird aber gesondert aktualisiert
        BEGEHBAR, //!< Objekt ist nicht kollidierbar, aber begehbar und klickbar
        GESCHOSS //!< Objekt hat spezielle Kollisionserkennung für Geschosse und ist weder klickbar noch begehbar
    }; // TODO auslagern nach Constants.h und ersetzen aller Vorkommen von `core::stringc type`

    ObjectType type; //!< Der Kollisions-Typ des Objektes

    ObjectConfigurationContextForObject() : type(DEKORATION) {}

};

/*! \class ObjectConfigurationContextForNode
 *  \brief Informationen über den zu erstellenden Szenenknoten.
 */
class ObjectConfigurationContextForNode
{

public:

    core::stringc name; //!< Der Name des Objektes

    ObjectConfigurationContextForNode() : name("<noname>") {}

};

/*! \class ObjectConfigurationContextForMesh
 *  \brief Informationen über das zu erstellende Mesh.
 */
class ObjectConfigurationContextForMesh
{

public:

    core::vector3df position; //!< Absolute Position in der Welt
    core::vector3df offset; //!< Objekt-interne Nullpunktverschiebung
    core::vector3df scale; //!< Vergrößerungsfaktor des Objektes
    core::vector3df rotation; //!< Ausrichtung des Objektes in der Welt
    u32 materialCount; //!< Anzahl der Materialien eines Objektes

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

    core::array<bool> isTransparent; //!< Ist das MATERIAL transparent?
    core::array<bool> isBackFaceCulled; //!< Sollen die Rückseiten aller Flächen des MATERIALS ausgeblendet werden?
    core::array<bool> isLighted; //!< Reagiert das MATERIAL auf Licht?

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

    io::path mesh; //!< Pfad zur Mesh-Datei
    core::array<io::path> mainTexture; //!< Pfade zu den Haupttexturen der MATERIALIEN
    core::array<io::path> secondTexture; //!< Pfade zu den Nebentexturen der MATERIALIEN

    ObjectConfigurationContextForFiles() : mesh("")
    {
        mainTexture.clear();
        secondTexture.clear();
    }

};

#endif
