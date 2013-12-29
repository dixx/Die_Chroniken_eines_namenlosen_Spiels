#include "Logfile.h"



Logfile& Logfile::getInstance( io::IFileSystem* fs, const c8* filename,
        const u16 logginglevel ) 
{ 
    static Logfile _instance( fs, filename, logginglevel );
    return _instance; 
}



void Logfile::setNewFilesystem( io::IFileSystem* fs )
{
    if ( fs == 0 )
        exit( 1 );
    fs_ = fs;
    openLogfile();
    writeLine( DEBUG, "Logdatei auf neues Entchen umgehaengt." );
    closeLogfile();
}



void Logfile::write( const u16 logginglevel, const core::stringc& logline )
{
    if ( logginglevel <= globalLogLevel_ )
    {
        openLogfile();
        if ( logginglevel == DEBUG )
            logfile_->write( debugPrefix_.c_str(), debugPrefix_.size() );
        logfile_->write( logline.c_str(), logline.size() );
        closeLogfile();
    }
}



void Logfile::writeLine( const u16 logginglevel, const core::stringc& logline )
{
    if ( logginglevel <= globalLogLevel_ )
    {
        openLogfile();
        if ( logginglevel == DEBUG )
            logfile_->write( debugPrefix_.c_str(), debugPrefix_.size() );
        logfile_->write( logline.c_str(), logline.size() );
        logfile_->write( newLine_.c_str(), newLineSize_ );
        closeLogfile();
    }
}



void Logfile::emergencyExit( const core::stringc& logline )
{
    openLogfile();
    logfile_->write( logline.c_str(), logline.size() );
    logfile_->write( newLine_.c_str(), newLineSize_ );
    closeLogfile();
    exit( 1 );
}



/* private */



Logfile::Logfile( io::IFileSystem* fs, const c8* filename,
        const u16 logginglevel )
: filename_(filename),
  fs_(fs),
  logfile_(0),
  globalLogLevel_(logginglevel),
  newLine_("\r\n"),
  debugPrefix_("[debug] ")
{
    if ( fs_ == 0 )
        exit( 1 );
    logfile_ = fs_->createAndWriteFile( filename_ );
    if ( logfile_ == 0 )
        exit( 1 );
    newLineSize_ = newLine_.size();
    debugPrefixSize_ = debugPrefix_.size();
    writeLine( INFO, "Logdatei gestartet. LogLevel: ", globalLogLevel_ );
    writeLine( INFO, "" );
    closeLogfile();
}



Logfile::~Logfile()
{
    closeLogfile();
}
