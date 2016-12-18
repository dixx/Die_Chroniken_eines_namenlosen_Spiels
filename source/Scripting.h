/*! \file Scripting.h
 * \brief Klasse (Singleton) stellt Schnittstelle für die LUA-Scriptsprache bereit.
 */

#ifndef _SCRIPTING_HEADER
#define _SCRIPTING_HEADER

#include <irrlicht.h>
#include "lua.hpp"

/*! \class Scripting Scripting.h "Scripting.h"
 *  \brief  Schnittstelle für die LUA ScriptEngine.
 *  \attention Klasse ist `Singleton`.
 *  \note Instanzierung: `Scripting& myScripting = Scripting::getInstance();`
 *        \n Oder: `Scripting::getInstance();`
 *        \n Benutzen: `myScripting.runScriptFile( "EXECUTOR.LUA" );`
 *        \n Oder: `Scripting::getInstance().runScriptFile( "C.LUA" );`
 */
class Scripting
{

public:

    /*! \brief Ersatz für den Konstruktor.
     *
     *  Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
     *  \param -
     *  \return Referenz auf die einzige Instanz dieser Klasse
     */
    static Scripting& getInstance();

    /*! \brief Führt eine LUA-Scriptdatei aus.
     *  \param filename (\a c8*) Scriptdateiname
     *  \return -
     */
    void runScriptFile( const irr::c8* filename );

    /*! \brief Lädt Positionen, Dateinamen und Eigenschaften beliebiger Objekte aus einer Script-Datei.
     *  \param filename (\a c8*) Dateiname
     *  \return \a core::stringc Liste mit Positionen, Dateinamen und Eigenschaften der einzelnen Objekte
     */
    irr::core::stringc getObjectDataFromScript( const irr::c8* filename );

private:

    lua_State* luaVM_;
    irr::core::stringc nextStringValue_;
    irr::f32 nextFloatValue_;

    Scripting();  // ctor. Von außen keine Instanzen direkt erzeugbar
    Scripting( const Scripting& );  // Instanz ist nicht kopierbar
    Scripting& operator=( const Scripting& );  // Instanz ist nicht zuweisbar
    ~Scripting();  // dtor. Instanz zerstört sich bei Programmende

    inline void readNextStringValue();
    inline void readNextFloatValue();
    void errorHandler( const irr::s32 errorCode, const irr::c8* errorMessage );
    void addLuaSearchPath( const irr::c8* path );
    irr::core::stringc stackDump();

};

#endif
