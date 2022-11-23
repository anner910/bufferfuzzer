#include "Model.h"

#ifdef __cplusplus
extern "C"{
#endif

void integration_Other(elementXmlContent *tree)
{
    //奇怪的东西在这里赋值吧
    if(tree->type == ElementType_Analyzer)
    {
        if (g_bufferFuzz.onoffDebugXml)
            BF_printf(" %20s is Analyzer,parent is %s\r\n",tree->attribute_name,tree->parent->attribute_name);

        tree->parent->isAnalyzer = 1;
    }


    if(tree->type == ElementType_Param)
    {
        if (g_bufferFuzz.onoffDebugXml)
            BF_printf(" %20s is Param,parent is %s\r\n",tree->attribute_name,tree->parent->attribute_name);

        if (mlib_strlen(tree->parent->attribute_para1) == 0)
            mlib_strcpy(tree->parent->attribute_para1, tree->attribute_value);
        else if (mlib_strlen(tree->parent->attribute_para2) == 0)
            mlib_strcpy(tree->parent->attribute_para2, tree->attribute_value);
        else if (mlib_strlen(tree->parent->attribute_para3) == 0)
            mlib_strcpy(tree->parent->attribute_para3, tree->attribute_value);
        else if (mlib_strlen(tree->parent->attribute_para4) == 0)
            mlib_strcpy(tree->parent->attribute_para4, tree->attribute_value);
    }


    if((tree->type == ElementType_Number)
        ||(tree->type == ElementType_S8)
        ||(tree->type == ElementType_S16)
        ||(tree->type == ElementType_S32)
        ||(tree->type == ElementType_S64)
        ||(tree->type == ElementType_U8)
        ||(tree->type == ElementType_U16)
        ||(tree->type == ElementType_U32)
        ||(tree->type == ElementType_U64)
        ||(tree->type == ElementType_Bit))
    {

        //默认值与机器一样
        tree->isbigEndian = isBigendian;

        if (g_bufferFuzz.g_isBigEndian > 0)
        {
            if (g_bufferFuzz.g_isBigEndian == BigEndian)
                tree->isbigEndian = 1;
            else
                tree->isbigEndian = 0;
        }

        if (mlib_strlen(tree->attribute_endian) > 0)
        {
            if (mlib_strcmp(tree->attribute_endian, "big") == 0)
                tree->isbigEndian = 1;
            else
                tree->isbigEndian = 0;
        }
    }
}


void parseXmlOther(elementXmlContent *tree)
{
    elementXmlContent *temp_tree = tree;

    integration_Other(temp_tree);

    if(temp_tree->bigChild)
    {
        parseXmlOther(temp_tree->bigChild);
    }

    temp_tree = temp_tree->littleBrother;

    for(;temp_tree;)
    {
        integration_Other(temp_tree);

        if(temp_tree->bigChild)
        {
            parseXmlOther(temp_tree->bigChild);
        }
        temp_tree = temp_tree->littleBrother;
    }
}


#ifdef __cplusplus
}
#endif

