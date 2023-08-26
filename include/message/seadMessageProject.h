#pragma once

#include <heap/seadHeap.h>
#include <LibMessageStudio/include/projfile.h>

namespace sead
{

class MessageProject
{
public:
    virtual ~MessageProject();

    void initialize(void* prjData,sead::Heap* heap);
    void finalize();
    
    // Libms => LibMessageStudio
    static void* allocForLibms_(u64 size);
    static void freeForLibms_(void* ptr);

    LMS_ProjectBinary* getInitializeData();

    LMS_ProjectBinary* mProject;
    u32 mGradationColorCount;
    char unk[0x34];

    static Heap* sHeap;
};

}  // namespace sead
