/*! \file ILevel.h
 *  \brief Bietet Zugriff auf die Repräsentation eines Levels.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_WORLD_ILEVEL_H
#define LEVIATHAN_PUBLIC_INTERFACES_WORLD_ILEVEL_H

namespace leviathan {
    namespace video {
        struct Vector3D;
        using Position3D = Vector3D;
    }

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

            /*! \brief Gibt die aus einer Level-Datei gelesene Spawn-Position zurück, oder (0, 0, 0)
             */
            virtual const leviathan::video::Position3D& getSpawnPosition() const = 0;
        };
    }
}

#endif
