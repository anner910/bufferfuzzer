


#include "../../model/Model.h"



#ifdef __cplusplus
extern "C"{
#endif


int doSizeAddSub4Get(int size)
{
    return size + 4;
}

int doSizeAddSub4Set(int size)
{
    return size - 4;
}


int doSizeAddSub2Get(int size)
{
    return size - 2;
}

int doSizeAddSub2Set(int size)
{
    return size + 2;
}


int doSizeIpv4Get(int size)
{
    return size * 4;
}

int doSizeIpv4Set(int size)
{
    return size /4 ;
}


#ifdef __cplusplus
}
#endif

