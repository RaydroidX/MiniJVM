#include <ByteCodeInterpreter.hpp>
#include "Utils.h"
#include "data_structs.hpp"
#include "ClassFileStream.hpp"
#include <vector> 
using namespace std;

void ByteCodeInterpreter::printClassFile(char *filePath)
{
    Class_File_Format classFile;
    ClassFileStream cfs(filePath);
    
    int magic = 0xcafebabe;
    if (cfs.get_u4_fast() == magic) {
        classFile.magic_number = magic;
        cout << "魔数校验通过" << endl;
    }
    else
    {
        cerr << "这不是一个合法的class文件" << endl;
        return;
    }

    classFile.minor_version = cfs.get_u2_fast();
    classFile.major_version = cfs.get_u2_fast();

    dec(cout);
    cout << "class version " << classFile.major_version << "." << classFile.minor_version << endl;

    u2 count = cfs.get_u2_fast(); //常量的个数

    vector<void*> *cpInfos = new vector<void*>();

    for (int i=0; i<count; i++) {
        u1 tag = cfs.get_u1_fast();

        switch (tag)
        {
            case CONSTANT_Class:
            {
                CONSTANT_Class_info* cci = (CONSTANT_Class_info*) malloc(sizeof(CONSTANT_Class_info));
                cpInfos->push_back(cci);

                cci->name_index = cfs.get_u2_fast();
                break;
            };

            case CONSTANT_Fieldref:
            {
                CONSTANT_Fieldref_info* cci = (CONSTANT_Fieldref_info*) malloc(sizeof(CONSTANT_Fieldref_info));
                cpInfos->push_back(cci);

                cci->class_index = cfs.get_u2_fast();
                cci->name_and_type_index = cfs.get_u2_fast();
                break;
            }

            case CONSTANT_Methodref:
            {
                CONSTANT_Methodref_info* cci = (CONSTANT_Methodref_info*) malloc(sizeof(CONSTANT_Methodref_info));
                cpInfos->push_back(cci);

                cci->class_index = cfs.get_u2_fast();
                cci->name_and_type_index = cfs.get_u2_fast();
                break;
            }

            case CONSTANT_String:
            {
                CONSTANT_String_info* cci = (CONSTANT_String_info*) malloc(sizeof(CONSTANT_String_info));
                cpInfos->push_back(cci);

                cci->string_index = cfs.get_u2_fast();
                break;
            }

            case CONSTANT_Utf8:
            {
                int len = cfs.get_u2_fast();
                CONSTANT_Utf8_info* cci = (CONSTANT_Utf8_info*) malloc(sizeof(CONSTANT_Utf8_info) + len + 1);
                cpInfos->push_back(cci);
                cfs.copyBytes(cci->bytes, len);
                cci->bytes[len] = '\0';
                cci->length = len;

                break;
            }

            default:
            {
                break;
            }
            
        };
    }

    constants_info* constant_info = (constants_info*)malloc(sizeof(constants_info));
    
    return;
};