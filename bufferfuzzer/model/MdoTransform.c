


#include "Model.h"


#ifdef __cplusplus
extern "C"{
#endif

//��������
enum TransformType
{
    TransformType_Unknow = 0,
    TransformType_Bas64 = 1, 
	
};

//Transform �����Ͼ��Ǹı��Լ�

//�����������ܾ���
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



//�Ͳ���Ӧ��Ҫ�ģ�Ӧ�ú�relationͳһ����
void do_transform_after(elementBinContent *tree)
{
    //ֻ��ֵһ�Σ�����ٶȣ������Ժ��ڴ�Ƚϵ��ٶ�
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


