//
// Created by erik9 on 4/28/2024.
//

#ifndef MEMORY_H
#define MEMORY_H
#include "datatypes/Patch.h"

namespace memory {
    unsigned char *CreateDetour(unsigned char *startAddress, unsigned char *newAddress);

    /// Last 4 or 8 bytes of the patch should be 0x90 (NOP) and will be replaced with the return address
    void CreatePatch(unsigned char *address, const datatypes::Patch& patch);
}


#endif //MEMORY_H
