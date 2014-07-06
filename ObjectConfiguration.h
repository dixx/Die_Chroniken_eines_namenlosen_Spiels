/*! \file ObjectConfiguration.h
 *  \brief Informationen zur Erstellung eines 3D-Objektes.
 */

#ifndef _OBJECTCONFIGURATION_HEADER
#define _OBJECTCONFIGURATION_HEADER

#include <irrlicht.h>
#include "ObjectConfigurationContext.hpp"

using namespace irr;

/*! \class ObjectConfiguration ObjectConfiguration.h "ObjectConfiguration.h"
 *  \brief Informationen zur Erstellung eines 3D-Objektes.
 *  \note Instanzierung: `ObjectConfiguration* myObjectConfiguration = new ObjectConfiguration();`
 *  \n Benutzen: `myObjectConfiguration->node->name;`
 */
class ObjectConfiguration
{

public:

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

private:

    ObjectConfiguration( const ObjectConfiguration& );
    ObjectConfiguration& operator=( const ObjectConfiguration& );

};

#endif
