#pragma once

#ifdef NNSDK
#include <nn/os.h>
#endif

namespace sead
{
    namespace nnsdk
    {
        void PrintStackTrace(nn::os::UserExceptionInfo* exceptionInfo);
    }
}