#ifndef _Utils
#define _Utils

char* readFileToBuffer(char* path)
{
    filebuf *pbuf;
    ifstream filestr;
    long size;
    char * buffer;
    // 要读入整个文件，必须采用二进制打开 
    filestr.open (path, ios::binary);
    // 获取filestr对应buffer对象的指针 
    pbuf=filestr.rdbuf();
    
    // 调用buffer对象方法获取文件大小
    size=pbuf->pubseekoff (0,ios::end,ios::in);
    pbuf->pubseekpos (0,ios::in);
    
    // 分配内存空间
    buffer=new char[size];
    
    // 获取文件内容
    pbuf->sgetn (buffer,size);
    buffer[size-1]='\0';
    
    filestr.close();

    return buffer;
}

#endif