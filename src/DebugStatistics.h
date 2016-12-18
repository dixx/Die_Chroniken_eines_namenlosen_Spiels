/*! \file DebugStatistics.h
 *  \brief Klasse stellt Schnittstelle für Statistiken der benutzten Klassen bereit.
 */

#ifndef _DEBUGSTATISTICS_HEADER
#define _DEBUGSTATISTICS_HEADER

#include <irrlicht.h>

/*! \class DebugStatistics DebugStatistics.h "DebugStatistics.h"
 *  \brief Schnittstelle für Statistiken.
 *  \note Instanzierung: `DebugStatistics* myDebugStatistics = new DebugStatistics();`
 * 		\n Benutzen: `myDebugStatistics->writeStatisticsToLogfile();`
 *  \attention Klasse löscht sich selbst via drop().
 */
class DebugStatistics
{

public:

    /*! \brief Konstruktor.
     *  \param device (\a IrrlichtDevice*) Zeiger auf das Entchen
     *  \return Zeiger auf das instanzierte Klassenobjekt
     */
    DebugStatistics( irr::IrrlichtDevice* device );

    /*! \brief Schreibt Informationen über alle möglichen Objekte, Zustände, Listen usw. in das aktuelle Logfile.
     */
    void writeStatisticsToLogfile();

private:

    irr::IrrlichtDevice* device_;

};

#endif
