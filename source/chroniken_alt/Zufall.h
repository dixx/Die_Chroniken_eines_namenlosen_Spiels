/*! \file Zufall.h
 *  \brief Klasse (Singleton) mit verschiedenen Methoden für Zufallsberechnung.
 */

#ifndef _ZUFALL_HEADER
#define _ZUFALL_HEADER

#include <irrlicht.h>

/*! \class Zufall Zufall.h "Zufall.h"
 *  \brief Enthält Funktionen zum Erzeugen von Zufallszahlen.
 *  \attention Klasse ist `Singleton`.
 *  \note Instanzierung: `Zufall& myZufall = Zufall::getInstance();` \n Oder: `Zufall::getInstance();`
 *        \n Benutzen: `myZufall.start( (u32)time( NULL ) );` \n Oder: `Zufall::getInstance().getInt();`
 */
class Zufall
{

public:

    /*! \brief Ersatz für den Konstruktor.
     *
     *  Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
     *  \return Referenz auf die einzige Instanz dieser Klasse
     */
    static Zufall& getInstance();

    /*! \brief Initialisiert den Zufallsgenerator.
     *  \attention Muss vor dem Benutzen der anderen Methoden aufgerufen werden, sonst werden bei jedem Programmstart
     *             dieselben Werte errechnet wie vorher!\n
     *             Möglicher Aufruf: `Zufall::getInstance().start( (u32)time( NULL ) );`
     *  \param seed (\a u32) Startwert
     *  \return -
     */
    void start( const irr::u32 seed );

    /*! \brief Berechnet eine \a float Zufallszahl zwischen \b 0.0 und \b 0.9periode... (inklusive).
     *  \param -
     *  \return \a f32 Zufallszahl
     */
    irr::f32 getFloat();

    /*! \brief Berechnet eine \a int Zufallszahl zwischen \b 0 und \b 4294967295 (inklusive).
     *  \note Berechnung basiert auf XORSHIFT mit 4 Seeds
     *  \param -
     *  \return \a u32 Zufallszahl
     */
    irr::u32 getInt();

    /*! \brief Berechnet eine \a int Zufallszahl zwischen \b min und \b max (inklusive).
     *  \note Vertauscht automatisch \b min und \b max, wenn \b min grösser ist als \b max.
     *  \attention Maximalwert darf U32_MAX-1 nicht überschreiten!
     *  \param min (\a u32) unterer Grenzwert
     *  \param max (\a u32) oberer Grenzwert
     *  \return \a int Zufallszahl
     */
    irr::u32 getIntBetween( const irr::u32 min, const irr::u32 max );

    /*! \brief Berechnet eine \a float Zufallszahl zwischen \b min und \b max (inklusive).
     *  \note Vertauscht automatisch \b min und \b max, wenn \b min grösser ist als \b max.
     *  \param min (\a f32) unterer Grenzwert
     *  \param max (\a f32) oberer Grenzwert
     *  \return \a f32 Zufallszahl
     */
    irr::f32 getFloatBetween( const irr::f32 min, const irr::f32 max );

    /*! \brief Berechnet anhand einer Wahrscheinlichkeit \b p, ob ein Ereignis eintritt.
     *  \note \b p wird automatisch auf Werte innerhalb [0..100] begrenzt.
     *  \param p (\a f32) Prozentuale Wahrscheinlichkeit für ein Ereignis
     *  \return `true` (Ereignis tritt ein) oder `false`
     */
    bool doesOccur( const irr::f32 p );

    /*! \brief Berechnet anhand des Verhältnisses von \b A zu \b B, ob Ereignis \b A eintritt.
     *  \param A (\a f32) Verhältniswert für Ereignis \b A
     *  \param B (\a f32) Verhältniswert für Ereignis \b B
     *  \return `true` wenn Ereignis \b A eintritt, ansonsten `false`
     */
    bool doesAoccur( const irr::f32 A, const irr::f32 B );

    /*! \brief Berechnet anhand der prozentualen Wahrscheinlichkeit \b A und \b B, ob sich Ereignis \b A ergibt.
     *  \note \b A und \b B werden automatisch auf Werte innerhalb [1..99] begrenzt.
     *  \param A (\a u32) prozentuale Wahrscheinlichkeit für Ereignis \b A
     *  \param B (\a u32) prozentuale Wahrscheinlichkeit für Ereignis \b B
     *  \return `true` wenn Ereignis \b A eintritt, ansonsten `false`
     */
    bool doesAoccur100( const irr::u32 A, const irr::u32 B );

    /*! \brief Gibt eine zufällig erzeugte Zahl zurück. Diese wurde mittels einem fairen echten Würfel-Wurf ermittelt.
     *         Garantiert zufällig! (c) XKCD (http://xkcd.com/221/)
     *  \attention Benutzen auf eigene Gefahr!
     *  \param -
     *  \return \a int Die per Würfel ermittelte Zahl "4".
     */
    irr::u8 getRandomNumber() const;

private:

    irr::u32 seed_, seed2_, seed3_, seed4_;  // Startwerte
    irr::u32 tmp_;

    Zufall();  // ctor. Von außen keine Instanzen direkt erzeugbar
    Zufall( const Zufall& );  // Instanz ist nicht kopierbar
    Zufall& operator=( const Zufall& );  // Instanz ist nicht zuweisbar
    ~Zufall() {}  // dtor. Instanz zerstört sich bei Programmende

};

#endif
