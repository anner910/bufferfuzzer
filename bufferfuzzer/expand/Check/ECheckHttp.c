

#include "../../model/Model.h"


#ifdef __cplusplus
extern "C"{
#endif

int do_check_http_bin(elementBinContent *tree, char* bin, int length)
{

    if (2 <= length)
    {
        if ((bin[0] == '\r') && (bin[1] == '\n'))
            return -1;
    }

    return 0;
}

int do_check_http_value(elementBinContent *tree, char* value, int length)
{
    return 0;
}

#ifdef __cplusplus
}
#endif

