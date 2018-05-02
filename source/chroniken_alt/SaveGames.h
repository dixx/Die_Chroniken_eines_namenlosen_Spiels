/*! \file SaveGames.h
 *  \brief Klasse stellt Schnittstelle für Savegames bereit.
 */

#ifndef _SAVEGAMES_HEADER
#define _SAVEGAMES_HEADER

#include <irrlicht.h>

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
    SaveGames( irr::IrrlichtDevice* device );

	/*! \brief Destruktor
     */
	~SaveGames();

    /*! \brief Lädt ein Savegame.
     *  \param filename (\a u8*) Pfad und Dateiname des Savegames.
     *  \return -
     */
    void load( const irr::io::path& filename );

    /*! \brief Schreibt ein Savegame.
     *  \param filename (\a u8*) Pfad und Dateiname des Savegames.
     *  \return -
     */
    void save( const irr::io::path& filename );

    /*! \brief Findet das neueste Savegame. Natürlich im Ordner /SAVEGAMES.
     *  \param -
     *  \return \a io::path& Dateiname des neuesten Savegames, oder ""
     */
    const irr::io::path& findNewest();

private:

    irr::IrrlichtDevice* device_;
    irr::io::IFileSystem* fs_;
    irr::io::path savegameName_;
    irr::io::path applicationDirectory_;
    irr::io::path savegamesDirectory_;
    const irr::u8 CURRENT_VERSION;

    SaveGames( const SaveGames& );
    SaveGames& operator=( const SaveGames& );

    template <typename T> inline T read( irr::io::IReadFile* stream );
    irr::core::stringc readString( irr::io::IReadFile* stream );
    template <typename T> inline void write( irr::io::IWriteFile* stream, const T& number );
    void writeString( irr::io::IWriteFile* stream, const irr::core::stringc& text );
    template <typename T> inline void skip( irr::io::IReadFile* stream );
    inline void checkVersion( irr::u8 version );
    irr::u32 getTimestamp();

};

#endif
