#include <iostream>
#include "ByteCodeInterpreter.hpp"

using namespace std;
int main(int argc, char *argv[]) {
    if (argc < 2)
    {
        cout << "请输入字节码文件路径作为参数" << endl;
        return -1;
    }
    cout << argv[1] << endl;
    ByteCodeInterpreter byteCodeInterpreter;
    byteCodeInterpreter.printClassFile(argv[1]);
    return 0;
}