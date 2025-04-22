/*! \file ILevel.h
 *  \brief Bietet Zugriff auf die Repräsentation eines Levels.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_WORLD_ILEVEL_H
#define LEVIATHAN_PUBLIC_INTERFACES_WORLD_ILEVEL_H

namespace leviathan {
    namespace world {
        /*! \interface ILevel
         *  \brief Bietet Zugriff auf die Repräsentation eines Levels.
         */
        struct ILevel {
            virtual ~ILevel() {}

            /*! \brief Lädt ein Level aus einer YAML-Datei.
             *  \param fileName: Pfad der Level-Datei
             */
            virtual void loadFromFile(const char* fileName) = 0;
        };
    }
}

#endif
