/*! \file Actions.h
 *  \brief Bietet Mappings von beliebigen Eingaben zu in-Game Aktionen.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef _LEVIATHAN_ACTIONS_HEADER
#define _LEVIATHAN_ACTIONS_HEADER

#include <irrlicht.h>
#include <cstdint>

namespace leviathan
{
    namespace input
    {

        /*! \class Actions Actions.h "Actions.h"
         *  \brief Mappings von Input zu Aktion
         */
        class Actions
        {

        public:

            /*! \brief Konstruktor.
             */
            Actions() = default;

            /*! \brief Destruktor.
             */
            ~Actions() = default;

            Actions( const Actions& ) = delete;
            Actions& operator=( const Actions& ) = delete;

            /*! \brief bla.
             *  \param :
             *  \return `true` wenn xxx, ansonsten `false`
             */
            bool inProgress( uint32_t id ) const;

            /*! \brief bla.
             *  \param :
             *  \return `true` wenn xxx, ansonsten `false`
             */
            bool inactive( uint32_t id ) const;

            /*! \brief bla.
             *  \param :
             *  \return `true` wenn xxx, ansonsten `false`
             */
            bool justStarted( uint32_t id ) const;

            /*! \brief bla.
             *  \param :
             *  \return `true` wenn xxx, ansonsten `false`
             */
            bool justStopped( uint32_t id ) const;

            /*! \brief bla.
             *  \param :
             *  \return `true` wenn xxx, ansonsten `false`
             */
            void mergeFromFile( const irr::io::path& fileName, const irr::io::IFileSystem* fileSystem = nullptr );

        private:

        };
    }
}

#endif
