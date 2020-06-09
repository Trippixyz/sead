#include <sead/seadDisposer.h>
#include <sead/seadHeapMgr.h>

namespace
{
const u32 cDestructedFlag = 1;

}  // namespace

namespace sead
{
IDisposer::IDisposer() : IDisposer(nullptr, HeapNullOption::UseSpecifiedOrContainHeap) {}

IDisposer::IDisposer(Heap* const disposer_heap, HeapNullOption option)
{
    mDisposerHeap = disposer_heap;
    if (mDisposerHeap)
    {
        mDisposerHeap->appendDisposer_(this);
        return;
    }

    switch (option)
    {
    case HeapNullOption::AlwaysUseSpecifiedHeap:
        SEAD_ASSERT(false, "disposer_heap must not be nullptr");
    case HeapNullOption::UseSpecifiedOrContainHeap:
        if (!sead::HeapMgr::sInstancePtr)
            return;
        mDisposerHeap = sead::HeapMgr::sInstancePtr->findContainHeap(this);
        if (mDisposerHeap)
            mDisposerHeap->appendDisposer_(this);
        return;
    case HeapNullOption::DoNotAppendDisposerIfNoHeapSpecified:
        return;
    case HeapNullOption::UseSpecifiedOrCurrentHeap:
        if (!sead::HeapMgr::sInstancePtr)
            return;
        mDisposerHeap = sead::HeapMgr::sInstancePtr->getCurrentHeap();
        if (mDisposerHeap)
            mDisposerHeap->appendDisposer_(this);
        return;
    default:
        SEAD_ASSERT(false, "illegal option[%d]", int(option));
        return;
    }
}

IDisposer::~IDisposer()
{
    if (*reinterpret_cast<size_t*>(&mDisposerHeap) != cDestructedFlag)
    {
        if (mDisposerHeap != NULL)
            mDisposerHeap->removeDisposer_(this);

        *reinterpret_cast<size_t*>(&mDisposerHeap) = cDestructedFlag;
    }
}

}  // namespace sead
