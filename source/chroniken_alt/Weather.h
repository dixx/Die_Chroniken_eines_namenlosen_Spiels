/*! \file Weather.h
 *  \brief Klasse (Singleton) stellt Schnittstelle für Wetter bereit.
 */

#ifndef _WEATHER_HEADER
#define _WEATHER_HEADER

#include "leviathan.h"

/*! \class Weather Weather.h "Weather.h"
 *  \brief  Schnittstelle für Wetter und Weltlicht.
 *  \attention Klasse ist `Singleton`.
 *  \note Instanzierung: `Weather& myWeather = Weather::getInstance();` \n Oder: `Weather::getInstance();`
 *        \n Benutzen: `myWeather.getSkyColor();` \n Oder: `Weather::getInstance().getDayTime();`
 */
class Weather
{

public:

    /*! \brief Ersatz für den Konstruktor.
     *
     *  Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
     *  \param smgr (\a scene::ISceneManager*) Zeiger auf den ScenenManager
     *  \return Referenz auf die einzige Instanz dieser Klasse
     */
    static Weather& getInstance( irr::scene::ISceneManager* smgr = 0 );

    /*! \brief Lädt Wetter.
     *  \param -
     *  \return -
     */
    void load();

    /*! \brief Entlädt Wetter.
     *  \param -
     *  \return -
     */
    void unload();

    /*! \brief Gibt Farbe des Himmels zurück. Diese ist abhängig von Wetter, Mond und Tageszeit.
     *  \param -
     *  \return \a const \a video::SColor& Himmelsfarbe
     */
    const irr::video::SColor& getSkyColor() const;

    /*! \brief Aktualisiert Wetter.
     *  \param -
     *  \return -
     */
    void update();

    /*! \brief Gibt die aktuelle Tageszeit in virtuellen Sekunden zurück.
     *  \param -
     *  \return \a f32 Uhrzeit ( Zeitformat 24h*100m*100.0s )
     */
    irr::f32 getDayTime() const;

    /*! \brief Gibt die aktuelle Mondzeit in virtuellen Sekunden zurück.
     *  \param -
     *  \return \a f32 Mondzeit ( Zeitformat 24h*100m*100.0s )
     */
    irr::f32 getMoonPhase() const;

private:

    irr::f32 SUNCYCLEDURATION_;  // Anzahl Spiel-Sekunden pro Sonnen-Umlauf
    irr::f32 MOONCYCLEDURATION_;  // Anzahl Spiel-Sekunden pro Mond-Umlauf
    irr::f32 SUNMOVEMENTDELTA_;  // "Konstante" zur schnellen Sonnenstand-Berechnung
    irr::f32 MOONMOVEMENTDELTA_;  // "Konstante" zur schnellen Mondstand-Berechnung
    irr::f32 FACTOR_V2R_SEC_;  // Faktor virtuelle Zeit zu reale Zeit
    // 24vh pro Tag, 100min pro vh, 100s pro min, 24vh entsprechen 2 Realstunden
    irr::scene::ISceneManager* smgr_;
    irr::core::array<irr::scene::ILightSceneNode*> dayLightSource_;
    irr::core::array<irr::f32> sunCircleY_;  // Sonnenstand, von -1 bis +1
    irr::core::array<irr::f32> moonCircleY_;  // Mondstand, von -1 bis +1
    irr::f32 fogDensity_;
    irr::f32 lightRadius_;
    irr::f32 currentDayTime_;  // Spiel-"Uhrzeit" in "virtuelle Sekunden"
    irr::f32 currentMoonPhase_;  // Mondumlauf-"Uhrzeit" in "virtuelle Sekunden"
    irr::f32 seasonOffsetY_;  // längere/kürzere Tage, von -0.2f bis 0.2f
    irr::video::SColor skyColor_;
    leviathan::core::Timer* updateTimer_;

    Weather( irr::scene::ISceneManager* smgr );
    Weather( const Weather& );
    Weather& operator=( const Weather& );
    ~Weather();

    void calculateSunMoonCirclesY();
    void setFog();
    void createLights();
    void calculateLightValues();
    inline void clearArrays();

};

#endif
