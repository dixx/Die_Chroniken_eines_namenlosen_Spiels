#include "LoadingScreen.h"
#include "Configuration.h"
#include "Constants.h"
#include "GenericHelperMethods.h"
#include "Logfile.h"



LoadingScreen::LoadingScreen( irr::IrrlichtDevice* device, irr::io::path imageFileName )
:  device_(device),
  imageFileName_(imageFileName),
  loadingScreenImageFrame_(0),
  loadingText_(0)
{
    if ( device_ == 0 )
        Logfile::getInstance().emergencyExit( "Entchen in [LoadingScreen] nicht mehr gefunden! Abbruch." );
    createLoadingScreenImage();
    createLoadingScreenText();
    loadingScreenImageFrame_->getImage()->grab();  // don't let anyone delete your precious image!
}



LoadingScreen::~LoadingScreen()
{
    loadingScreenImageFrame_->getImage()->drop();  // you grab it, you drop it.
    loadingScreenImageFrame_->remove();
    loadingText_->remove();
}



void LoadingScreen::enable()
{
    loadingScreenImageFrame_->setEnabled( true );
    loadingScreenImageFrame_->setVisible( true );
}



void LoadingScreen::disable()
{
    loadingScreenImageFrame_->setVisible( false );
    loadingScreenImageFrame_->setEnabled( false );
}



void LoadingScreen::setText( const wchar_t* text )
{
    loadingText_->setText( text );
}



/* private */



void LoadingScreen::createLoadingScreenImage()
{
    GenericHelperMethods::getInstance().validateFileExistence( imageFileName_ );
    irr::video::ITexture* loadingScreenImage = device_->getVideoDriver()->getTexture( imageFileName_ );
    irr::core::recti frame = screenDependentSizeOf( *loadingScreenImage );
    loadingScreenImageFrame_ = device_->getGUIEnvironment()->addImage( frame );
    loadingScreenImageFrame_->setImage( loadingScreenImage );
    loadingScreenImageFrame_->setScaleImage( true );
    loadingScreenImageFrame_->setEnabled( false );
    loadingScreenImageFrame_->setVisible( false );
}



void LoadingScreen::createLoadingScreenText()
{
    irr::core::dimension2di screenSize = irr::core::dimension2di( Configuration::getInstance().getScreenSize() );
    GenericHelperMethods& helpers = GenericHelperMethods::getInstance( device_ );
    loadingText_ = device_->getGUIEnvironment()->addStaticText(
            L"",
            irr::core::recti(
                irr::core::position2di( 9, screenSize.Height - 30 ),
                irr::core::position2di( screenSize )
            )
    );
    loadingText_->setOverrideColor( irr::video::SColor( 255, 128, 64, 64) );
    helpers.validateFileExistence( "GFX/FONTS/Dooling_font.xml" );
    helpers.validateFileExistence( "GFX/FONTS/Dooling_font.png" );
    helpers.validateFileExistence( "GFX/FONTS/Dooling_font_readme.txt" );
    irr::gui::IGUIFont* font = device_->getGUIEnvironment()->getFont( "GFX/FONTS/Dooling_font.xml" );
    loadingText_->setOverrideFont( font );
}



irr::core::recti LoadingScreen::screenDependentSizeOf( irr::video::ITexture& image )
{
    irr::core::dimension2du screenSize = Configuration::getInstance().getScreenSize();
    irr::f32 screenWidth = static_cast<irr::f32>( screenSize.Width );
    irr::f32 screenHeight = static_cast<irr::f32>( screenSize.Height );
    irr::f32 screenRatio = screenWidth / screenHeight;
    irr::f32 imageWidth = static_cast<irr::f32>( image.getSize().Width );
    irr::f32 imageHeight = static_cast<irr::f32>( image.getSize().Height );
    irr::f32 imageRatio = imageWidth / imageHeight;
    irr::core::recti frame;
    if ( imageRatio > screenRatio )
    {
        irr::f32 resizedImageHeight = ( screenWidth / imageWidth ) * imageHeight;
        irr::f32 minHightOffset = ( screenHeight - resizedImageHeight ) / 2.0f;
        frame = irr::core::recti(
                0,
                static_cast<irr::s32>( minHightOffset ),
                static_cast<irr::s32>( screenSize.Width ),
                static_cast<irr::s32>( minHightOffset + resizedImageHeight )
        );
    }
    else if ( imageRatio < screenRatio )
    {
        irr::f32 resizedImageWidth = ( screenHeight / imageHeight ) * imageWidth;
        irr::f32 minWidthOffset = ( screenWidth - resizedImageWidth ) / 2.0f;
        frame = irr::core::recti(
                static_cast<irr::s32>( minWidthOffset ),
                0,
                static_cast<irr::s32>( minWidthOffset + resizedImageWidth ),
                static_cast<irr::s32>( screenSize.Height )
        );
    }
    else
    {
        frame = irr::core::recti( VEC_2DI_NULL, screenSize );
    }
    return frame;
}
