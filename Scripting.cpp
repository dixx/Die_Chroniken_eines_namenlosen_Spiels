#include "Scripting.h"
#include "Logfile.h"
#include "GenericHelperMethods.h"

#define NO_ARGS 0
#define TAKES_ARGS 1
#define NO_RETURN_VALUE 0
#define RETURNS_VALUE 1
#define NO_ERROR_CALLBACK 0



Scripting& Scripting::getInstance()
{
    static Scripting instance;
    return instance;
}



void Scripting::runScriptFile( const c8* filename )
{
    // LUA-Scriptdatei wird geladen
    errorHandler( luaL_loadfile( luaVM_, filename ), filename );
    // geladene Scriptdatei wird ausgeführt
    errorHandler( lua_pcall( luaVM_, NO_ARGS, NO_RETURN_VALUE, NO_ERROR_CALLBACK ), "runScriptFile()" );
}



core::stringc Scripting::getObjectDataFromScript( const c8* filename )
{
    lua_getglobal( luaVM_, "getObjectDataFromScript" );
    lua_pushstring( luaVM_, filename );
    errorHandler(
            lua_pcall( luaVM_, TAKES_ARGS, RETURNS_VALUE, NO_ERROR_CALLBACK ),
            "Scripting::getObjectDataFromScript()"
    );
    if ( lua_istable( luaVM_, lua_gettop( luaVM_ ) ) == 0 )
    {
        lua_close( luaVM_ );
        luaVM_ = 0;
        Logfile::getInstance().emergencyExit(
                "[Script-VM]: LUA_LOADER::getObjectDataFromScript() hat kein Table geliefert! Abbruch." );
    }
    core::stringc entry = "";
    core::stringc data = "";
    bool readTuples = false;
    bool valueFound = false;
    lua_pushnil( luaVM_ );
    while ( lua_next( luaVM_, -2 ) != 0 )
    {
        entry = lua_tolstring( luaVM_, -1, 0 );  // Wert vom Stack lesen
        lua_pop( luaVM_, 1 );  // Wert vom Stack entfernen
        if ( entry == "START_OBJECT" )
        {
            readTuples = true;
            continue;
        }
        else if ( entry == "ENDE_OBJECT" )
        {
            readTuples = false;
            data += '\n';
            continue;
        }
        if ( readTuples )
        {
            valueFound = true;
            readNextStringValue();
            if ( entry == "MESH_DATEI" )
                data += "MFILE";
            else if ( entry == "POSITION" )
                data += "POSXZ";
            else if ( entry == "NAME" )
                data += "ONAME";
            else if ( entry == "TYP" )
                data += "OTYPE";
            else if ( entry == "TEXTUR" )
                data += "MTEX0";
            else if ( entry == "SKALIERUNG" )
                data += "MSCAL";
            else if ( entry == "OFFSET" )
                data += "MOFFS";
            else if ( entry == "ROTATION" )
                data += "MROTA";
            else
                valueFound = false;

            if ( valueFound )
            {
                data += nextStringValue_;
                data += "@";
            }
        }
    }
    while ( lua_gettop( luaVM_ ) )
        lua_pop( luaVM_, 1 );
    return data;
}



/* private */



Scripting::Scripting()
: nextStringValue_(""),
  nextFloatValue_(0.0f)
{
    // DEPRECATED since 5.1:
    //luaVM_ = lua_open();
    luaVM_ = luaL_newstate();
    if ( !luaVM_ )
        Logfile::getInstance().emergencyExit( "LUA Script-VM konnte nicht gestartet werden! Abbruch." );
    luaL_openlibs( luaVM_ );  // LUA-Libs werden geladen
    addLuaSearchPath( "/SCRIPTS/" );  // Suchpfad für Scriptdateien in LUA
    runScriptFile( "SCRIPTS/LUA_LOADER.LUA" );
    Logfile::getInstance().writeLine( Logfile::INFO, "Script-VM gestartet." );
    Logfile::getInstance().writeLine( Logfile::DETAIL, "    Version: ", LUA_VERSION );
}



Scripting::~Scripting()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    if ( luaVM_ != 0 )
    {
        lua_close( luaVM_ );
        luaVM_ = 0;
    }
    Logfile::getInstance().writeLine( Logfile::INFO, "Script-VM normal beendet." );
}



void Scripting::readNextStringValue()
{
    if ( lua_next( luaVM_, -2 ) != 0 )
    {
        if ( lua_isstring( luaVM_, -1 ) )
            nextStringValue_ = lua_tolstring( luaVM_, -1, 0 );
        lua_pop( luaVM_, 1 );
    }
    else
    {
        nextStringValue_ = "";
    }
}



void Scripting::readNextFloatValue()
{
    if ( lua_next( luaVM_, -2 ) != 0 )
    {
        if ( lua_isnumber( luaVM_, -1 ) )
            nextFloatValue_ = static_cast<f32>( lua_tonumber( luaVM_, -1 ) );
        lua_pop( luaVM_, 1 );
    }
    else
    {
        nextFloatValue_ = 0.0f;
    }
}



void Scripting::errorHandler( const s32 errorCode, const c8* errorMessage )
{
    if ( errorCode != 0 )
    {
        core::stringc completeErrorMessage = errorMessage;
        completeErrorMessage += ": ";
        switch ( errorCode )
        {
            case 1:
                completeErrorMessage += "LUA_YIELD, keine Ahnung.";
                break;
            case 2:
                completeErrorMessage += "Laufzeitfehler!";
                break;
            case 3:
                completeErrorMessage += "Syntaxfehler!";
                break;
            case 4:
                completeErrorMessage += "Speicherzugriffsfehler!";
                break;
            case 5:
                completeErrorMessage +=
                        "...haha! Fehler in Fehlerbehandlungsroutine!";
                break;
            case 6:
                completeErrorMessage += "Datei konnte nicht gelesen werden!";
                break;
            default:
                completeErrorMessage += "Unbekannter LUA-Fehler: ";
                completeErrorMessage += errorCode;
                completeErrorMessage += '!';
                break;
        }
        Logfile::getInstance().writeLine( Logfile::INFO, "[Script-VM]: ", completeErrorMessage.c_str() );
        Logfile::getInstance().writeLine( Logfile::INFO, "[Script-VM]: ", lua_tolstring( luaVM_, -1, 0 ) );
        lua_pop( luaVM_, 1 );
        Logfile::getInstance().writeLine( Logfile::INFO, "[Script-VM]: ", stackDump() );
        lua_close( luaVM_ );
        luaVM_ = 0;
        Logfile::getInstance().emergencyExit( "[Script-VM]: Abbruch." );
    }
}



void Scripting::addLuaSearchPath( const c8* path )
{
    lua_getglobal( luaVM_, "package" );
    lua_getfield( luaVM_, -1, "path" );
    core::stringc newPath = lua_tolstring( luaVM_, -1, 0 );
    newPath += ";.";
    newPath += path;
    newPath += "?.LUA;";
    lua_pop( luaVM_, 1 );
    lua_pushstring( luaVM_, newPath.c_str() );
    lua_setfield( luaVM_, -2, "path" );
    lua_pop( luaVM_, 1 );
}



core::stringc Scripting::stackDump()
{
    s32 items = lua_gettop( luaVM_ );
    if ( items == 0 )
        return "--- Stack is empty ---";
    core::stringc message = "--- Stack Dump ---\n";
    message += "total in stack: ";
    message += items;
    message += "\n";
    for ( register s32 i = 1; i <= lua_gettop( luaVM_ ); ++i )
    {
        switch ( lua_type( luaVM_, i ) )
        {
            case LUA_TSTRING:
                message += "string: '";
                message += lua_tolstring( luaVM_, i, 0 );
                message += '\'';
                break;
            case LUA_TBOOLEAN:
                message += "boolean '";
                message += lua_toboolean( luaVM_, i ) ? "true" : "false";
                message += '\'';
                break;
            case LUA_TNUMBER:
                message += "number: '";
                message += lua_tonumber( luaVM_, i );
                message += '\'';
                break;
            default:
                message += lua_typename( luaVM_, lua_type( luaVM_, i ) );
                if ( lua_isthread( luaVM_, i ) )
                    message += "  ...which is a thread.";
                if ( lua_isuserdata( luaVM_, i ) )
                    message += "  ...which is user data ?!?";
                break;
        }
        if ( lua_isnone( luaVM_, i ) )
            message += "  ...WHICH IS OUTSIDE THE STACK!";
        message += "\n  ";
    }
    message += "--- Ende Stack Dump ---";
    return message;
}
