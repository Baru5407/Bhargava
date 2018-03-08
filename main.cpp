#include "simplefilesystem.h"
#include "BlocksBitmap.h"
#include "fileinfo.h"

#include <fstream>
#include <iostream>
#include <cstring>
#include <stdlib.h>
using std::cout;
using std::endl;

int main() {
    BlocksBitmap b;
    b.setBit(9);
    cout << b.getBit(9) << " : " << b.getBit(290) << endl;
    b.clearBit(9);
    cout << b.getBit(9) << " : " << b.getBit(19) << endl;

    char block[500];
    FileInfo *info = new FileInfo();
    info->setFilename("bhargava konduru");
    info->size = 1;
    info->startBlockNumber = 16;
    info->write(block);

    std::ofstream outfile ("new.txt",std::ofstream::binary);
    outfile.write(block, sizeof(*info));

    SimpleFileSystem fs;

    cout << endl << "Block bitmap" << endl;
    for(int o = 0; o < 512; o++) {
        cout << fs.vcb->freeBlocks.getBit(o) << " ";
    }

    cout << endl << "Open file nagg.txt" << endl;
    int r = fs.create("nagg.txt", 2);
    fs.dumpToDisk();
    FCB * file = fs.open("nagg.txt");

    char *data = "Test writing";
    cout << "Write: " << data;
    fs.write(file, data, strlen(data));
    cout << endl << r << endl;
    cout << "Opened files after opening a file" << endl;
    fs.printOpenFiles();

    cout << endl << "Close file nagg.txt" << endl;
    fs.close(file);
    cout << "Opened files after closing a file" << endl;
    fs.printOpenFiles();

    cout << endl << "Oen file nagg.txt again" << endl;
    file = fs.open("nagg.txt");

    cout << "Opened files after opening a file" << endl;
    fs.printOpenFiles();

    char *new_data = (char *) malloc(90);
    cout << "Read from nagg.txt to varable new_data and length of 90" << endl;
    fs.read(file, new_data, 90);

    cout << "We got: \"" << new_data << "\" from nagg.txt" << endl;

    cout << endl << "Executing dir()" << endl;
    fs.dir();

    cout << endl << "Deleting nagg.txt" << endl;
    fs.deleteFile("nagg.txt");
    cout << endl << "Executing dir()" << endl;
    fs.dir();

    fs.dumpToDisk();
    return 0;
}
