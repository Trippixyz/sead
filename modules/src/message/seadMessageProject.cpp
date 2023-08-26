#include <message/seadMessageProject.h>

#include <LibMessageStudio/include/libms.h>

namespace sead
{

// not matching
void MessageProject::initialize(void* prjData,sead::Heap* heap)
{
    // set sHeap to heap
    sHeap = heap;

    LMS_SetMemFuncs(allocForLibms_, freeForLibms_);

    LMS_ProjectBinary* prjBinary = LMS_InitProject(prjData);

    mProject = prjBinary;

    LMS_SetMemFuncs(0, 0);

    // set sHeap to 0x0
    sHeap = 0;

    s32 colorNum = LMS_GetColorNum(prjBinary);

    if (colorNum > 0) {

    }
}

}