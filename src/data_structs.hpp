/**
 * Created By Ray.Jiang on 2021/09/02
 * 229135609@qq.com
 * 参考https://docs.oracle.com/javase/specs/jvms/se8/html/jvms-4.html
 * */
#ifndef JVM_DATA_STRUCTS
#define JVM_DATA_STRUCTS
#endif

typedef  unsigned int u4;
typedef  unsigned int u2;
typedef  unsigned char u1;

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
    CONSTANT_Double = 6,
    CONSTANT_NameAndType = 12,
    CONSTANT_Utf8 = 1,
    CONSTANT_MethodHandle = 15,
    CONSTANT_MethodType = 16,
    //CONSTANT_Dynamic = 17,
    CONSTANT_InvokeDynamic = 18,
    //CONSTANT_Module = 19,
    //CONSTANT_Package = 20,
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
    u2 string_index;
};

struct CONSTANT_Integer_info
{
    u1 tag = CONSTANT_Integer;
    u4 bytes; //The bytes of the value are stored in big-endian (high byte first) order
};

/**
 * The value represented by the CONSTANT_Float_info structure is determined as follows. The bytes of the value are first converted into an int constant bits. Then:
 * If bits is 0x7f800000, the float value will be positive infinity.
 * If bits is 0xff800000, the float value will be negative infinity.
 * If bits is in the range 0x7f800001 through 0x7fffffff or in the range 0xff800001 through 0xffffffff, the float value will be NaN.
 * In all other cases, let s, e, and m be three values that might be computed from bits:
 * 
 * int s = ((bits >> 31) == 0) ? 1 : -1;
 * int e = ((bits >> 23) & 0xff);
 * int m = (e == 0) ? (bits & 0x7fffff) << 1 :(bits & 0x7fffff) | 0x800000;
 * 
 * Then the float value equals the result of the mathematical expression s · m · 2e-150.
 * */
struct CONSTANT_Float_info
{
    u1 tag = CONSTANT_Float;
    u4 bytes;//The bytes of the single format representation are stored in big-endian (high byte first) order.
};

struct CONSTANT_Long_info {
    u1 tag = CONSTANT_Long;
    /**
     * the long value is :  ((long) high_bytes << 32) + low_bytes
     * */
    u4 high_bytes; // stored in big-endian (high byte first) order.
    u4 low_bytes; 
};

/**
 * First let temp = ((long) high_bytes << 32) + low_bytes
 * Then:

        If bits is 0x7ff0000000000000L, the double value will be positive infinity.

        If bits is 0xfff0000000000000L, the double value will be negative infinity.

        If bits is in the range 0x7ff0000000000001L through 0x7fffffffffffffffL or in the range 0xfff0000000000001L through 0xffffffffffffffffL, the double value will be NaN.

        In all other cases, let s, e, and m be three values that might be computed from bits:

        int s = ((bits >> 63) == 0) ? 1 : -1;
        int e = (int)((bits >> 52) & 0x7ffL);
        long m = (e == 0) ? (bits & 0xfffffffffffffL) << 1 : (bits & 0xfffffffffffffL) | 0x10000000000000L;
	  
Then the floating-point value equals the double value of the mathematical expression s · m · 2e-1075.
 **/
struct CONSTANT_Double_info {
    u1 tag = CONSTANT_Double;
    u4 high_bytes;
    u4 low_bytes;
};

// Just used to refer to
enum Filed_Descriptor {
    B = 'B', //signed byte
    C = 'C', //Unicode character code point in the Basic Multilingual Plane, encoded with UTF-16
    D = 'D', //double
    F = 'F', //float
    I = 'I', //int
    J = 'J', //long
    S = 'S', //signed short
    Z = 'Z', // boolean
    ObjectType = 'L..;', //对象

    ArrayType = '[' //数组
};

struct CONSTANT_NameAndType_info {
    u1 tag = CONSTANT_NameAndType;
    u2 name_index; //The constant_pool entry at that index must be a CONSTANT_Utf8_info structure
    u2 descriptor_index; //The constant_pool entry at that index must be a CONSTANT_Utf8_info structure representing a valid field descriptor or method descriptor
};

struct CONSTANT_Utf8_info {
    u1 tag = CONSTANT_Utf8;
    u2 length;
    u1 bytes[0];
};

enum Reference_Kind {
    REF_getField = 1,
    REF_getStatic,
    REF_putField,
    REF_putStatic,
    REF_invokeVirtual,
    REF_invokeStatic,
    REF_invokeSpecial,
    REF_newInvokeSpecial,
    REF_invokeInterface,
};

//方法句柄？？
struct CONSTANT_MethodHandle_info {
    u1 tag = CONSTANT_MethodHandle;
    u1 reference_kind; // in the range 1 to 9. 表示方法句柄的类型，描述字节码的行为；
    u2 reference_index; 
};

struct CONSTANT_MethodType_info {
    u1 tag = CONSTANT_MethodType;
    u2 descriptor_index; //The constant_pool entry at that index must be a CONSTANT_Utf8_info structure (§4.4.7) representing a method descriptor
};

//https://docs.oracle.com/javase/specs/jvms/se8/html/jvms-4.html#jvms-4.4.10
// struct CONSTANT_Dynamic_info {
//     u1 tag = CONSTANT_Dynamic;
//     u2 bootstrap_method_attr_index;
//     u2 name_and_type_index;
// };

struct CONSTANT_InvokeDynamic_info {
    u1 tag = CONSTANT_InvokeDynamic;
    u2 bootstrap_method_attr_index; //索引指向the bootstrap_methods array of the bootstrap method table
    u2 name_and_type_index;
};

//从Java 9开始，JDK引入了模块（Module
//represent a module
// struct CONSTANT_Module_info {
//     u1 tag = CONSTANT_Module;
//     u2 name_index;
// };

// //represent a package exported or opened by a module
// struct CONSTANT_Package_info {
//     u1 tag = CONSTANT_Package;
//     u2 name_index;
// };
enum Method_Access_Flag {
    ACC_PUBLIC    = 0x0001,
    ACC_PRIVATE   = 0x0002,
    ACC_PROTECTED = 0x0004,
    ACC_STATIC    = 0x0008,
    ACC_FINAL     = 0x0010,
    ACC_SYNCHRONIZED = 0x0020,
    ACC_BRIDGE  = 0x0040, //桥接方法
    ACC_VARARGS = 0x0080, //可变参数
    ACC_NATIVE = 0x0100, //native方法
    ACC_ABSTRACT      = 0x0400,
    ACC_STRICT = 0x0800, //精确浮点  strictfp 关键字可应用于类、接口或方法。
    ACC_SYNTHETIC = 0x1000, //编译器自动生成，对Java源码来说是不可见的，但可以通过反射调用
};

enum Field_Access_Flag {
    FIELD_ACC_PUBLIC    = 0x0001,
    FIELD_ACC_PRIVATE   = 0x0002,
    FIELD_ACC_PROTECTED = 0x0004,
    FIELD_ACC_STATIC    = 0x0008,
    FIELD_ACC_FINAL     = 0x0010,
    FIELD_ACC_VOLATILE  = 0x0040,
    FIELD_ACC_TRANSIENT = 0x0080,
    FIELD_ACC_SYNTHETIC = 0x1000,
    FIELD_ACC_ENUM      = 0x4000,
};

struct attribute_info {
    u2 attribute_name_index;
    u4 attribute_length;
    u1 info[0];
};

/**
 * Table 4.5-A. Field access and property flags

    Flag Name	    Value	Interpretation
    ACC_PUBLIC	    0x0001	Declared public; may be accessed from outside its package.
    ACC_PRIVATE	    0x0002	Declared private; usable only within the defining class.
    ACC_PROTECTED	0x0004	Declared protected; may be accessed within subclasses.
    ACC_STATIC	    0x0008	Declared static.
    ACC_FINAL	    0x0010	Declared final; never directly assigned to after object construction (JLS §17.5).
    ACC_VOLATILE	0x0040	Declared volatile; cannot be cached.
    ACC_TRANSIENT	0x0080	Declared transient; not written or read by a persistent object manager.
    ACC_SYNTHETIC	0x1000	Declared synthetic; not present in the source code.
    ACC_ENUM	    0x4000	Declared as an element of an enum.
 * */
struct field_info {
    u2             access_flags; //访问限制
    u2             name_index; //名字索引
    u2             descriptor_index; // 指向类型签名的索引。 类型签名 eg. Ljava/lang/Thread;
    u2             attributes_count; //额外的属性数量
    attribute_info attributes[0];
};

struct method_info {
    u2             access_flags;
    u2             name_index;
    u2             descriptor_index; // 指向方法签名的索引。方法签名 eg.(IDLjava/lang/Thread;)Ljava/lang/Object;
    u2             attributes_count;
    attribute_info attributes[0];
};

/**
 *  Table 4.7-C. Predefined class file attributes (by location)

    Attribute	                                                                Location	class file

    SourceFile	                                                                ClassFile	45.3
    InnerClasses	                                                            ClassFile	45.3
    EnclosingMethod	                                                            ClassFile	49.0
    SourceDebugExtension                                                    	ClassFile	49.0
    BootstrapMethods                                                        	ClassFile	51.0
    ConstantValue                                                           	field_info	45.3
    Code	                                                                    method_info	45.3
    Exceptions	                                                                method_info	45.3
    RuntimeVisibleParameterAnnotations, RuntimeInvisibleParameterAnnotations	method_info	49.0
    AnnotationDefault	                                                        method_info	49.0
    MethodParameters	                                                        method_info	52.0
    Synthetic	                                                                ClassFile, field_info, method_info	45.3
    Deprecated	                                                                ClassFile, field_info, method_info	45.3
    Signature	                                                                ClassFile, field_info, method_info	49.0
    RuntimeVisibleAnnotations, RuntimeInvisibleAnnotations	                    ClassFile, field_info, method_info	49.0
    LineNumberTable	                                                            Code	45.3
    LocalVariableTable	                                                        Code	45.3
    LocalVariableTypeTable	                                                    Code	49.0
    StackMapTable	                                                            Code	50.0
    RuntimeVisibleTypeAnnotations, RuntimeInvisibleTypeAnnotations	            ClassFile, field_info, method_info, Code	52.0
 * 
 **/

struct exception_table
{
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
};

struct Code_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 code[0];
    u2 exception_table_length;
    exception_table exception_table[0];
    u2 attributes_count;
    attribute_info attributes[0];
};


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
    field_info fields[0];

    u2 methods_count;
    method_info methods[0];

    u2 attributes_count;
    attribute_info attributes[0];
};