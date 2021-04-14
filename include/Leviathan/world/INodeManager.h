/*! \file INodeManager.h
 *  \brief Erstellt und verwaltet alle geometrischen Objekte und deren Attribute.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_WORLD_NODE_MANAGER_H
#define LEVIATHAN_PUBLIC_INTERFACES_WORLD_NODE_MANAGER_H

#include "../video/Vector3D.h"
#include "INode3D.h"

namespace leviathan {
    namespace world {

        /*! \interface INodeManager
         *  \brief Erstellt und verwaltet alle geometrischen Objekte und deren Attribute.
         */
        class INodeManager {
        public:
            /*! \brief Erstellt ein 3D-Objekt.
             *  \note  Notwendige Transformationen werden beim Erstellen ausgeführt.
             *  \param fileName: Name und Pfad der Mesh-Datei
             *  \param position: Position innerhalb der Welt, relativ zu Elternknoten
             *  \param offset: Translation relativ zur Position
             *  \param rotation: Rotation relativ zur Position
             *  \param scale: Skalierung
             */
            virtual INode3D& add3DNode(const char* fileName, video::Position3D position, video::Vector3D offset,
                video::Rotation3D rotation, video::Scale3D scale) = 0;

            /*! \brief Entfernt alle Objekte aus dem Spiel und gibt den Speicher frei.
             */
            virtual void unload() = 0;

        protected:
            /*! \brief Destruktor.
             *  \note Instanzen abgeleiteter Klassen können mittels dieses Interfaces nicht zerstört werden.
             */
            ~INodeManager() = default;
        };
    }
}
#endif
