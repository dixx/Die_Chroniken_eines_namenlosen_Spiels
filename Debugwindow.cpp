#include "Debugwindow.h"
#include "Constants.h"
#include "Logfile.h"



Debugwindow& Debugwindow::getInstance( IrrlichtDevice* device ) 
{ 
    static Debugwindow instance( device );
    return instance;
}



void Debugwindow::addLine( const c8* callerName, const core::stringw& text )
{
    if ( dwin_->isVisible() )
        fragments_.set(callerName, text);
}



void Debugwindow::show()
{
    if ( dwin_->isVisible() )
    {
        if ( displayTimer_ < device_->getTimer()->getRealTime() )
        {
            displayTimer_ = device_->getTimer()->getRealTime() + 500;
            fragment_ = fragments_.getParentFirstIterator();
            content_ = L"";
            while ( !fragment_.atEnd() )
            {
                content_ += fragment_.getNode()->getValue();
                content_ += newLine_;
                fragment_++;
            }
            dwin_->setText( content_.c_str() );
        }
    }
}



void Debugwindow::toggle()
{
    dwin_->setVisible( !dwin_->isVisible() );
    fragments_.clear();  // to be able to "reset" the collected lines of text in the window
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
    fragments_.clear();
    displayTimer_ = device_->getTimer()->getRealTime();
}



Debugwindow::~Debugwindow()
{
    dwin_->remove();
}
