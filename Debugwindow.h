/*! \file Debugwindow.h
  \brief Klasse (Singleton) mit verschiedenen Methoden für ein Debugfenster.
*/

#ifndef _DEBUGWINDOW_HEADER
#define _DEBUGWINDOW_HEADER

// Linken der IRRLICHT-DLL, nur in VisualStudio nötig
//#ifdef _IRR_WINDOWS_
//    #pragma comment(lib, "Irrlicht.lib")
//#endif

#include <irrlicht.h>

using namespace irr;
// Die innenliegenden Namespaces "core", "video" usw. werden im Folgenden
// immer explizit angegeben, um den Ueberblick zu behalten.

/*! \class Debugwindow Debugwindow.h "Debugwindow.h"
  \brief Ein IRRLICHT-Debugfenster.

  Diese Klasse enthält Funktionen zum Befüllen und Anzeigen eines
  IRRLICHT-Debugfensters. Der anzuzeigende Text kann von überall im Code in das
  Fenster geschrieben werden.
  \attention Klasse ist `Singleton`.\n Ein Zeiger auf eine Instanz des
             Irrlicht-Entchens wird benötigt.
  \note Instanzierung: `Debugwindow& myDebugwindow =
        Debugwindow::getInstance();`
        \n Oder: `Debugwindow::getInstance();`
        \n Benutzen: `myDebugwindow.show();`
        \n Oder: `Debugwindow::getInstance().toggle();`
*/
class Debugwindow
{

public:

    /*! \brief Ersatz für den Konstruktor.

      Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
      Das Debugwindow wird per Default NICHT angezeigt.
      \param device (\a IrrlichtDevice*) Zeiger auf das Entchen
      \return Referenz auf die einzige Instanz dieser Klasse
    */
    static Debugwindow& getInstance( IrrlichtDevice* device = 0 ); 

    /*! \brief Fügt Text in das Debugfenster ein.
      \attention Es wird automatisch ein Zeilenumbruch angehängt.
      \param text (\a core::stringw&) Text
      \return -
    */
    void addLine( const core::stringw& text );

    /*! \brief Fügt Text und Daten in das Debugfenster ein.

      Schreibt eine Irrlicht-Zeichenkette und eine Zahl beliebigen Typs in das
      Debugfenster.
      \attention Es wird automatisch ein Zeilenumbruch angehängt.
      \param text (\a core::stringw&) Text
      \param number (\a beliebiger \a Zahlentyp) Zahl
      \return -
    */
    // Da diese Funktion für verschiedene Zahlentypen gilt, und das durch ein
    // Template realisiert wird, muss der Body leider in der Headerdatei
    // angelegt werden.
    template <typename T>
    void addLine( const core::stringw& text, const T number )
    {
        if ( dwin_->isVisible() )
        {
            content_ += text;
            content_ += core::stringw( number );
            content_ += newLine_;
        }
    }

    /*! \brief Fügt Text und Daten in das Debugfenster ein.

      Schreibt eine Irrlicht-Zeichenkette und zwei Zahlen beliebigen (aber
      gleichen) Typs in das Debugfenster.
      \attention Es wird automatisch ein Zeilenumbruch angehängt.
      \param text (\a core::stringw&) Text
      \param number1 (\a beliebiger \a Zahlentyp) Zahl 1
      \param number2 (\a beliebiger \a Zahlentyp) Zahl 2
      \return -
    */
    // Da diese Funktion für verschiedene Zahlentypen gilt, und das durch ein
    // Template realisiert wird, muss der Body leider in der Headerdatei
    // angelegt werden.
    template <typename T>
    void addLine( const core::stringw& text, const T number1, const T number2 )
    {
        if ( dwin_->isVisible() )
        {
            content_ += text;
            content_ += L"( ";
            content_ += core::stringw( number1 );
            content_ += L", ";
            content_ += core::stringw( number2 );
            content_ += L" )";
            content_ += newLine_;
        }
    }

    /*! \brief Fügt Text und Daten in das Debugfenster ein.

      Schreibt eine Irrlicht-Zeichenkette und drei Zahlen beliebigen (aber
      gleichen) Typs in das Debugfenster.
      \attention Es wird automatisch ein Zeilenumbruch angehängt.
      \param text (\a core::stringw&) Text
      \param number1 (\a beliebiger \a Zahlentyp) Zahl 1
      \param number2 (\a beliebiger \a Zahlentyp) Zahl 2
      \param number3 (\a beliebiger \a Zahlentyp) Zahl 3
      \return -
    */
    // Da diese Funktion für verschiedene Zahlentypen gilt, und das durch ein
    // Template realisiert wird, muss der Body leider in der Headerdatei
    // angelegt werden.
    template <typename T>
    void addLine( const core::stringw& text, const T number1, const T number2,
            const T number3 )
    {
        if ( dwin_->isVisible() )
        {
            content_ += text;
            content_ += L"( ";
            content_ += core::stringw( number1 );
            content_ += L", ";
            content_ += core::stringw( number2 );
            content_ += L", ";
            content_ += core::stringw( number3 );
            content_ += L" )";
            content_ += newLine_;
        }
    }

    /*! \brief Zeigt das Debugfenster an, wenn \b isVisible() == `true`.
      \param -
      \return -
    */
    void show();
    
    /*! \brief Schaltet die Sichtbarkeit des Debugfenster um.
      \param -
      \return -
    */
    void toggle();
    
    /*! \brief Gibt an, ob das Debugfenster sichtbar ist.
      \param -
      \return `true` wenn das Debugfenster sichtbar ist, ansonsten `false`
    */
    bool isVisible() const;

private:

    IrrlichtDevice* device_;  // das Entchen
    gui::IGUIEnvironment* guienv_;  // IRRLICHT GUI Zeiger
    gui::IGUIStaticText* dwin_;  // das GUI-Element "Fenster"
    core::stringw content_;  // Inhalt des Fensters
    core::stringw newLine_;  // Maske für einen Zeilenumbruch
    u32 displayTimer_;  // Aktualisierung des Debugwindow aller ?ms

    Debugwindow( IrrlichtDevice* device );  // ctor. Von aussen keine Instanzen
                                            // direkt erzeugbar
    Debugwindow( const Debugwindow& );  // Instanz ist nicht kopierbar
    Debugwindow& operator=( const Debugwindow& );  // Instanz ist nicht
                                                   // zuweisbar
    ~Debugwindow();  // dtor. Instanz zerstört sich bei Programmende
    
};
// Ende class Debugwindow

#endif
// Ende Header-Datei Debugwindow
