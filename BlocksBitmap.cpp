#include "BlocksBitmap.h"

#include <cstring>

BlocksBitmap::BlocksBitmap() {
    for(int i = 0; i < this->getBitsCount(); i++)
        this->clearBit(i);
}

void BlocksBitmap::setBit(int i) {
    bits[WORD_OFFSET(i)] |= (1 << BIT_OFFSET(i));
}

void BlocksBitmap::clearBit(int i) {
    bits[WORD_OFFSET(i)] &= ~(1 << BIT_OFFSET(i));
}

bool BlocksBitmap::getBit(int i) {
    char bit = bits[WORD_OFFSET(i)] & (1 << BIT_OFFSET(i));
    return (bool)(bit != 0);
}

void BlocksBitmap::write(char *block) {
    memcpy(block, bits, 64);
}

void BlocksBitmap::read(char *block) {
    memcpy(bits, block, 64);
}

int BlocksBitmap::getChunk(int size_in_blocks) {
    for(int i = 1; i < 512; i++) {
        if(!getBit(i)) {
            bool ok = true;
            for(int j = i; j < (i + size_in_blocks); j++) {
                if(getBit(j)) {
                    ok = false;
                    return -1; // break;
                }
            }
            if(ok)
                return i;
        }
    }
    return -1;
}
