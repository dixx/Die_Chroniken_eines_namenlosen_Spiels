#ifndef _IRRLICHT_DEVICE_MOCK_HEADER
#define _IRRLICHT_DEVICE_MOCK_HEADER

#include <irrlicht.h>
#include "IrrlichtTimerMock.h"

class IrrlichtDeviceMock : public irr::IrrlichtDevice
{
public:
    IrrlichtDeviceMock();
    virtual ~IrrlichtDeviceMock();
    // mocked methods
    virtual irr::ITimer* getTimer();
    virtual bool run();
    virtual bool isWindowActive() const;
    virtual void yield();
    // setter for mocked method default return values
    // TODO
    // setter for mocked method return values; these can be called multiple times for sequential returns
    void letRunReturn( bool ret );
    void letIsWindowActiveReturn( bool ret );
    // getter for how many times mocked method was called so far
    irr::u32 timesRunWasCalled();
    irr::u32 timesIsWindowActiveWasCalled();
    irr::u32 timesYieldWasCalled();
    // so far unused methods
    virtual void sleep(irr::u32 timeMs, bool pauseTimer=false) { (void)timeMs; (void)pauseTimer; };
    virtual irr::video::IVideoDriver* getVideoDriver() { return 0; };
    virtual irr::io::IFileSystem* getFileSystem() { return 0; };
    virtual irr::gui::IGUIEnvironment* getGUIEnvironment() { return 0; };
    virtual irr::scene::ISceneManager* getSceneManager() { return 0; };
    virtual irr::gui::ICursorControl* getCursorControl() { return 0; };
    virtual irr::ILogger* getLogger() { return 0; };
    virtual irr::video::IVideoModeList* getVideoModeList() { return 0; };
    virtual irr::IOSOperator* getOSOperator() { return 0; };
    virtual irr::IRandomizer* getRandomizer() const { return 0; };
    virtual void setRandomizer(irr::IRandomizer* r) { (void)r; };
    virtual irr::IRandomizer* createDefaultRandomizer() const { return 0; };
    virtual void setWindowCaption(const wchar_t* text) { (void)text; };
    virtual bool isWindowFocused() const { return false; };
    virtual bool isWindowMinimized() const { return false; };
    virtual bool isFullscreen() const { return false; };
    virtual irr::video::ECOLOR_FORMAT getColorFormat() const { return irr::video::ECF_UNKNOWN ; };
    virtual void closeDevice() {};
    virtual const irr::c8* getVersion() const { return ""; };
    virtual void setEventReceiver(irr::IEventReceiver* receiver) { (void)receiver; };
    virtual irr::IEventReceiver* getEventReceiver() { return 0; };
    virtual bool postEventFromUser(const irr::SEvent& event) { (void)event; return false; };
    virtual void setInputReceivingSceneManager(irr::scene::ISceneManager* sceneManager) { (void)sceneManager; };
    virtual void setResizable(bool resize=false) { (void)resize; };
    virtual void minimizeWindow() {};
    virtual void maximizeWindow() {};
    virtual void restoreWindow() {};
    virtual bool activateJoysticks(irr::core::array<irr::SJoystickInfo>& joystickInfo) { (void)joystickInfo; return false; };
    virtual bool setGammaRamp(irr::f32 red, irr::f32 green, irr::f32 blue, irr::f32 relativebrightness, irr::f32 relativecontrast) { (void)red; (void)green; (void)blue; (void)relativebrightness; (void)relativecontrast; return false; };
    virtual bool getGammaRamp(irr::f32 &red, irr::f32 &green, irr::f32 &blue, irr::f32 &brightness, irr::f32 &contrast) { (void)red; (void)green; (void)blue; (void)brightness; (void)contrast; return false; };
    virtual void clearSystemMessages() {};
    virtual irr::E_DEVICE_TYPE getType() const { return irr::EIDT_BEST ; };
private:
    IrrlichtTimerMock timer_;
    irr::core::list<bool> runReturn_;
    bool runReturnDefault_;
    irr::u32 runCallCount_;
    mutable irr::core::list<bool> isWindowActiveReturn_;
    mutable bool isWindowActiveReturnDefault_;
    mutable irr::u32 isWindowActiveCallCount_;
    irr::u32 yieldCallCount_;
};

#endif

// TODO this smells like a more generic mock class.
// - what has been the arguments?
// - how to check mocks within mocks?
