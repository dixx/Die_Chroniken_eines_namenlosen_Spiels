#include "LoadingScreen.h"
#include "Configuration.h"
#include "GenericHelperMethods.h"
#include "Logfile.h"



LoadingScreen::LoadingScreen( IrrlichtDevice* device, io::path& imageFileName )
:  device_(device),
  imageFileName_(imageFileName)
{
    if ( device_ == 0 )
        Logfile::getInstance().emergencyExit( "Entchen in [LoadingScreen] nicht mehr gefunden! Abbruch." );
    createLoadingScreenImage();
    createLoadingScreenText();
}



LoadingScreen::~LoadingScreen()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    loadingScreenImageFrame_->remove();
    loadingText_->remove();
}



void LoadingScreen::setText( core::stringw& text )
{
    loadingText_->setText( text.c_str() );
}



/* private */



void LoadingScreen::createLoadingScreenImage()
{
    GenericHelperMethods::getInstance().validateFileExistence( imageFileName_ );
    video::ITexture* loadingScreenImage = device_->getVideoDriver()->getTexture( imageFileName_ );
    loadingScreenImageFrame_ = device_->getGUIEnvironment()->addImage(
            // set to screen center
            core::recti( core::dimension2di( 0, 0 ), Configuration::getInstance().getScreenSize() ) );
    loadingScreenImageFrame_->setImage( loadingScreenImage );
    // if image > screensize:
    loadingScreenImageFrame_->setScaleImage( true );
    loadingScreenImageFrame_->setEnabled( false );
}



void LoadingScreen::createLoadingScreenText()
{
    core::dimension2du screenSize = Configuration::getInstance().getScreenSize();
    GenericHelperMethods& helpers = GenericHelperMethods::getInstance( device_ );
    loadingText_ = device_->getGUIEnvironment()->addStaticText(
            L"", core::recti( core::dimension2di( 9, screenSize.Height - 30 ), screenSize ) );
    loadingText_->setOverrideColor( video::SColor( 255, 128, 64, 64) );
    helpers.validateFileExistence( "GFX/FONTS/Dooling_font.xml" );
    helpers.validateFileExistence( "GFX/FONTS/Dooling_font.png" );
    helpers.validateFileExistence( "GFX/FONTS/Dooling_font_readme.txt" );
    gui::IGUIFont* font = device_->getGUIEnvironment()->getFont( "GFX/FONTS/Dooling_font.xml" );
    loadingText_->setOverrideFont( font );
}
