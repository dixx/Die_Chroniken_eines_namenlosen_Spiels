#include "ObjectConfiguration.h"



ObjectConfiguration::ObjectConfiguration()
{
    object = new ObjectConfigurationContextForObject;
    node = new ObjectConfigurationContextForNode;
    mesh = new ObjectConfigurationContextForMesh;
    materials = new ObjectConfigurationContextForMaterials;
    files = new ObjectConfigurationContextForFiles;
}



ObjectConfiguration::~ObjectConfiguration()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    delete files;
    delete materials;
    delete mesh;
    delete node;
    delete object;
}
