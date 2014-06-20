#include "Debugwindow.h"
#include "Constants.h"
#include "Logfile.h"



Debugwindow& Debugwindow::getInstance( IrrlichtDevice* device ) 
{ 
    static Debugwindow instance( device );
    return instance;
}



void Debugwindow::addLine( const core::stringw& text )
{
    if ( dwin_->isVisible() )
    {
        content_ += text;
        content_ += newLine_;
    }
}



void Debugwindow::show()
{
    if ( dwin_->isVisible() )
    {
        if ( displayTimer_ < device_->getTimer()->getRealTime() )
        {
            displayTimer_ = device_->getTimer()->getRealTime() + 500;
            dwin_->setText( content_.c_str() );
        }
    }
    content_ = L"";
}



void Debugwindow::toggle()
{
    dwin_->setVisible( !dwin_->isVisible() );
    content_ = L"";
}



bool Debugwindow::isVisible() const
{
    return dwin_->isVisible();
}



/* private */



Debugwindow::Debugwindow( IrrlichtDevice* device )
: device_(device),
  content_(L""),
  newLine_(L"\r\n")
{
    if ( device_ == 0 )
        Logfile::getInstance().emergencyExit( "Entchen in [Debugwindow] nicht mehr gefunden! Abbruch." );
    dwin_ = device_->getGUIEnvironment()->addStaticText(
        L"",
        core::recti( VEC_2DI_NULL, core::vector2di( 300, 300 ) ),
        false,
        true,
        0,
        -1,
        true
    );
    dwin_->setVisible( false );
    dwin_->setEnabled( false );
    dwin_->setOverrideColor( COL_GREEN );
    dwin_->setBackgroundColor( video::SColor( 160,  0,  0,  0 ) );
    displayTimer_ = device_->getTimer()->getRealTime();
}



Debugwindow::~Debugwindow()
{
    // nothing to do here
    dwin_->remove();
}
