/*! \file Zufall.h
  \brief Klasse (Singleton) mit verschiedenen Methoden für Zufallsberechnung.
*/

#ifndef _ZUFALL_HEADER
#define _ZUFALL_HEADER

// Linken der IRRLICHT-DLL, nur in VisualStudio nötig
//#ifdef _IRR_WINDOWS_
//    #pragma comment(lib, "Irrlicht.lib")
//#endif

#include <irrlicht.h>

using namespace irr;
// Die innenliegenden Namespaces "core", "video" usw. werden im Folgenden
// immer explizit angegeben, um den Überblick zu behalten.

/*! \class Zufall Zufall.h "Zufall.h"
  \brief Enthält Funktionen zum Erzeugen von Zufallszahlen.
  \attention Klasse ist `Singleton`.
  \note Instanzierung: `Zufall& myZufall = Zufall::getInstance();`
        \n Oder: `Zufall::getInstance();`
        \n Benutzen: `myZufall.Start( (u32)time( NULL ) );`
        \n Oder: `Zufall::getInstance().rnd_int();`
*/
class Zufall
{

public:

    /*! \brief Ersatz für den Konstruktor.

      Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
      \return Referenz auf die einzige Instanz dieser Klasse
    */
    static Zufall& getInstance();

    /*! \brief Initialisiert den Zufallsgenerator.
      \attention Muss vor dem Benutzen der anderen Methoden aufgerufen werden,
                 sonst werden bei jedem Programmstart dieselben Werte errechnet
                 wie vorher!\n Möglicher Aufruf:
                 `Zufall::getInstance().start( (u32)time( NULL ) );`
      \param seed (\a u32) Startwert
      \return -
    */
    void start( const u32 seed );

    /*! \brief Berechnet eine \a float Zufallszahl zwischen \b 0.0 und
             \b 0.9periode... (inklusive).
      \param -
      \return \a f32 Zufallszahl
    */
    f32 getFloat();

    /*! \brief Berechnet eine \a int Zufallszahl zwischen \b 0 und
               \b 4294967295 (inklusive).
      \note Berechnung basiert auf XORSHIFT mit 4 Seeds
      \param -
      \return \a u32 Zufallszahl
    */
    u32 getInt();

    /*! \brief Berechnet eine \a int Zufallszahl zwischen \b min und
             \b max (inklusive).
      \note Vertauscht automatisch \b min und \b max, wenn \b min
            grösser ist als \b max.
      \attention Maximalwert darf U32_MAX-1 nicht überschreiten!
      \param min (\a u32) unterer Grenzwert
      \param max (\a u32) oberer Grenzwert
      \return \a int Zufallszahl
    */
    u32 getIntBetween( const u32 min, const u32 max );

    /*! \brief Berechnet eine \a float Zufallszahl zwischen \b min und
             \b max (inklusive).
      \note Vertauscht automatisch \b min und \b max, wenn \b min
            grösser ist als \b max.
      \param min (\a f32) unterer Grenzwert
      \param max (\a f32) oberer Grenzwert
      \return \a f32 Zufallszahl
    */
    f32 getFloatBetween( const f32 min, const f32 max );

    /*! \brief Berechnet anhand einer Wahrscheinlichkeit \b p,
             ob ein Ereignis eintritt.
      \note \b p wird automatisch auf Werte innerhalb [0..100] begrenzt.
      \param p (\a f32) Prozentuale Wahrscheinlichkeit für ein Ereignis
      \return `true` (Ereignis tritt ein) oder `false`
    */
    bool doesOccur( const f32 p );

    /*! \brief Berechnet anhand des Verhältnisses von \b A zu \b B,
             ob Ereignis \b A eintritt.
      \param A (\a f32) Verhältniswert für Ereignis \b A
      \param B (\a f32) Verhältniswert für Ereignis \b B
      \return `true` wenn Ereignis \b A eintritt, ansonsten `false`
    */
    bool doesAoccur( const f32 A, const f32 B );

    /*! \brief Berechnet anhand der prozentualen Wahrscheinlichkeit \b A
             und \b B, ob sich Ereignis \b A ergibt.
      \note \b A und \b B werden automatisch auf Werte
            innerhalb [1..99] begrenzt.
      \param A (\a u32) prozentuale Wahrscheinlichkeit für Ereignis \b A
      \param B (\a u32) prozentuale Wahrscheinlichkeit für Ereignis \b B
      \return `true` wenn Ereignis \b A eintritt, ansonsten `false`
    */
    bool doesAoccur100( const u32 A, const u32 B );

    /*! \brief Gibt eine zufällig erzeugte Zahl zurück.
             Diese wurde mittels einem fairen echten Würfel-Wurf ermittelt.
             Garantiert zufällig!
             (c) XKCD (http://xkcd.com/221/)
      \attention Benutzen auf eigene Gefahr!
      \param -
      \return \a int Die per Würfel ermittelte Zahl "4".
    */
    u8 getRandomNumber() const;

private:

    u32 seed_, seed2_, seed3_, seed4_;  // Startwerte
    u32 tmp_;

    Zufall();  // ctor. Von außen keine Instanzen direkt erzeugbar
    Zufall( const Zufall& );  // Instanz ist nicht kopierbar
    Zufall& operator=( const Zufall& );  // Instanz ist nicht zuweisbar
    ~Zufall() {}  // dtor. Instanz zerstört sich bei Programmende

};
// Ende class Zufall

#endif
// Ende Header-Datei Zufall
