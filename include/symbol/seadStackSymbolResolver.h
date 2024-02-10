#pragma once

#ifdef NNSDK
#include <nn/os.h>
#endif

namespace sead
{
    namespace StackSymbolResolver
    {
        bool isIllegalSymbolAddress(u64, u64);
    }
}