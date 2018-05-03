/*! \file Configuration.h
 *  \brief Klasse (Singleton) zum Lesen und Schreiben der Konfig-Datei sowie Verwaltung der enthaltenen Variablen.
 */

#ifndef _CONFIGURATION_HEADER
#define _CONFIGURATION_HEADER

#include <irrlicht.h>

/*! \class Configuration Configuration.h "Configuration.h"
 *  \brief Enthält Funktionen zum Lesen und Schreiben von Konfig-Dateien sowie zum Verändern von Konfig-Variablen.
 *  \attention Klasse ist `Singleton`.\n Ein Zeiger auf eine Instanz des Irrlicht-Dateisystems wird benötigt, dieser
 *             Zeiger wird jedoch nur beim Erstellen benutzt.
 *  \note Instanzierung: `Configuration& myConfiguration = Configuration::getInstance();`
 *        \n Oder: `Configuration::getInstance();`
 *        \n Benutzen: `myConfiguration.readConfigFile( "Config.cfg" );`
 *        \n Oder: `Configuration::getInstance().readConfigFile( "Config.cfg" );`
 */
class Configuration
{

public:

    /*! \brief Ersatz für den Konstruktor.
     *
     *  Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
     *  \param fs (\a IFileSystem*) Zeiger auf das Irrlicht-Dateisystem
     *  \return Referenz auf die einzige Instanz dieser Klasse
     */
    static Configuration& getInstance( irr::io::IFileSystem* fs = 0 );

    /*! \brief Liest eine Konfigdatei aus und schreibt die Werte ins System.
     *  \param filename (\a c8*) Name und Pfad der Logdatei
     *  \return -
     */
    void readConfigFile( const irr::c8* filename );

    /*! \brief Schreibt die Werte aus dem System in eine Konfigdatei.
     *  \param filename (\a c8*) Name und Pfad der Logdatei
     *  \return -
     */
    void writeConfigFile( const irr::c8* filename);

    /*! \brief Ändert den Zeiger auf ein Irrlicht-Dateisystem.
     *  \attention Dies ist notwendig, wenn das Entchen zerstört und neu erstellt wurde!
     *  \param fs (\a IFileSystem*) Zeiger auf das Irrlicht-Dateisystem
     *  \return -
     */
    void setNewFilesystem( irr::io::IFileSystem* fs = 0 );

    /*! \brief Gibt die Bildschirm- oder Fensterdimensionen zurück.
     *  \param -
     *  \return \a core::dimension2du Höhe und Breite in Pixel
     */
    irr::core::dimension2du getScreenSize() const;

    /*! \brief Gibt die Farbtiefe zurück.
     *  \param -
     *  \return \a u16 Farbtiefe
     */
    irr::u16 getColorDepht() const;

    /*! \brief Gibt an, ob die Anwendung Fullscreen oder im Fenstermodus läuft.
     *  \param -
     *  \return \a bool `true` wenn Fullscreen, ansonsten `false`
     */
    bool isFullScreen() const;

    /*! \brief Gibt den Render-Modus (Video-Treiber) zurück.
     *  \param -
     *  \return \a video::E_DRIVER_TYPE Render-Modus
     */
    irr::video::E_DRIVER_TYPE getRenderMode() const;

    /*! \brief Gibt die Sichtweite der Kamera zurück.
     *  \param -
     *  \return \a f32 Sichtweite (in Meter)
     */
    irr::f32 getFarValue() const;

private:

    irr::io::IFileSystem* fs_;  // Zeiger auf das Irrlicht-Dateisystem
    irr::u16 screenSizeX_;  // Bild-Breite in Pixel
    irr::u16 screenSizeY_;  // Bild-Höhe in Pixel
    irr::u16 colorDepht_;  // Farbtiefe in Bit
    bool fullscreen_;  // Vollbild oder Fenstermodus
    irr::f32 farValue_;  // Sichtweite der Kamera
    irr::video::E_DRIVER_TYPE rendermode_;  // Render-Treiber

    Configuration( irr::io::IFileSystem* fs );  // ctor. Von aussen keine Instanzen direkt erzeugbar
    Configuration( const Configuration& );  // Instanz ist nicht kopierbar
    Configuration& operator=( const Configuration& );  // Instanz ist nicht zuweisbar
    ~Configuration();  // dtor. Instanz zerstört sich bei Programmende

    // holt einen bestimmten Wert aus dem eingelesenen Inhalt der Konfigdatei.
    const irr::core::stringc getItem(
            const irr::core::stringc& content,
            const irr::c8* topic,
            const irr::c8* varname,
            const irr::c8* origin = ""
    );

};

#endif
