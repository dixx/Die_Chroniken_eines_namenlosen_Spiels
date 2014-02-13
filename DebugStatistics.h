/*! \file DebugStatistics.h
  \brief Klasse stellt Schnittstelle für Statistiken der benutzten Klassen
         bereit.
*/

#ifndef _DEBUGSTATISTICS_HEADER
#define _DEBUGSTATISTICS_HEADER

// Linken der IRRLICHT-DLL, nur in VisualStudio nötig
//#ifdef _IRR_WINDOWS_
//    #pragma comment(lib, "Irrlicht.lib")
//#endif

#include <irrlicht.h>

using namespace irr;
// Die innenliegenden Namespaces "core", "video" usw. werden im Folgenden
// immer explizit angegeben, um den Überblick zu behalten.

/*! \class DebugStatistics DebugStatistics.h "DebugStatistics.h"
  \brief Schnittstelle für Statistiken.
  \note Instanzierung: `DebugStatistics* myDebugStatistics
        = new DebugStatistics();`
		\n Benutzen: `myDebugStatistics->writeStatisticsToLogfile();`
  \attention Klasse löscht sich selbst via drop().
*/
class DebugStatistics
{

public:

    /*! \brief Konstruktor.
      \param device (\a IrrlichtDevice*) Zeiger auf das Entchen
      \return Zeiger auf das instanzierte Klassenobjekt
    */
    DebugStatistics( IrrlichtDevice* device );

    /*! \brief Schreibt Informationen über alle möglichen Objekte, Zustände,
               Listen usw. in das aktuelle Logfile.
      \note Objekt gibt sich selbst zurück, damit drop() direkt danach
            aufgerufen werden kann.
      \param -
      \return Zeiger auf das instanzierte Klassenobjekt
    */
    DebugStatistics* writeStatisticsToLogfile();

    /*! \brief Löscht die Instanz.
      \param -
      \return -
    */
    void drop();

private:

    IrrlichtDevice* device_;

    ~DebugStatistics();
    DebugStatistics( const DebugStatistics& );
    DebugStatistics& operator=( const DebugStatistics& );

};
// Ende class DebugStatistics

#endif
// Ende Header-Datei DebugStatistics
