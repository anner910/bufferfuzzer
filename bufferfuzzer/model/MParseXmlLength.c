



#include "Model.h"

#ifdef __cplusplus
extern "C"{
#endif

static void integration_length(elementXmlContent *tree, elementXmlContent *root)
{
    //����һ���г���
    if((tree->type == ElementType_Number) 
    || (tree->type == ElementType_Bit)
    || (tree->type == ElementType_Bits))
    {
        //size
        if(mlib_strlen(tree->attribute_size))
        {
            tree->xml_size = mlib_atoi(tree->attribute_size);
            tree->xml_length =  mlib_fromSizeToLength(tree->xml_size);
        }
    }

    //xml���ָ���˳���
    if(mlib_strlen(tree->attribute_length))
    {
        tree->xml_length = mlib_atoi(tree->attribute_length);
    }

    //�±������Լ��й̶�����
    if(tree->type == ElementType_S8)
    {
        tree->xml_length = 1;
    }

    if(tree->type == ElementType_S16)
    {
        tree->xml_length = 2;
    }

    if(tree->type == ElementType_S32)
    {
        tree->xml_length = 4;
    }

    if(tree->type == ElementType_S64)
    {
        tree->xml_length = 8;
    }

    if(tree->type == ElementType_U8)
    {
        tree->xml_length = 1;
    }

    if(tree->type == ElementType_U16)
    {
        tree->xml_length = 2;
    }

    if(tree->type == ElementType_U32)
    {
        tree->xml_length = 4;
    }

    if(tree->type == ElementType_U64)
    {
        tree->xml_length = 8;
    }

    if(tree->type == ElementType_Float)
    {
        tree->xml_length = 4;
    }

    if(tree->type == ElementType_Double)
    {
        tree->xml_length = 8;
    }


    //������ָ��������Ҫfix,������֤bin
    tree->fixLength = tree->xml_length;

    //����֮�⣬����string,blob��Ҫ��xml����������
    if((tree->xml_length == 0) && ((tree->type == ElementType_String) || (tree->type == ElementType_Buf)))
    {
        if (tree->attribute_value)
        {
            char *attribute_value = parseXmlConfigure(root, tree->attribute_value);
            tree->xml_length = mlib_strlen(attribute_value);
        }

        //hexĿǰ��֧�ֿո�
        if ((mlib_strlen(tree->attribute_valueType)>=3)&&(mlib_memcmp("hex",tree->attribute_valueType,3) == 0))
        {
            tree->xml_length = tree->xml_length / 2;
        }

        if ((mlib_strlen(tree->attribute_valueType)>=4)&&(mlib_memcmp("ipv4",tree->attribute_valueType,4) == 0))
        {
            tree->xml_length = 4;
        }
    }

    //token����ָ������
    if ((mlib_strlen(tree->attribute_token)>=4)&&(mlib_memcmp("true",tree->attribute_token,4) == 0))
    {
        tree->istoken = 1;

        //token����fix,������֤bin
        tree->fixLength = tree->xml_length;
    }

    if (g_bufferFuzz.onoffDebugXml)
    {
        BF_printf("     -------type  is  %s \r\n",mlib_getTypeName(tree->type));
        BF_printf("            name  is  %s \r\n",tree->attribute_name);
        BF_printf("        xml_size  is  %d \r\n",tree->xml_size);
        BF_printf("      xml_length  is  %d \r\n",tree->xml_length);
        BF_printf("       fixLength  is  %d \r\n",tree->fixLength);
        BF_printf("         istoken  is  %d \r\n",tree->istoken);
    }
}


void parseXmlLength(elementXmlContent *tree, elementXmlContent *root)
{
    elementXmlContent *temp_tree = tree;

    integration_length(temp_tree, root);


    if(temp_tree->bigChild)
    {
        parseXmlLength(temp_tree->bigChild, root);
    }

    temp_tree = temp_tree->littleBrother;

    for(;temp_tree;)
    {

        integration_length(temp_tree, root);

        if(temp_tree->bigChild)
        {
            parseXmlLength(temp_tree->bigChild, root);
        }
        temp_tree = temp_tree->littleBrother;
    }
}


#ifdef __cplusplus
}
#endif

