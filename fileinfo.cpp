#include "fileinfo.h"

#include <cstring>
#include <iostream>

void FileInfo::write(char *block) {
    memcpy(block, filename, sizeof(filename)+1);
    block = block + FILENAME_LENGTH;
//    std::cout << block;
    memcpy(block, (char *)&startBlockNumber, sizeof(startBlockNumber));
    block = block + sizeof(startBlockNumber);
    memcpy(block, (char *)&size, sizeof(size));
}

void FileInfo::read(char *block)
{
    memcpy(filename, block, FILENAME_LENGTH);
    block = block + FILENAME_LENGTH;
    memcpy((char *)&startBlockNumber, block, sizeof(startBlockNumber));
    block = block + sizeof(startBlockNumber);
    memcpy((char *)&size, block, sizeof(size));
}

void FileInfo::setFilename(const char *f) {
    memcpy(filename, f, strlen(f));
    filename[strlen(f)] = '\0';
//    filename[strlen(f) + 1] = '\0';
}
