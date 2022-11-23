


#include "Model.h"


#ifdef __cplusplus
extern "C"{
#endif

//数据类型
enum TransformType
{
    TransformType_Unknow = 0,
    TransformType_Bas64 = 1, 
	
};

//Transform 理论上就是改变自己

//这里做个解密就行
void do_transform_before(elementBinContent *tree)
{
    char* buf = tree->xml->attribute_type;
    int length = mlib_strlen(tree->xml->attribute_type);

    if ((length==6)&&(mlib_memcmp("base64",buf,6)==0))
    {
        doBase64Decode(tree);
    }
}

//----------------------------------------------



//和部分应该要改，应该和relation统一管理
void do_transform_after(elementBinContent *tree)
{
    //只赋值一次，提高速度，减少以后内存比较的速度
    if (tree->typeTransform == TransformType_Unknow)
    {
        char* buf = tree->xml->attribute_type;
        int length = mlib_strlen(tree->xml->attribute_type);

        if ((length == 6)&&(mlib_memcmp("base64",buf,6) == 0))
        {
            tree->typeTransform = TransformType_Bas64;
        }
        else
        {
            BF_printf("TransformType %s is unknow\r\n",tree->xml->attribute_type);
            ASSERT("TransformType check failed\r\n");
        }
    }

    //
    if (tree->typeTransform == TransformType_Bas64)
    {
        doBase64Encode(tree);
    }
}


#ifdef __cplusplus
}
#endif


