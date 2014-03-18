/*! \file HeroPunk.h
  \brief Klasse stellt die Charakterklasse Punk bereit.
*/

#ifndef _HEROPUNK_HEADER
#define _HEROPUNK_HEADER

// Linken der IRRLICHT-DLL, nur in VisualStudio nötig
//#ifdef _IRR_WINDOWS_
//    #pragma comment(lib, "Irrlicht.lib")
//#endif

#include <irrlicht.h>
#include "BasicHero.h"

using namespace irr;
// Die innenliegenden Namespaces "core", "video" usw. werden im Folgenden
// immer explizit angegeben, um den Überblick zu behalten.

/*! \class HeroPunk HeroPunk.h "HeroPunk.h"
  \brief Der Punk.
  \note Instanzierung: `HeroPunk* myHeroPunk = new HeroPunk();`
		\n Benutzen: `myHeroPunk->xxxx();`
*/
class HeroPunk : public BasicHero
{

public:

    /*! \brief Konstruktor. Erstellt einen Punk.
      \param punkData (\a const \a core::stringc&) textuelle Beschreibung des
             Punk
      \param smgr (\a scene::ISceneManager*) Zeiger auf den SceneManager
      \return Zeiger auf das instanzierte Klassenobjekt
    */
    HeroPunk( const core::stringc& punkData, scene::ISceneManager* smgr );

	/*! \brief Destruktor
    */
	~HeroPunk();

    /*! \brief Liefert den aktuellen objectData-String des Punk.
      \param -
      \return \a core::stringc objectData des Punk
    */
    core::stringc getObjectData();


private:

    HeroPunk( const HeroPunk& );
    HeroPunk& operator=( const HeroPunk& );

    inline void init();

};
// Ende class HeroPunk

#endif
// Ende Header-Datei HeroPunk
