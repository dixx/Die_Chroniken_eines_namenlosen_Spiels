/*! \file IrrlichtEngine.h

  Klasse (Singleton) stellt Schnittstelle für die Irrlicht-3D-Engine bereit.
*/

#ifndef _IRRLICHTENGINE_HEADER
#define _IRRLICHTENGINE_HEADER

#include <irrlicht.h>

using namespace irr;

/*! \class IrrlichtEngine IrrlichtEngine.h "IrrlichtEngine.h"

  Schnittstelle zur Irrlicht-3D-Engine. Diese bietet Zugriff auf den
  Grafiktreiber, das Dateisystem und vieles mehr. Im ganzen Spiel werden nur
  Irrlicht-interne Datentypen verwendet, das gewährleistet
  Betriebssystemunabhängigkeit.
  \attention Klasse ist \c Singleton.
  \note Instanzierung: <c>IrrlichtEngine& myIrrlichtEngine =
        IrrlichtEngine::getInstance();</c>
        \n Oder:     <c>IrrlichtEngine::getInstance();</c>
        \n Benutzen: <c>myIrrlichtEngine.filesystem;</c>
        \n Oder:     <c>IrrlichtEngine::getInstance().scenemanager</c>
*/
class IrrlichtEngine
{

public:

    IrrlichtEngine* device;

    /*! Ersatz für den Konstruktor.

      Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
      \param -
      \return Referenz auf die einzige Instanz dieser Klasse
    */
    static IrrlichtEngine& getInstance();

private:

    IrrlichtEngine();
    IrrlichtEngine( const IrrlichtEngine& );
    IrrlichtEngine& operator=( const IrrlichtEngine& );
    ~IrrlichtEngine();

};

#endif
