#include "Actions.h"

namespace leviathan
{
    namespace input
    {
        bool Actions::inProgress( uint32_t id ) const {
            (void)id;
            return false;
        }

        bool Actions::inactive( uint32_t id ) const {
            return !inProgress( id );
        }

        bool Actions::justStarted( uint32_t id ) const {
            (void)id;
            return false;
        }

        bool Actions::justStopped( uint32_t id ) const {
            (void)id;
            return false;
        }

        void Actions::mergeFromFile( const irr::io::path& fileName, const irr::io::IFileSystem* fileSystem ) {
            (void)fileName;
            (void)fileSystem;
        }
    }
}
