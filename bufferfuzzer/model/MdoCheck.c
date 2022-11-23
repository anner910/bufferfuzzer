
#include "Model.h"


#ifdef __cplusplus
extern "C"{
#endif

enum CheckType
{
    CheckType_Unknow = 0,
    CheckType_Http = 1, 
};

int do_check_bin(elementBinContent *tree, char* bin, int length)
{
    //只赋值一次，提高速度，减少以后内存比较的速度
    //
    if (tree->typeCheck == CheckType_Unknow)
    {
        char* buf = tree->xml->attribute_check;
        int length = mlib_strlen(tree->xml->attribute_check);

        if ((length == 9)&&(mlib_memcmp("checkHttp",buf,9) == 0))
        {
            tree->typeRelation = CheckType_Http;
        }
        else
        {
            BF_printf("CheckType %s is unknow\r\n",tree->xml->attribute_check);
            //ASSERT("CheckType check failed\r\n");
        }
    }


    //需要 增加各种s32等类型
    if (tree->typeRelation == CheckType_Http)
    {
        return do_check_http_bin(tree, bin, length);
    }

    return 0;
}

int do_check_value(elementBinContent *tree, char* value, int length)
{
    //只赋值一次，提高速度，减少以后内存比较的速度
    //
    if (tree->typeCheck == CheckType_Unknow)
    {
        char* buf = tree->xml->attribute_check;
        int length = mlib_strlen(tree->xml->attribute_check);

        if ((length == 9)&&(mlib_memcmp("checkHttp", buf, 9) == 0))
        {
            tree->typeRelation = CheckType_Http;
        }
        else
        {
            BF_printf("CheckType %s is unknow\r\n",tree->xml->attribute_check);
            //ASSERT("CheckType check failed\r\n");
        }
    }


    //需要 增加各种s32等类型
    if (tree->typeRelation == CheckType_Http)
    {
        return do_check_http_value(tree, value, length);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif

