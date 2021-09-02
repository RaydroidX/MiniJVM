#ifndef JVM_DATA_STRUCTS
#define JVM_DATA_STRUCTS
#endif

typedef  unsigned int u4;
typedef  unsigned int u2;
typedef  unsigned char u1;

struct Class_File_Format
{
    u4 magic_number; // 魔术0xcafebabe

    u2 minor_version;
    u2 major_version;

    u2 constant_pool_count; //常量个数

    cp_info constant_pool[0]; //常量池

    u2 access_flags; //访问权限标志

    u2 this_class; //当前类的类名
    u2 super_class; //父类类名

    u2 interface_cout;

    u2* interfaces;

    u2 field_count;
    filed_info fields[0];

    u2 methods_count;
    method_info methods[0];

    u2 attributes_count;
    attribute_info attributes[0];
};


struct cp_info
{
    u1 tag;  // 常量值类型
    u1 info[0]; //Each tag byte must be followed by two or more bytes giving information about the specific constant
};


/**
 * 不同java版本支持的类型有区别 待处理
 * */
enum CONSTANT_TYPE {
    CONSTANT_Class = 7,
    CONSTANT_Fieldref = 9,
    CONSTANT_Methodref = 10,
    CONSTANT_InterfaceMethodref = 11,
    CONSTANT_String = 8,
    CONSTANT_Integer = 3,
    CONSTANT_Float = 4,
    CONSTANT_Long = 5,
    CONSTANT_NameAndType = 12,
    CONSTANT_Utf8 = 1,
    CONSTANT_MethodHandle = 15,
    CONSTANT_MethodType = 16,
    CONSTANT_Dynamic = 17,
    CONSTANT_InvokeDynamic = 18,
    CONSTANT_Module = 19,
    CONSTANT_Package = 20,
};

struct CONSTANT_Class_info
{
    u1 tag = CONSTANT_Class; //对应于CONSTANT_TYPE中的 CONSTANT_Class = 7
    /**
     * encoded类名所在的index，其值为CONSTANT_Utf8_info类型；
     * eg. Thread[] is [Ljava/lang/Thread 
     * If the name of the method in a CONSTANT_Methodref_info structure begins with a '<' ('\u003c'), then the name must be the special name <init>
     **/
    u2 name_index;
};

struct CONSTANT_Fieldref_info
{
    u1 tag = CONSTANT_Fieldref;
    u2 class_index; //常量表中该index处的值对应CONSTANT_Class_info类型
    u2 name_and_type_index; //CONSTANT_NameAndType_info index；  indicates the name and descriptor of the field or method.
};

struct CONSTANT_Methodref_info
{
    u1 tag = CONSTANT_Methodref;
    u2 class_index; //
    u2 name_and_type_index;
};

struct CONSTANT_InterfaceMethodref_info
{
    u1 tag = CONSTANT_InterfaceMethodref;
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_String_info
{
    u1 tag = CONSTANT_String;

};




