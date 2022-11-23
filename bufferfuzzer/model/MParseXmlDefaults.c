



#include "Model.h"

#ifdef __cplusplus
extern "C"{
#endif

static void integration_defaults(elementXmlContent *tree)
{
    //整数一定有长度
    if(tree->type == ElementType_Number)
    {
        //size
        if (mlib_strlen(tree->attribute_endian) > 0)
        {
            if(mlib_strcmp(tree->attribute_alignment, "big"))
            {
                g_bufferFuzz.g_isBigEndian = BigEndian;
            }
            else
                g_bufferFuzz.g_isBigEndian = LittleEndian;
        }
    }

    if (g_bufferFuzz.onoffDebugXml)
    {
        BF_printf("     -------type  is  %s \r\n",mlib_getTypeName(tree->type));
        BF_printf("            name  is  %s \r\n",tree->attribute_name);
        BF_printf("       alignment  is  %d \r\n",g_bufferFuzz.g_isBigEndian);
    }

}


void parseXmlDefaults(elementXmlContent *tree)
{
    //默认和自己一样
    g_bufferFuzz.g_isBigEndian = isBigendian;

    elementXmlContent *temp_tree = tree->bigChild;

    for(;temp_tree;)
    {
        if (temp_tree->type == ElementType_Defaults)
        {
            elementXmlContent *temp_child = temp_tree->bigChild;

            for(;temp_child;)
            {
                integration_defaults(temp_child);
                temp_child = temp_child->littleBrother;
            }

            break;
        }
        temp_tree = temp_tree->littleBrother;
    }

}


#ifdef __cplusplus
}
#endif

