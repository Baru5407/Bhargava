#include "vcb.h"

#include <cstring>

VCB::VCB() {
    blockNumber = 512;
    blockSize = 2;
    freeBlocksCoun = 511;
    freeBlocks.setBit(0);
}

void VCB::write(char *block) {
    memcpy(block, (char *)&blockNumber, sizeof(blockNumber));
    block = block + sizeof(blockNumber);
    memcpy(block, (char *)&blockSize, sizeof(blockSize));
    block = block + sizeof(blockSize);
    memcpy(block, (char *)&freeBlocksCoun, sizeof(freeBlocksCoun));
    block = block + sizeof(freeBlocksCoun);
    freeBlocks.write(block);
}

void VCB::read(char *block) {
    memcpy((char *)&blockNumber, block, sizeof(blockNumber));
    block = block + sizeof(blockNumber);
    memcpy((char *)&blockSize, block, sizeof(blockSize));
    block = block + sizeof(blockSize);
    memcpy((char *)&freeBlocksCoun, block, sizeof(freeBlocksCoun));
    block = block + sizeof(freeBlocksCoun);
    freeBlocks.read(block);

    freeBlocks.setBit(0);
}
