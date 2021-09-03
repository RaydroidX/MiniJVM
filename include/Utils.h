#ifndef _Utils
#define _Utils

#include "data_structs.hpp"

int isBigEnd();
void use_endianSwap(u1 *pData);
void endianSwap(u1 *pData, int startIndex, int length);


//大端转小端
void endianSwap(u1 *pData, int startIndex, int length) {
    int i, cnt, end, start;
    cnt = length / 2;
    start = startIndex;
    end  = startIndex + length - 1;
    u1 tmp;
    for (i = 0; i < cnt; i++) {
        tmp            = pData[start + i];
        pData[start + i] = pData[end - i];
        pData[end - i]   = tmp;
    }
}
void use_endianSwap(u1 *pData) {
    for (int i = 0; i < 4; i += 4) {
        endianSwap(pData, i, 4);
    }
}

union w
 {
  int a;  //4 bytes
  char b; //1 byte
 } c;

int isBigEnd()
{
  c.a = 1;
  return c.b != 1;
}

#endif