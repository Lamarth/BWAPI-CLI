#include <BWAPI/Unit.h>

namespace BWAPI
{
    namespace Filter
    {
        bool NullImpl(Unit u){ return(true); }
        const PtrUnitFilter Null(NullImpl);
    }
}