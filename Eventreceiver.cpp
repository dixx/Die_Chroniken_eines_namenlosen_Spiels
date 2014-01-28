#include "Eventreceiver.h"
#include "GameStateManager.h"



Eventreceiver& Eventreceiver::getInstance() 
{ 
    static Eventreceiver _instance;
    return _instance; 
}



bool Eventreceiver::OnEvent( const SEvent& event )
{
    if ( reactOnKeys_ && event.EventType == EET_KEY_INPUT_EVENT )
    {
        KeyIsDown_[ event.KeyInput.Key ] = event.KeyInput.PressedDown;
        ShiftIsDown_                     = event.KeyInput.Shift;
        CtrlIsDown_                      = event.KeyInput.Control;
        thereWasKeyEvent_                = true;
        return true;
    } //end Keyboard-Events
    if ( event.EventType == EET_MOUSE_INPUT_EVENT )
    {
        switch ( event.MouseInput.Event )
        {
            case EMIE_MOUSE_MOVED:
                mouseY_ = event.MouseInput.Y;
                mouseX_ = event.MouseInput.X;
                break;
            case EMIE_LMOUSE_PRESSED_DOWN:
                LMBIsDown_ = reactOnMouse_;
                thereWasKeyEvent_ = true;
                break;
            case EMIE_LMOUSE_LEFT_UP:
                LMBIsDown_ = false;
                thereWasKeyEvent_ = true;
                break;
            case EMIE_RMOUSE_PRESSED_DOWN:
                RMBIsDown_ = reactOnMouse_;
                thereWasKeyEvent_ = true;
                break;
            case EMIE_RMOUSE_LEFT_UP:
                RMBIsDown_ = false;
                thereWasKeyEvent_ = true;
                break;
            case EMIE_MMOUSE_PRESSED_DOWN:
                MMBIsDown_ = reactOnMouse_;
                thereWasKeyEvent_ = true;
                break;
            case EMIE_MMOUSE_LEFT_UP:
                MMBIsDown_ = false;
                thereWasKeyEvent_ = true;
                break;
            case EMIE_MOUSE_WHEEL:
                if ( reactOnMouse_ )
                    mouseWheel_ += event.MouseInput.Wheel;
                break;
            default:
                // Mouse-Event konnte nicht behandelt werden.
                break;
        }
    } //end Mouse-Events
    if ( reactOnGUI_ && event.EventType == EET_GUI_EVENT )
    {
        return GameStateManager::getInstance().handleGuiEvents( event );
    } //end GUI-Events
    // Event konnte oder sollte nicht behandelt werden, wird nun von OS
    // behandelt.
    return false;
}



void Eventreceiver::setKeysLastState()
{
    if ( thereWasKeyEvent_ )
    {
        for ( u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i )
            KeyLastState_[ i ] = KeyIsDown_[ i ];
        ShiftWasDown_     = ShiftIsDown_;
        CtrlWasDown_      = CtrlIsDown_;
        LMBWasDown_       = LMBIsDown_;
        MMBWasDown_       = MMBIsDown_;
        RMBWasDown_       = RMBIsDown_;
        thereWasKeyEvent_ = false;
    }
    mouseWheel_ = 0.0f;
    mouseLastX_ = mouseX_;
    mouseLastY_ = mouseY_;
}



void Eventreceiver::setEventReactionActive( bool keysActive,
        bool mausActive, bool guiActive )
{
    reactOnKeys_ = keysActive;
    reactOnMouse_ = mausActive;
    reactOnGUI_ = guiActive;
    resetKeyStates();
    resetMouseButtonStates();
    resetGuiStates();
}



bool Eventreceiver::isKeyDown( const EKEY_CODE keyCode ) const
{
    return KeyIsDown_[ keyCode ];
}



bool Eventreceiver::wasKeyDown( const EKEY_CODE keyCode ) const
{
    return KeyLastState_[ keyCode ];
}



bool Eventreceiver::hasKeyJustBeenPressedDown( const EKEY_CODE keyCode ) const
{
    return ( isKeyDown( keyCode ) && !wasKeyDown( keyCode ) );
}



bool Eventreceiver::hasKeyJustBeenReleased( const EKEY_CODE keyCode ) const
{
    return ( !isKeyDown( keyCode ) && wasKeyDown( keyCode ) );
}



bool Eventreceiver::isShiftDown() const
{
    return ShiftIsDown_;
}



bool Eventreceiver::wasShiftDown() const
{
    return ShiftWasDown_;
}



bool Eventreceiver::isCtrlDown() const
{
    return CtrlIsDown_;
}



bool Eventreceiver::wasCtrlDown() const
{
    return CtrlWasDown_;
}



bool Eventreceiver::isLMBDown() const
{
    return LMBIsDown_;
}



bool Eventreceiver::wasLMBDown() const
{
    return LMBWasDown_;
}



bool Eventreceiver::isMMBDown() const
{
    return MMBIsDown_;
}



bool Eventreceiver::wasMMBDown() const
{
    return MMBWasDown_;
}



bool Eventreceiver::isRMBDown() const
{
    return RMBIsDown_;
}



bool Eventreceiver::wasRMBDown() const
{
    return RMBWasDown_;
}



bool Eventreceiver::isHover() const
{
    return hover_;
}



s32 Eventreceiver::getMouseX() const
{
    return mouseX_;
}



s32 Eventreceiver::getMouseY() const
{
    return mouseY_;
}



s32 Eventreceiver::getMouseLastX() const
{
    return mouseLastX_;
}



s32 Eventreceiver::getMouseLastY() const
{
    return mouseLastY_;
}



f32 Eventreceiver::getMouseWheel() const
{
    return mouseWheel_;
}



/* private */



Eventreceiver::Eventreceiver()
: reactOnKeys_(false),
  reactOnMouse_(false),
  reactOnGUI_(false),
  mouseX_(0),
  mouseLastX_(0),
  mouseY_(0),
  mouseLastY_(0),
  mouseWheel_(0.0f),
//  ShiftIsDown_(false),
//  ShiftWasDown_(false),
//  CtrlIsDown_(false),
//  CtrlWasDown_(false),
  LMBIsDown_(false),
  LMBWasDown_(false),
  MMBIsDown_(false),
  MMBWasDown_(false),
  RMBIsDown_(false),
  RMBWasDown_(false),
  hover_(false)
//  thereWasKeyEvent_(false)
{
    resetKeyStates();
}



Eventreceiver::~Eventreceiver()
{
    // nothing to do here
}



void Eventreceiver::resetKeyStates()
{
    for ( register u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i )
    {
        KeyIsDown_[ i ] = false;
        KeyLastState_[ i ] = false;
    }
    ShiftIsDown_ = false;
    ShiftWasDown_ = false;
    CtrlIsDown_ = false;
    CtrlWasDown_ = false;
    thereWasKeyEvent_ = false;
}



void Eventreceiver::resetMouseButtonStates()
{
    LMBIsDown_ = false;
    LMBWasDown_ = false;
    MMBIsDown_ = false;
    MMBWasDown_ = false;
    RMBIsDown_ = false;
    RMBWasDown_ = false;
    mouseWheel_ = 0.0f;
}



void Eventreceiver::resetGuiStates()
{
    hover_ = false;
}
