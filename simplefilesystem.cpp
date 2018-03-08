#include "simplefilesystem.h"
#include "vcb.h"
#include "fcb.h"

#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <iostream>

#include <vector>
using std::vector;

#define BLOCK_SIZE 1024*1024

bool SimpleFileSystem::IsFirstRun = true;
char *SimpleFileSystem::block;
vector<FCB *> SimpleFileSystem::openFiles;

SimpleFileSystem::SimpleFileSystem() {
    if(SimpleFileSystem::IsFirstRun) {
        block = (char*)malloc(BLOCK_SIZE);
        for(int i = 0; i < BLOCK_SIZE; i++)
            block[i] = '\0';

        vcb = new VCB();
        vcb->write(block);
        vcb->freeBlocks.setBit(0);

        SimpleFileSystem::IsFirstRun = false;
    }
    else {
        vcb = new VCB();
        vcb->read(SimpleFileSystem::block);
    }
}

void SimpleFileSystem::dumpToDisk() {
    std::ofstream outfile ("disk.txt",std::ofstream::binary);
    outfile.write(SimpleFileSystem::block, BLOCK_SIZE);
    outfile.close();
}

void SimpleFileSystem::printOpenFiles()
{
    for(std::vector<FCB *>::iterator it = SimpleFileSystem::openFiles.begin(); it != SimpleFileSystem::openFiles.end(); ++it) {
        std::cout << std::endl << (*it)->size << " : " << (*it)->firstDataBlock << std::endl;
    }
}

int SimpleFileSystem::create(char *filename, short size) {
    if(strlen(filename) > 15) {
        return FILENAME_TOO_LONG;
    }

    int start_block_number = vcb->freeBlocks.getChunk(size);
    if(start_block_number == -1) {
        return NO_ENOUGH_CONTIGOUS_SPACE;
    }

    FileInfo info;
    memcpy(info.filename, filename, strlen(filename) + 1);
    info.startBlockNumber = start_block_number;
    info.size = size;

    char *tmp = block;
    tmp = tmp + sizeof(*vcb);

    bool ok = false;
    int position = -1;
    for(int t = sizeof(*vcb); t < 2*1024; t = t + sizeof(info)) {
        FileInfo inf;
        inf.read(tmp);
        if(inf.filename[0] == '\0') {
            ok = true;
            position = t;
            break;
        }
        tmp = tmp + sizeof(info);
    }
    if(!ok) {
        return FILE_COUNT_EXCEDED;
    }


    info.write(tmp);

    return 0;
}

FCB *SimpleFileSystem::open(char *filename) {
    if(strlen(filename) > 15) {
        return NULL;
    }
    FileInfo info;
//    memcpy(info.filename, filename, strlen(filename));
//    info.startBlockNumber = start_block_number;
//    info.size = size;

    char *tmp = block;
    tmp = tmp + sizeof(*vcb);

    bool ok = false;
    int position = -1;
    for(int t = sizeof(*vcb); t < 2*1024; t = t + sizeof(info)) {
        FileInfo inf;
        inf.read(tmp);
        if(strcmp(inf.filename,filename) == 0) {
            ok = true;
            position = t;
            break;
        }
        tmp = tmp + sizeof(info);
    }
    if(!ok) {
//        std::cout << std::endl << ":::::::::::::" << std::endl;
        return NULL;
    }


    info.read(tmp);
    FCB *fcb = new FCB();
    fcb->size = info.size;
    fcb->firstDataBlock = info.startBlockNumber;

    SimpleFileSystem::openFiles.push_back(fcb);

    return fcb;
}

void SimpleFileSystem::close(FCB *fcb) {
    for(std::vector<FCB *>::iterator it = SimpleFileSystem::openFiles.begin(); it != SimpleFileSystem::openFiles.end(); ++it) {
        if((*it) == fcb) {
            SimpleFileSystem::openFiles.erase(it);
            break;
        }
    }
    delete fcb;
}

int SimpleFileSystem::write(FCB *fcb, char *data, int length) {
    if(length == -1)
        length = strlen(data);
    char *tmp = SimpleFileSystem::block;
    tmp = tmp + (fcb->firstDataBlock) * 2 * 1024;
    memcpy(tmp, data, length);
//    std::cout << std::endl << "WRITING " << fcb->firstDataBlock; // << " : " << (SimpleFileSystem::block + (fcb->firstDataBlock) * BLOCK_SIZE);
    return length;
}

void SimpleFileSystem::read(FCB *fcb, char *data, int length = -1) {
    if(length == -1)
        length = strlen(data);
    char *tmp = SimpleFileSystem::block;
    tmp = tmp + (fcb->firstDataBlock) * 2 * 1024;
    memcpy(data, tmp, length);
//    std::cout << std::endl << "WRITING " << fcb->firstDataBlock; // << " : " << (SimpleFileSystem::block + (fcb->firstDataBlock) * BLOCK_SIZE);
//    return length;
}

void SimpleFileSystem::dir() {
    FileInfo info;
//    memcpy(info.filename, filename, strlen(filename) + 1);
//    info.startBlockNumber = start_block_number;
//    info.size = size;

    char *tmp = block;
    tmp = tmp + sizeof(*vcb);

    bool ok = false;
    int position = -1;
    for(int t = sizeof(*vcb); t < 2*1024; t = t + sizeof(info)) {
        FileInfo inf;
        inf.read(tmp);
        if(inf.filename[0] != '\0') {
            std::cout << "=======" << std::endl;
            std::cout << "File name: " << inf.filename << std::endl;
            std::cout << "File start block: " << inf.startBlockNumber << std::endl;
            std::cout << "File size: " << inf.size << std::endl;
            std::cout << "=======" << std::endl;
        }
        tmp = tmp + sizeof(info);
    }
}

void SimpleFileSystem::deleteFile(char *filename) {
    if(strlen(filename) > 15) {
        return;
    }
    FileInfo info;
//    memcpy(info.filename, filename, strlen(filename));
//    info.startBlockNumber = start_block_number;
//    info.size = size;

    char *tmp = block;
    tmp = tmp + sizeof(*vcb);

    bool ok = false;
    int position = -1;
    for(int t = sizeof(*vcb); t < 2*1024; t = t + sizeof(info)) {
        FileInfo inf;
        inf.read(tmp);
        if(strcmp(inf.filename,filename) == 0) {
            for(int u = 0; u < FILENAME_LENGTH; u++)
                inf.filename[u] = '\0';
            inf.size = 0;
            inf.startBlockNumber = 0;
            inf.write(tmp);
            break;
//            ok = true;
//            position = t;
            break;
        }
        tmp = tmp + sizeof(info);
    }
//    if(!ok) {
//        std::cout << std::endl << ":::::::::::::" << std::endl;
//        return NULL;
//    }


//    info.read(tmp);
//    FCB *fcb = new FCB();
//    fcb->size = info.size;
//    fcb->firstDataBlock = info.startBlockNumber;

//    SimpleFileSystem::openFiles.push_back(fcb);

}
