
class ClassFileStream
{
    private:
    u1*   _buffer_start; // Buffer bottom
    u1*   _buffer_end;   // Buffer top (one past last element)
    u1*   _current;      // Current buffer position
    long size = 0;
    //char* _source;       // Source of stream (directory name, ZIP/JAR archive name)

    public:
    // Constructor
    ClassFileStream(char* filePath)
    {
        filebuf *pbuf;
        ifstream filestr;
        u1 * buffer;
        // 要读入整个文件，必须采用二进制打开 
        filestr.open (filePath, ios::binary);
        // 获取filestr对应buffer对象的指针 
        pbuf=filestr.rdbuf();
        
        // 调用buffer对象方法获取文件大小
        size=pbuf->pubseekoff (0,ios::end,ios::in);
        pbuf->pubseekpos (0,ios::in);
        
        // 分配内存空间
        buffer = (u1*)malloc(size);
        _current = buffer;
        _buffer_start = buffer;
        // 获取文件内容
        pbuf->sgetn ((char*)buffer,size);
        buffer[size-1]='\0';
        _buffer_end = buffer+size-1;
        
        filestr.close();
    }

    ~ClassFileStream()
    {
        delete _buffer_start;
    }

    u1 get_u1_fast() {
        return *_current++;
    }

    // Read u2 from stream
    u2 get_u2_fast() {
        u2 res = Bytes::get_Java_u2(_current);
        _current += 2;
        return res;
    }

    // Read u4 from stream
    u4 get_u4_fast() {
        u4 res = Bytes::get_Java_u4(_current);
        _current += 4;
        return res;
    }

    // Get direct pointer into stream at current position.
    // Returns NULL if length elements are not remaining. The caller is
    // responsible for calling skip below if buffer contents is used.
    u1* get_u1_buffer() {
        return _current;
    }

    u2* get_u2_buffer() {
        return (u2*) _current;
    }

    // Skip length u1 or u2 elements from stream
    void skip_u1_fast(int length) {
        _current += length;
    }

    void skip_u2_fast(int length) {
        _current += 2 * length;
    }

    void skip_u4_fast(int length) {
        _current += 4 * length;
    }

    // Tells whether eos is reached
    bool at_eos() const          { return _current == _buffer_end; }

    void copyBytes(u1* to, int bytecount)
    {
        memcpy(to, _current, bytecount);
        _current += bytecount;
    }
};