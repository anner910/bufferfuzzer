
#include "Model.h"

#ifdef __cplusplus
extern "C"{
#endif

int BF_random(void)
{
    return rand();
}

void* BF_malloc(size_t size)
{
    void* temp = malloc(size);
    return temp;
}

void BF_free(void* s)
{
    free(s);
    return;
}

void* BF_memset(void *s,int ch,size_t n)
{
    return memset(s, ch, n);
}

void* BF_memcpy(void *d,void *s,size_t n)
{
    return memcpy(d, s, n);
}

uint8_t  BF_swap8(uint8_t x)  
{ 
    return x; 
}
uint16_t BF_swap16(uint16_t x) 
{ 
    return __builtin_bswap16(x); 
}
uint32_t BF_swap32(uint32_t x) 
{ 
    return __builtin_bswap32(x); 
}
uint64_t BF_swap64(uint64_t x) 
{ 
    return __builtin_bswap64(x); 
}

void IO_readFileRaw(char* path, char** buf, int* len)
{
    int InputLen;
    char *Buf;
    FILE *In = fopen(path, "r");
    {
        *len = 0;
        *buf = NULL;
        if (!In) 
            return;
    }

    fseek(In, 0, SEEK_END);

    InputLen = ftell(In);
    fseek(In, 0, SEEK_SET);

    Buf = (char*)BF_malloc(InputLen + 1);

    fread(Buf, 1, InputLen, In);
    fclose(In);

    Buf[InputLen] = 0;
    *len = InputLen;
    *buf = Buf;
    return;
}

void BF_seed(int setSeed)
{
    srand(setSeed);
}

#ifdef __cplusplus
}
#endif

