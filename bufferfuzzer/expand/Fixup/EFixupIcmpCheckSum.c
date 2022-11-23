


#include "../../model/Model.h"



#ifdef __cplusplus
extern "C"{
#endif


static u16 checksum(u16 *buffer, int size) 
{
    unsigned long cksum=0;

    while(size >1) 
    {
        cksum+=*buffer++;
        size -=sizeof(u16);
    }

    if(size ) 
    {
        cksum += *(u8*)buffer;
    }

    cksum = (cksum >> 16) + (cksum & 0xffff);
    cksum += (cksum >>16);
    return (u16)(~cksum);
}


void doIcmpCheckSum(elementBinContent *value, elementBinContent *blob)
{
    g_bufferFuzz.tempBufferLength = 0;
    BF_memset(value->after_buf, 0, value->after_lenght);
    tree_bufferValueGet(blob, 0);

    //没有补齐，以后再说
    u16 aaa = checksum((u16 *)g_bufferFuzz.tempBuffer, g_bufferFuzz.tempBufferLength);

    BF_memcpy(value->after_buf, (char*)&aaa, 2);
}

#ifdef __cplusplus
}
#endif

