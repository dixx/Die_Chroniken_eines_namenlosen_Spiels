/*! \file Vegetation.h
  \brief Klasse stellt Schnittstelle für Vegetation bereit.
*/

#ifndef _VEGETATION_HEADER
#define _VEGETATION_HEADER

// Linken der IRRLICHT-DLL, nur in VisualStudio nötig
//#ifdef _IRR_WINDOWS_
//    #pragma comment(lib, "Irrlicht.lib")
//#endif

#include <irrlicht.h>

using namespace irr;
// Die innenliegenden Namespaces "core", "video" usw. werden im Folgenden
// immer explizit angegeben, um den Überblick zu behalten.

/*! \class Vegetation Vegetation.h "Vegetation.h"
  \brief Schnittstelle für Vegetation.
  \note Instanzierung: `Vegetation* myVegetation = new Vegetation();`
		\n Benutzen: `myVegetation->xxxx();`
*/
class Vegetation
{

public:

	// Variablen

    /*! \brief Konstruktor.
      \param -
      \return Zeiger auf das instanzierte Klassenobjekt
    */
    Vegetation();

	/*! \brief Destruktor
    */
	~Vegetation();

    /*! \brief Erstellt die Vegetation für ein Level.
      \param -
      \return -
    */
    void create();

    /*! \brief Aktualisiert die Vegetation für ein Level, z.B. Bewegung oder
               Blütenstände.
      \param -
      \return -
    */
    void update();

private:

    scene::SMesh* grass_;

    Vegetation( const Vegetation& );
    Vegetation& operator=( const Vegetation& );
};
// Ende class Vegetation

#endif
// Ende Header-Datei Vegetation
