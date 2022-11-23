



#include "Model.h"

#ifdef __cplusplus
extern "C"{
#endif

static char* integration_configure(elementXmlContent *tree, char* value)
{
    int pos = mlib_searchMemory("##", 2, value, mlib_strlen(value));
    int pos1;

    if (pos >= 0 )
    {
        pos1 = mlib_searchMemory(tree->attribute_name, mlib_strlen(tree->attribute_name), value + pos, mlib_strlen(value) - pos);

        //找到了
        if (2 == pos1)
        {
            BF_memcpy(g_bufferFuzz.tempBuffer, value, pos);
            BF_memcpy(g_bufferFuzz.tempBuffer + pos, tree->attribute_value, mlib_strlen(tree->attribute_value));
            BF_memcpy(g_bufferFuzz.tempBuffer + pos + mlib_strlen(tree->attribute_value), 
            value + pos + 4 + mlib_strlen(tree->attribute_name), mlib_strlen(value) + 1 - pos - 4 - mlib_strlen(tree->attribute_name));

            return g_bufferFuzz.tempBuffer;
        }
    }

    //没找到
    return value;
}


char* parseXmlConfigure(elementXmlContent *tree, char* value)
{
	
    elementXmlContent *temp_tree = tree->bigChild;

    char* temp = value;

    for(;temp_tree;)
    {
        if (temp_tree->type == ElementType_Configure)
        {
            elementXmlContent *temp_child = temp_tree->bigChild;

            for(;temp_child;)
            {
                temp = integration_configure(temp_child, temp);
                temp_child = temp_child->littleBrother;
                }

            break;
        }
        temp_tree = temp_tree->littleBrother;
    }

    //找不到拉倒
    return temp;

}


#ifdef __cplusplus
}
#endif

