/*! \file Mauspfeil.h
 *  \brief Klasse (Singleton) stellt ein umfassendes Mauspfeil-Management bereit.
 */

#ifndef _MAUSPFEIL_HEADER
#define _MAUSPFEIL_HEADER

#include <irrlicht.h>

/*! \class Mauspfeil Mauspfeil.h "Mauspfeil.h"
 *  \brief Stellt einen Mauspfeil-Manipulator bereit.
 *  \attention Klasse ist `Singleton`.
 *  \note Instanzierung: `Mauspfeil& myMauspfeil = Mauspfeil::getInstance();` \n Oder: `Mauspfeil::getInstance();`
 *        \n Benutzen: `myMauspfeil.updateMouse();` \n Oder: `Mauspfeil::getInstance().updateMouse()`
 */
class Mauspfeil
{

public:

    /*! \brief Mauspfeil-Auswahl
     *
     *  Alle Angaben des gewählten Mauspfeils werden hiermit indiziert.
     */
    enum Pfeil
    {
        MAUSPFEIL_UNSICHTBAR = 0,  //!< Mauspfeil wird nicht angezeigt
        MAUSPFEIL_SELECT,  //!< Normaler Pfeil
        MAUSPFEIL_GESPERRT,  //!< Nicht begehbar
        MAUSPFEIL_WARTE,  //!< Sanduhr
        MAUSPFEIL_MISCHMASCH,  //!< Zeigt alle Bilder einmal an

        MAUSPFEIL_COUNT  //!< Anzahl verfügbarer Mauspfeile
    };

    /*! \brief Ersatz für den Konstruktor.
     *
     *  Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
     *  \param device (\a IrrlichtDevice*) Zeiger auf das Entchen
     *  \return Referenz auf die einzige Instanz dieser Klasse
     */
    static Mauspfeil& getInstance( irr::IrrlichtDevice* device = 0 );

    /*! \brief Zeichnet den Mauszeiger mit dem aktuell gewählten Bild auf den Bildschirm.
     *  \param -
     *  \return -
     */
    void draw();

    /*! \brief Gibt den Enum des aktuell gewählten Mauspfeils zurück.
     *  \param -
     *  \return \a Enum Mauspfeil
     */
    Pfeil getCurrentArrow() const;

    /*! \brief Ändert den zu zeichnenden Mauspfeil.
     *  \param mauspfeil (\a Enum) zu setzender Mauspfeil
     *  \return -
     */
    void setCurrentArrow( const Pfeil mauspfeil);

private:

    irr::IrrlichtDevice* device_;  // Zeiger auf Entchen
    irr::gui::ICursorControl* control_;  // IRRLICHT Maus Zeiger
    irr::video::ITexture* imageCatalog_;  // Zeiger auf aktuelle Mauspfeil-Bildfolge
    irr::core::dimension2di imageCatalogRaster_;  // Aufteilung der Einzelbilder im Imagekatalog
    irr::core::array<irr::core::recti> imageCatalogActualPosition_;  // Liste der Positionen aller Einzelbilder
                                                          // innerhalb des Imagekataloges
    irr::core::array<irr::u32> startImageNumber_;  // Liste der Nummern des Startbildes für Mauspfeilanimation im Imagekatalog
    irr::core::array<irr::u32> endImageNumber_;  // Liste der Nummern des letzten Bildes der Mauspfeilanimation im Imagekatalog
    irr::u32 actualImageNumber_;  // Nummer des aktuellen Bildes der Mauspfeilanimation
    irr::core::array<irr::u32> sequenceSpeed_;  // Liste der Geschwindigkeiten des Einzelbild-Wechsels in Bilder pro Sekunde
    irr::u32 interFrameTime_;  // Zeit zwischen zwei Frames (in ms)
    irr::core::recti imageSize_;  // Größe eines Mauspfeil-Einzelbildes
    irr::core::position2di hotSpot_;  // Position des Maus-HotSpots
    irr::u32 sequenceTimer_;  // Zeitgeber-Hilfsvariable für Einzelbild-Wechsel
    Pfeil currentArrow_;  // Enum des aktuell gewählten Mauspfeils

    Mauspfeil( irr::IrrlichtDevice* device );
    Mauspfeil( const Mauspfeil& );
    Mauspfeil& operator=( const Mauspfeil& );
    ~Mauspfeil();

    inline void setCurrentArrowInterFrameTime();  // Sicherheitsfunktion
    inline void clearArrays();

};

#endif
