#include "Weather.h"
#include "Configuration.h"
#include "Constants.h"
#include "Logfile.h"
#include "ObjectManager.h"
#include "TimerManager.h"
#ifdef _DEBUG_MODE
#include "Debugwindow.h"
#endif



Weather& Weather::getInstance( scene::ISceneManager* smgr )
{
    static Weather instance( smgr );
    return instance;
}



void Weather::load()
{
    fogDensity_ = 0.01f;
    lightRadius_ = 1.0f;
    currentDayTime_ = SUNCYCLEDURATION_ / 2;  // mittags
    currentMoonPhase_ = 0;  // Neumond
    seasonOffsetY_ = 0.3f;  // Sommer
    updateTimer_->start();
    updateTimer_->tick( updateTimer_->getMaxValue() + 1.0f );
    smgr_->setShadowColor( video::SColor( 50, 0, 0, 0 ) );
    calculateSunMoonCirclesY();
    setFog();
    createLights();
    calculateLightValues();
}



void Weather::unload()
{
    updateTimer_->stop();
    for ( register u32 i = 0; i < 7; ++i )
        dayLightSource_[i]->remove();
}



const video::SColor& Weather::getSkyColor() const
{
    return skyColor_;
}



void Weather::update()
{
    if ( updateTimer_->isFull() )
    {
        currentDayTime_ += FACTOR_V2R_SEC_ * updateTimer_->getMaxValue();
        if ( currentDayTime_ >= SUNCYCLEDURATION_ )
            currentDayTime_ -= SUNCYCLEDURATION_;
        currentMoonPhase_ += FACTOR_V2R_SEC_ * updateTimer_->getMaxValue();
        if ( currentMoonPhase_ >= MOONCYCLEDURATION_ )
            currentMoonPhase_ -= MOONCYCLEDURATION_;
        calculateSunMoonCirclesY();
        calculateLightValues();
        setFog();
        updateTimer_->restart();
    }
#ifdef _DEBUG_MODE
    Debugwindow::getInstance().addLine( L"SunMoonCircle.Y:  ", sunCircleY_[6], moonCircleY_[6] );
#endif
}



f32 Weather::getDayTime() const
{
    return currentDayTime_;
}



f32 Weather::getMoonPhase() const
{
    return currentMoonPhase_;
}



/* private */



Weather::Weather( scene::ISceneManager* smgr )
: SUNCYCLEDURATION_(240000.0f),
  MOONCYCLEDURATION_(330000.0f),
  smgr_(smgr),
  fogDensity_(0.0f),
  lightRadius_(0.0f),
  currentDayTime_(0.0f),
  currentMoonPhase_(0.0f),
  seasonOffsetY_(0.0f),
  skyColor_(COL_PURPLE)
{
    if ( smgr_ == 0 )
        Logfile::getInstance().emergencyExit( "ScenenManager in [Weather] nicht mehr gefunden! Abbruch." );
    SUNMOVEMENTDELTA_ = ( core::PI * 2 ) / SUNCYCLEDURATION_;
    MOONMOVEMENTDELTA_ = ( core::PI * 2 ) / MOONCYCLEDURATION_;
    FACTOR_V2R_SEC_ = SUNCYCLEDURATION_ / 7200;
    updateTimer_ = TimerManager::getInstance().createTimer( 0.10f );
    clearArrays();
    for ( register u32 i = 0; i < 7; ++i )
    {
        dayLightSource_.push_back( 0 );
        sunCircleY_.push_back( 0.0f );
        moonCircleY_.push_back( 0.0f );
    }
}



Weather::~Weather()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    clearArrays();
    TimerManager::getInstance().removeTimer( updateTimer_ );
}



void Weather::calculateSunMoonCirclesY()
{
    // Sonnen-Kreis "anheben" fuer laengere Zeit Tageslicht
    f32 currentSunPosition = SUNMOVEMENTDELTA_ * currentDayTime_;
    f32 currentMoonPosition = MOONMOVEMENTDELTA_ * currentMoonPhase_;
    sunCircleY_[0] = static_cast<f32>( sin( currentSunPosition - core::HALF_PI * 1.4f ) );
    sunCircleY_[1] = static_cast<f32>( sin( currentSunPosition - core::HALF_PI * 1.2f ) );
    sunCircleY_[5] = static_cast<f32>( sin( currentSunPosition - core::HALF_PI * 1.2f ) );
    sunCircleY_[6] = static_cast<f32>( sin( currentSunPosition - core::HALF_PI ) );
    sunCircleY_[2] = static_cast<f32>( sin( currentSunPosition - core::HALF_PI * 0.8f ) );
    sunCircleY_[4] = static_cast<f32>( sin( currentSunPosition - core::HALF_PI * 0.8f ) );
    sunCircleY_[3] = static_cast<f32>( sin( currentSunPosition - core::HALF_PI * 0.6f ) );
    moonCircleY_[0] = static_cast<f32>( sin( currentMoonPosition - core::HALF_PI * 1.4f ) );
    moonCircleY_[1] = static_cast<f32>( sin( currentMoonPosition - core::HALF_PI * 1.2f ) );
    moonCircleY_[5] = static_cast<f32>( sin( currentMoonPosition - core::HALF_PI * 1.2f ) );
    moonCircleY_[6] = static_cast<f32>( sin( currentMoonPosition - core::HALF_PI ) );
    moonCircleY_[2] = static_cast<f32>( sin( currentMoonPosition - core::HALF_PI * 0.8f ) );
    moonCircleY_[4] = static_cast<f32>( sin( currentMoonPosition - core::HALF_PI * 0.8f ) );
    moonCircleY_[3] = static_cast<f32>( sin( currentMoonPosition - core::HALF_PI * 0.6f ) );
}



void Weather::setFog()
{
    smgr_->getVideoDriver()->setFog(
            skyColor_,
            video::EFT_FOG_LINEAR,
            Configuration::getInstance().getFarValue() * 0.3f,
            Configuration::getInstance().getFarValue() * 0.9f,
            fogDensity_,
            false,  // PixelFog, false==VertexFog
            true  // RangeFog (radial)
    );
}



void Weather::createLights()
{
    for ( register u32 i = 0; i < 7; ++i )
    {
        dayLightSource_[i] = smgr_->addLightSceneNode(
                ObjectManager::getInstance().weatherNodes,
                core::vector3df( 0.0f, 0.0f, 0.0f ),
                video::SColorf( 1.0f, 1.0f, 1.0f ),
                lightRadius_,
                ID_WELTBELEUCHTUNG
        );
        dayLightSource_[i]->setName( "Weltlicht" );
        dayLightSource_[i]->setLightType( video::ELT_DIRECTIONAL );
        dayLightSource_[i]->enableCastShadow( false );
        dayLightSource_[i]->setVisible( true );
        dayLightSource_[i]->setRotation(
                ( i < 6 )
                ? core::vector3df( 0.0f, 60.0f * static_cast<f32>( i ), 0.0f )
                : core::vector3df( 90.0f, 0.0f, 0.0f )
        );
    }
}



void Weather::calculateLightValues()
{
    video::SColorf lightColorSun;
    video::SColorf lightColorMoon;
    if ( sunCircleY_[6] > -0.05f )
    {
        lightColorSun.r = 1.0f * sunCircleY_[6];
        skyColor_.setBlue( static_cast<u32>( core::min_( 300 * ( sunCircleY_[6] + 0.05f ), 255.0f ) ) );
        if ( sunCircleY_[6] > 0.1f )
        {
            lightColorSun.g = 0.8f * ( sunCircleY_[6] - 0.1f );
            skyColor_.setRed( static_cast<u32>( core::min_( 60 * ( sunCircleY_[6] - 0.1f ), 50.0f ) ) );
            if ( sunCircleY_[6] > 0.2f )
            {
                lightColorSun.b = 0.8f * ( sunCircleY_[6] - 0.2f );
                skyColor_.setGreen( static_cast<u32>( core::min_( 244 * ( sunCircleY_[6] - 0.2f ), 170.0f ) ) );
            }
        }
    }
    else
    {
        lightColorSun = video::SColorf();
        skyColor_ = COL_BLACK;
    }
    if ( moonCircleY_[6] > 0.1f )
    {
        lightColorMoon.r = 0.02f + core::min_( 0.22f * ( moonCircleY_[6] - 0.1f ), 0.18f );
        lightColorMoon.g = 0.02f + core::min_( 0.22f * ( moonCircleY_[6] - 0.1f ), 0.18f );
        lightColorMoon.b = 0.08f + core::min_( 0.38f * ( moonCircleY_[6] - 0.1f ), 0.32f );
    }
    else
    {
        lightColorMoon = video::SColorf( 0.02f, 0.02f, 0.08f );
    }
    for ( register u32 i = 0; i < 7; ++i )
    {
        video::SLight& lightData = dayLightSource_[i]->getLightData();
        lightData.DiffuseColor = video::SColorf(
                core::max_( lightColorSun.r * sunCircleY_[i], lightColorMoon.r * moonCircleY_[i], 0.02f ),
                core::max_( lightColorSun.g * sunCircleY_[i], lightColorMoon.g * moonCircleY_[i], 0.02f ),
                core::max_( lightColorSun.b * sunCircleY_[i], lightColorMoon.b * moonCircleY_[i], 0.08f )
        );
        //lightData.AmbientColor = video::SColorf( 0.1f, 0.0f, 0.2f, 1.0f );
        lightData.SpecularColor = video::SColorf(
                lightData.DiffuseColor.r * 0.1f,
                lightData.DiffuseColor.g * 0.1f,
                lightData.DiffuseColor.b * 0.1f
        );
    }
}



void Weather::clearArrays()
{
    dayLightSource_.clear();
    sunCircleY_.clear();
    moonCircleY_.clear();
}
