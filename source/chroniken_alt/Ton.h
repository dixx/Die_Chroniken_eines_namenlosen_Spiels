/*! \file Ton.h
 *  \brief Klasse (Singleton) stellt Schnittstelle für Musik und Sounds bereit.
 */

#ifndef _TON_HEADER
#define _TON_HEADER

#include <irrlicht.h>
#include <irrKlang.h>

// Statt der irrklang-Typedefs werden weiterhin die Irrlicht-Typedefs verwendet.

/*! \class Ton Ton.h "Ton.h"
 *  \brief  Schnittstelle zu Geräuschen und Musik sowie deren Effekten.
 *  \attention Klasse ist `Singleton`.
 *  \note Instanzierung: `Ton& myTon = Ton::getInstance();` \n Oder: `Ton::getInstance();`
 *        \n Benutzen: `myTon.playGUISound( SND_GUI_CLICKBUTTON );`
 *        \n Oder: `Ton::getInstance().playGUISound( SND_GUI_HOVER );`
 */
class Ton
{

public:

    /*! \brief Sounds
     *
     *  Jedes Geräusch erhält eine ID.
     */
    enum Sound_ID
    {
        SND_GUI_HOVER = 0,  //!< Maus über Button
        SND_GUI_CLICKBUTTON,  //!< Button gedrückt

        SND_COUNT  //!< Anzahl verfügbarer IDs, sicherheitsrelevant!
    };

    /*! \brief Ersatz für den Konstruktor.
     *
     *  Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
     *  \param fs (\a IFileSystem*) Zeiger auf das virtuelle Dateisystem
     *  \return Referenz auf die einzige Instanz dieser Klasse
     */
    static Ton& getInstance( irr::io::IFileSystem* fs = 0 );

    /*! \brief Lädt eine Sounddatei in den Speicher.
     *  \param filename (\a c8*) zu ladende Datei
     *  \return -
     */
    void preload( const irr::c8* filename );

    /*! \brief Spielt eine GUI-Sounddatei ab.
     *  \param id (\a enum \a Sound_ID) ID des zu spielenden GUI-Sounds
     *  \return -
     */
    void playGUISound( const Sound_ID id );

private:

    irrklang::ISoundEngine* soundEngine_;  // Zeiger auf IrrKlang Sound Engine
    irr::io::IFileSystem* fileSystem_;  // Zeiger auf das virtuelle FileSystem
    irr::core::array<irr::core::stringc> sndGuiArray_;  // Array aller GUI-Geräusche

    Ton( irr::io::IFileSystem* fs = 0 );  // ctor. Von außen keine Instanzen direkt erzeugbar
    Ton( const Ton& );  // Instanz ist nicht kopierbar
    Ton& operator=( const Ton& );  // Instanz ist nicht zuweisbar
    ~Ton();  // dtor. Instanz zerstört sich bei Programmende

    inline void initAllSounds();

};

#endif
