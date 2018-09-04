#include "EventReceiver.h"

namespace leviathan
{
    namespace core
    {
        bool EventReceiver::OnEvent(const irr::SEvent& event)
        {
            (void)event;
            return false;
        }
    }
}
