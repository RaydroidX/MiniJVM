#include <ByteCodeInterpreter.hpp>
#include "Utils.h"

void ByteCodeInterpreter::printClassFile(char *filePath)
{
    bool isBig = isBigEnd() == 1;
    Class_File_Format classFile;
    ifstream ifs;
    ifs.open(filePath, ios::in);
    ifs.read((char*)&(classFile.magic_number), 4);
    int magic = 0xcafebabe;
    if (!isBig) {
        endianSwap((u1*)&magic, 0, 4);
    }
    if (classFile.magic_number == magic) {
        cout << "魔数校验通过" << endl;
    } 
    else
    {
        cerr << "这不是一个合法的class文件" << endl;
        ifs.close();
        return;
    }
    
    ifs.close();
    return;
};