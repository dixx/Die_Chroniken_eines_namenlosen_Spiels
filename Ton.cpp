#include "Ton.h"
#include "GenericHelperMethods.h"
#include "Logfile.h"



Ton& Ton::getInstance( io::IFileSystem* fs )
{
    static Ton instance( fs );
    return instance;
}



void Ton::preload( const c8* filename )
{
    GenericHelperMethods::getInstance().validateFileExistence( filename );
    ISoundSource* snd = soundEngine_->addSoundSourceFromFile( filename, ESM_NO_STREAMING, true );
    if ( snd == 0 )
    {
        Logfile::getInstance().write( Logfile::DEBUG, "Sound-Datei ", filename );
        Logfile::getInstance().writeLine( Logfile::DEBUG, " konnte nicht geladen werden!" );
    }
    snd->getPlayLength(); // workaround for a may-be-bug in preloading
}



ISoundEngine* Ton::getSoundEngine() const
{
    return soundEngine_;
}



void Ton::playGUISound( const Sound_ID id )
{
    soundEngine_->play2D( sndGuiArray_[ id ].c_str() );
}



/* private */



Ton::Ton( io::IFileSystem* fs )
: soundEngine_(0),
  fileSystem_(fs)
{
    Logfile& log = Logfile::getInstance();
    if ( fileSystem_ == 0 )
        log.emergencyExit( "Dateisystem in [Ton] nicht mehr gefunden! Abbruch." );
    soundEngine_ = createIrrKlangDevice();
    if ( soundEngine_ == 0 )
        log.emergencyExit( "Sound-Entchen konnte nicht erstellt werden! Abbruch." );
    log.writeLine( Logfile::INFO, "Sound-Entchen erfolgreich erstellt." );
    log.writeLine( Logfile::INFO, "    Version: IrrKlang ", "1.4.0" );
    log.write( Logfile::INFO, "    Treiber: ", soundEngine_->getDriverName() );
    log.writeLine( Logfile::INFO, soundEngine_->isMultiThreaded() ? ", Multi-Fred" : "" );
    sndGuiArray_.clear();
    initAllSounds();
}



Ton::~Ton()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    sndGuiArray_.clear();
    if ( soundEngine_ != 0 )
    {
        soundEngine_->drop();
        soundEngine_ = 0;
    }
    Logfile::getInstance().writeLine( Logfile::INFO, "Sound-Entchen normal beendet." );
}



void Ton::initAllSounds()
{
    // Sound <150ms werden nicht korrekt wiedergegeben!
    for ( u32 i = 0; i < SND_COUNT; ++i )
        sndGuiArray_.push_back( "" );
    sndGuiArray_[ SND_GUI_HOVER ] = "SFX/Mund7.wav";
    sndGuiArray_[ SND_GUI_CLICKBUTTON ] = "SFX/Mund6.wav";
    for ( u32 i = 0; i < SND_COUNT; ++i )
        preload( sndGuiArray_[i].c_str() );
}
