/*! \file SaveGames.h
 *  \brief Klasse stellt Schnittstelle für Savegames bereit.
 */

#ifndef _SAVEGAMES_HEADER
#define _SAVEGAMES_HEADER

#include <irrlicht.h>

using namespace irr;

/*! \class SaveGames SaveGames.h "SaveGames.h"
 *  \brief Schnittstelle für Savegames.
 *  \note Instanzierung: `SaveGames* mySaveGames = new SaveGames();`\n Benutzen: `mySaveGames->load(...);`
 */
class SaveGames
{

public:

    /*! \brief Konstruktor.
     *  \param device (\a IrrlichtDevice*) Zeiger auf das Irrlicht-Entchen
     *  \return Zeiger auf das instanzierte Klassenobjekt
     */
    SaveGames( IrrlichtDevice* device );

	/*! \brief Destruktor
     */
	~SaveGames();

    /*! \brief Lädt ein Savegame.
     *  \param filename (\a u8*) Pfad und Dateiname des Savegames.
     *  \return -
     */
    void load( const io::path& filename );

    /*! \brief Schreibt ein Savegame.
     *  \param filename (\a u8*) Pfad und Dateiname des Savegames.
     *  \return -
     */
    void save( const io::path& filename );

    /*! \brief Findet das neueste Savegame. Natürlich im Ordner /SAVEGAMES.
     *  \param -
     *  \return \a io::path& Dateiname des neuesten Savegames, oder ""
     */
    const io::path& findNewest();

private:

    IrrlichtDevice* device_;
    io::IFileSystem* fs_;
    io::path savegameName_;
    io::path applicationDirectory_;
    io::path savegamesDirectory_;
    const u8 CURRENT_VERSION;

    SaveGames( const SaveGames& );
    SaveGames& operator=( const SaveGames& );

    template <typename T> inline T read( io::IReadFile* stream );
    core::stringc readString( io::IReadFile* stream );
    template <typename T> inline void write( io::IWriteFile* stream, const T& number );
    void writeString( io::IWriteFile* stream, const core::stringc& text );
    template <typename T> inline void skip( io::IReadFile* stream );
    inline void checkVersion( u8 version );
    u32 getTimestamp();

};

#endif
