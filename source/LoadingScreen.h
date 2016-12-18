/*! \file LoadingScreen.h
 *  \brief Klasse stellt Schnittstelle für einen Ladebildschirm bereit.
 */

#ifndef _LOADINGSCREEN_HEADER
#define _LOADINGSCREEN_HEADER

#include <irrlicht.h>

/*! \class LoadingScreen LoadingScreen.h "LoadingScreen.h"
 *  \brief Schnittstelle für Ladebildschirm.
 *  \note Instanzierung: `LoadingScreen* myLoadingScreen = new LoadingScreen();`
 *  \n Benutzen: `myLoadingScreen->setText(L"...");`
 */
class LoadingScreen
{

public:

    /*! \brief Konstruktor.
     *  \param device (\a IrrlichtDevice*) Zeiger auf das Entchen
     *  \param imageFileName (\a io::path&) relativer oder absoluter Pfad zum Hintergrundbild
     *  \return Zeiger auf das instanzierte Klassenobjekt
     */
    LoadingScreen( irr::IrrlichtDevice* device, irr::io::path imageFileName );

    /*! \brief Destruktor.
     */
    ~LoadingScreen();

    /*! \brief Aktiviert den Ladebildschirm.
     *  \param -
     *  \return -
     */
    void enable();

    /*! \brief Deaktiviert den Ladebildschirm.
     *  \param -
     *  \return -
     */
    void disable();

    /*! \brief Aktualisiert das Textfeld des Ladebildschirms.
     *  \param text (\a const \a wchar_t*) neuer Text
     *  \return -
     */
    void setText( const wchar_t* text );

private:

    irr::IrrlichtDevice* device_;
    irr::io::path imageFileName_;
    irr::gui::IGUIImage* loadingScreenImageFrame_;
    irr::gui::IGUIStaticText* loadingText_;

    LoadingScreen( const LoadingScreen& );
    LoadingScreen& operator=( const LoadingScreen& );

    void createLoadingScreenImage();
    void createLoadingScreenText();
    irr::core::recti screenDependentSizeOf( irr::video::ITexture& image );

};

#endif
