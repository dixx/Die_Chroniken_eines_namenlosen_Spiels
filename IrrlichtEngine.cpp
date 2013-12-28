#include "IrrlichtEngine.h"



IrrlichtEngine& IrrlichtEngine::getInstance()
{
    static IrrlichtEngine _instance;
    return _instance;
}



/* private */



IrrlichtEngine::IrrlichtEngine()
: device(0)
{
}



IrrlichtEngine::~IrrlichtEngine()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
}
