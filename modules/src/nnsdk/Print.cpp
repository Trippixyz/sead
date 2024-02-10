#include <nnsdk/Print.h>

#include "basis/seadRawPrint.h"
#include "symbol/seadStackSymbolResolver.h"

#include <nn/diag.h>

namespace sead::nnsdk
{

void PrintStackTrace(nn::os::UserExceptionInfo* exceptionInfo)
{
    system::Print("Stack trace:\n");

    u64 symbolAddr;
    char symbolName[0x100];

    if (!exceptionInfo->PC.x) {

        symbolAddr = 0;
    }
    else {

        symbolAddr = (u64)nn::diag::GetSymbolName(symbolName, 0x100, exceptionInfo->PC.x);
    }

    if (!StackSymbolResolver::isIllegalSymbolAddress(symbolAddr, exceptionInfo->PC.x)) {

        system::Print("  0x%p %s + 0x%zx\n", (void*)exceptionInfo->PC.x, symbolName, exceptionInfo->PC.x - symbolAddr);
    }
    else {

        system::Print("  0x%p (unknown)\n", (void*)exceptionInfo->PC.x);
    }

    if (exceptionInfo->FP.x) {

        for (size_t i = 0; i < 0x20; i++) {

            symbolAddr = (u64)nn::diag::GetSymbolName(symbolName, 0x100, exceptionInfo->PC.x);

            if (!StackSymbolResolver::isIllegalSymbolAddress(symbolAddr, exceptionInfo->PC.x)) {
                system::Print("  0x%p %s + 0x%zx\n", (void*)exceptionInfo->PC.x, symbolName, exceptionInfo->PC.x - symbolAddr);
            }
            else {
                system::Print("  0x%p (unknown)\n", (void*)exceptionInfo->PC.x);
            }
        }
    }

    system::Print("\n");
}

}