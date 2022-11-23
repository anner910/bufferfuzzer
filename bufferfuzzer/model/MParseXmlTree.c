



#include "Model.h"

#ifdef __cplusplus
extern "C"{
#endif


//¸ø¸ç¸ç¸¸Ç×¸³Öµ  ½â¾öÊ÷²»ÍêÉÆµÄÎÊÌâ
void parseXmlTree(elementXmlContent *tree)
{

    elementXmlContent *temp_tree = tree;
    elementXmlContent *temp_tree1;

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("name is %20s;type is %20s\r\n",tree->attribute_name,mlib_getTypeName(tree->type));

    if(temp_tree->bigChild)
    {
        //¸¸Ç×
        temp_tree->bigChild->parent = temp_tree;
        parseXmlTree(temp_tree->bigChild);
    }


    //¸ç¸ç
    if(temp_tree->littleBrother)
        temp_tree->littleBrother->bigBrother=temp_tree;

    temp_tree1 = temp_tree->littleBrother;

    for(;temp_tree1;)
    {
        if (g_bufferFuzz.onoffDebugXml)
            BF_printf("name is %20s;type is %20s\r\n",temp_tree1->attribute_name,mlib_getTypeName(temp_tree1->type));

        //¸¸Ç×
        temp_tree1->parent = temp_tree;

        if(temp_tree1->bigChild)
        {
            //¸¸Ç×
            temp_tree1->bigChild->parent = temp_tree1;
            parseXmlTree(temp_tree1->bigChild);
        }

        //¸ç¸ç
        if(temp_tree1->littleBrother)
            temp_tree1->littleBrother->bigBrother=temp_tree1;

        temp_tree1 = temp_tree1->littleBrother;
    }
}


#ifdef __cplusplus
}
#endif

