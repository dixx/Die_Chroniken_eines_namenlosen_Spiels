/*! \file Eventreceiver.h
  \brief Klasse (Singleton) zur Behandlung von Tastatur/Maus, GUI und anderen
         Events.
*/

#ifndef _EVENTRECEIVER_HEADER
#define _EVENTRECEIVER_HEADER

// Linken der IRRLICHT-DLL, nur in VisualStudio nötig
//#ifdef _IRR_WINDOWS_
//    #pragma comment(lib, "Irrlicht.lib")
//#endif

#include <irrlicht.h>

using namespace irr;
// Die innenliegenden Namespaces "core", "video" usw. werden im Folgenden
// immer explizit angegeben, um den Ueberblick zu behalten.

/*! \class Eventreceiver Eventreceiver.h "Eventreceiver.h"
  \brief Diese Klasse enthält Funktionen zum Bearbeiten von Events.

  Events sind Tastatur- und Mauseingaben. GUI-Events (geklickter Button,
  Menüaufruf usw.) werden gesondert behandelt.
  \attention Klasse ist `Singleton`. Klasse ist von IRRLICHT-Klasse
             abgeleitet und multithreading-fähig. Sie wird bei Weitem
             schneller aktualisiert als der Main Loop.
  \note Instanzierung: `Eventreceiver& myEventreceiver =
        Eventreceiver::getInstance();`
        \n Oder: `Eventreceiver::getInstance();`
        \n Benutzen: `myEventreceiver.setKeysLastState();`
        \n Oder: `Eventreceiver::getInstance().isShiftDown();`
*/
class Eventreceiver : public IEventReceiver
{

public:
    
    /*! \brief Ersatz für den Konstruktor.

      Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
      \param -
      \return Referenz auf die einzige Instanz dieser Klasse
    */
    static Eventreceiver& getInstance(); 

    /*! \brief Event-Handler.

      Hier wird festgelegt, was bei einem beliebigen Tastatur-, Maus- oder
      GUI-Ereignis passieren soll.
      \attention Funktion wird im Hintergrund über Events bedient
                 und darf nicht aufgerufen werden!
      \param event (\a SEvent&) Event vom Betriebssystem.
      \return `true` wenn Event erfolgreich behandelt wurde, ansonsten `false`
    */
    virtual bool OnEvent( const SEvent& event );
    // todo check if it must be virtual! if so, change dtor to virtual!

    /*! \brief Merker für die letzten Tastenzustände.

      Wichtig, um mit Veränderungen (Taste wurde gerade gedrückt/losgelassen)
      arbeiten zu können.
      \attention Im Main Loop am Ende aller Tastenabfragen aufrufen, um
                 aktuellen Zustand der Tastatur/Maus für spätere Vergleiche zu
                 speichern!
      \param -
      \return -
    */
    void setKeysLastState();

    /*! \brief Bestimmt ob Eventreceiver auf bestimmte Events reagieren soll.
      \attention Das Abschalten von Reaktionen auf Maus-Events wirkt sich
                 nur auf die Maustasten aus, nicht auf die Mausposition!
      \param keysActive (\a bool) reagiere auf Tastatur-Events
      \param mausActive (\a bool) reagiere auf Maus-Events
      \param guiActive (\a bool) reagiere auf GUI-Events
      \return -
    */
    void setEventReactionActive( bool keysActive = true, bool mausActive = true,
            bool guiActive = true );

    /*! \brief Abfrage des aktuellen Zustands einer Taste.
      \param keyCode (\a const \a EKEY_CODE) TastenCode-Enumerator
      \return `true` wenn die Taste gedrückt ist, ansonsten `false`
    */
    bool isKeyDown( const EKEY_CODE keyCode ) const;

    /*! \brief Abfrage des vorherigen Zustands einer Taste.
      \param keyCode (\a const \a EKEY_CODE) TastenCode-Enumerator
      \return `true` wenn die Taste gedrückt war, ansonsten `false`
    */
    bool wasKeyDown( const EKEY_CODE keyCode ) const;

    /*! \brief Abfrage der Änderung des Zustands einer Taste.
      \param keyCode (\a const \a EKEY_CODE) TastenCode-Enumerator
      \return `true` wenn die Taste gerade noch nicht gedrückt war und jetzt
              gedrückt ist, ansonsten `false`
    */
    bool hasKeyJustBeenPressedDown( const EKEY_CODE keyCode ) const;

    /*! \brief Abfrage der Änderung des Zustands einer Taste.
      \param keyCode (\a const \a EKEY_CODE) TastenCode-Enumerator
      \return `true` wenn die Taste gerade noch gedrückt war und jetzt nicht
              mehr gedrückt ist, ansonsten `false`
    */
    bool hasKeyJustBeenReleased( const EKEY_CODE keyCode ) const;

    /*! \brief Abfrage des aktuellen Zustands der SHIFT-Tasten.
      \param -
      \return `true` wenn eine oder beide SHIFT-Tasten gedrückt sind, ansonsten
              `false`
    */
    bool isShiftDown() const;

    /*! \brief Abfrage des vorherigen Zustands der SHIFT-Tasten.
      \param -
      \return `true` wenn eine oder beide SHIFT-Tasten gedrückt waren, ansonsten
              `false`
    */
    bool wasShiftDown() const;

    /*! \brief Abfrage des aktuellen Zustands der STRG-Tasten.
      \param -
      \return `true` wenn eine oder beide STRG-Tasten gedrückt sind,
              ansonsten `false`
    */
    bool isCtrlDown() const;

    /*! \brief Abfrage des vorherigen Zustands der STRG-Tasten.
      \param -
      \return `true` wenn eine oder beide STRG-Tasten gedrückt waren, ansonsten
              `false`
    */
    bool wasCtrlDown() const;

    /*! \brief Abfrage des aktuellen Zustands der linken Maustaste.
      \param -
      \return `true` wenn linke Maustaste gedrückt ist, ansonsten `false`
    */
    bool isLMBDown() const;

    /*! \brief Abfrage des vorherigen Zustands der linken Maustaste.
      \param -
      \return `true` wenn linke Maustaste gedrückt war, ansonsten `false`
    */
    bool wasLMBDown() const;

    /*! \brief Abfrage des aktuellen Zustands der mittleren Maustaste.
      \param -
      \return `true` wenn mittlere Maustaste gedrückt ist, ansonsten `false`
    */
    bool isMMBDown() const;

    /*! \brief Abfrage des vorherigen Zustands der mittleren Maustaste.
      \param -
      \return `true` wenn mittlere Maustaste gedrückt war, ansonsten `false`
    */
    bool wasMMBDown() const;

    /*! \brief Abfrage des aktuellen Zustands der rechten Maustaste.
      \param -
      \return `true` wenn rechte Maustaste gedrückt ist, ansonsten `false`
    */
    bool isRMBDown() const;

    /*! \brief Abfrage des vorherigen Zustands der rechten Maustaste.
      \param -
      \return `true` wenn rechte Maustaste gedrückt war, ansonsten `false`
    */
    bool wasRMBDown() const;

    /*! \brief Gibt an, ob Mauspfeil über einem Menü und/oder Fenster steht.
      \param -
      \return `true` wenn Maus über Menü oder Fenster, ansonsten `false`
    */
    bool isHover() const;

    /*! \brief Gibt die aktuelle X-Koordinate des Mauspfeils zurück.
      \note Besser virtual core::position2d<s32>
            device->getCursorControl()->getPosition() verwenden!
      \param -
      \return \a s32 aktuelle X-Koordinate
    */
    s32 getMouseX() const;

    /*! \brief Gibt die aktuelle Y-Koordinate des Mauspfeils zurück.
      \note Besser virtual core::position2d<s32>
            device->getCursorControl()->getPosition() verwenden!
      \param -
      \return \a s32 aktuelle Y-Koordinate
    */
    s32 getMouseY() const;

    /*! \brief Gibt die vorherige X-Koordinate des Mauspfeils zurück.
      \param -
      \return \a s32 vorherige X-Koordinate
    */
    s32 getMouseLastX() const;

    /*! \brief Gibt die vorherige Y-Koordinate des Mauspfeils zurück.
      \param -
      \return \a s32 vorherige Y-Koordinate
    */
    s32 getMouseLastY() const;

    /*! \brief Gibt das aktuelle Delta des Mausrades zurück.
      \param -
      \return \a f32 um wieviel wurde das Mausrad bewegt
    */
    f32 getMouseWheel() const;

private:
    
    bool KeyIsDown_[ KEY_KEY_CODES_COUNT ];  // TastenCode-Liste mit den
                                            // aktuellen Werten
    bool KeyLastState_[ KEY_KEY_CODES_COUNT] ;  // TastenCode-Liste mit den
                                               // vorhergehenden Werten.
    // "KeyLastState" ist eine Bremse, sie dient zur synchronisierung.
    // Absolut notwendig, um Statuswechsel von Tasten in "Main-Loop-Speed"
    // abfragen zu können. Denn: der EventReceiver im Hintergrund ist immer
    // schneller als unser Main Loop. Darum würden wir Änderungen
    // (Tastendrücke) gar nicht mitbekommen.
    bool reactOnKeys_;  // Flag, ob Eventreceiver auf Tastatureingaben reagiert
    bool reactOnMouse_;  // Flag, ob Eventreceiver auf Maus-Events reagiert
    bool reactOnGUI_;  // Flag, ob Eventreceiver auf GUI-Events reagiert
    s32 mouseX_;  // aktuelle X-Koordinate des Mauspfeils
    s32 mouseLastX_;  // vorherige X-Koordinate des Mauspfeils
    s32 mouseY_;  // aktuelle Y-Koordinate des Mauspfeils
    s32 mouseLastY_;  // vorherige Y-Koordinate des Mauspfeils
    f32 mouseWheel_;  // in welche Richtung wurde das Scrollrad um wieviel bewegt
    bool ShiftIsDown_;  // aktueller Status der SHIFT-Tasten
    bool ShiftWasDown_;  // vorheriger Status der SHIFT-Tasten
    bool CtrlIsDown_;  // aktueller Status der STRG-Tasten
    bool CtrlWasDown_;  // vorheriger Status der STRG-Tasten
    bool LMBIsDown_;  // aktueller Status der linken Maustaste
    bool LMBWasDown_;  // vorheriger Status der linken Maustaste
    bool MMBIsDown_;  // aktueller Status der mittleren Maustaste
    bool MMBWasDown_;  // vorheriger Status der mittleren Maustaste
    bool RMBIsDown_;  // aktueller Status der rechten Maustaste
    bool RMBWasDown_;  // vorheriger Status der rechten Maustaste
    bool hover_;  // Flag, ob die Maus über einem Menüpunkt oder Fenster steht
    bool thereWasKeyEvent_;  // Flag, ob ein Tastatur-Event erfolgt ist

    Eventreceiver();  // ctor. Von außen keine Instanzen direkt erzeugbar
    Eventreceiver( const Eventreceiver& );  // Instanz ist nicht kopierbar
    Eventreceiver& operator=( const Eventreceiver& );  // Instanz ist nicht
                                                       // zuweisbar
    ~Eventreceiver();  // dtor. Instanz zerstört sich bei Programmende

    inline void resetKeyStates();
    inline void resetMouseButtonStates();
    inline void resetGuiStates();

};
// Ende class Eventreceiver

#endif
// Ende header-Datei Eventreceiver
