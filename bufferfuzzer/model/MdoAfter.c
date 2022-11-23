


#include "Model.h"



#ifdef __cplusplus
extern "C"{
#endif



//----------------------------------------------
//应该从儿子开始，往外递归,儿子们弄完了再弄自己

//好难啊

//一些逻辑矛盾的场景不支持就不支持吧

//理念错误，应该是引用对象搞完在搞自己吧，以后再改


static void do_after_action(elementBinContent *tree)
{
    if(tree->xml->type == ElementType_Padding)
    {
        do_padding_after(tree);

        if (g_bufferFuzz.onoffDebugDo)
            BF_printf("\r\n  do Padding, name is %s\r\n", 
            tree->xml->attribute_name);
    }

    if(tree->xml->type == ElementType_Bits)
    {
        do_bits_after(tree);

        if (g_bufferFuzz.onoffDebugDo)
            BF_printf("\r\n  do Bits, name is %s\r\n", 
            tree->xml->attribute_name);
    }

    //一定是儿子做完之后
    if(tree->xml->type == ElementType_Transform)
    {
        do_transform_after(tree);

        if (g_bufferFuzz.onoffDebugDo)
            BF_printf("\r\n  transform   value is %s\r\n", 
            tree->xml->attribute_name);

    }

    //
    if(tree->xml->isFixupValue == 1)
    {
        do_fixup_after(tree, NULL);

        if (g_bufferFuzz.onoffDebugDo)
            BF_printf("\r\n  fixup    value is %s, fixup   blob is %s\r\n", 
            tree->xml->attribute_name,tree->fixupBlob->xml->attribute_name);
    }

    if(tree->xml->isFixupBlob == 1)
    {
        do_fixup_after(NULL, tree);

        if (g_bufferFuzz.onoffDebugDo)
            BF_printf("\r\n  fixup1   value is %s, fixup   blob is %s\r\n", 
            tree->fixupValue->xml->attribute_name, tree->xml->attribute_name);
    }

    //搞两次是不是就 没有矛盾了
    if(tree->xml->isRelationValue == 1)
    {
        do_relation_after(tree, NULL);

        if (g_bufferFuzz.onoffDebugDo)
            BF_printf("\r\n  relation  value is %s, relation blob is %s\r\n", 
            tree->xml->attribute_name,tree->xml->relationBlob->attribute_name);
    }

    if(tree->xml->isRelationBlob == 1)
    {
        do_relation_after(NULL, tree);

        if (g_bufferFuzz.onoffDebugDo)
            BF_printf("\r\n  relation1 value is %s, relation blob is %s\r\n", 
            tree->xml->relationValue->attribute_name,tree->xml->attribute_name);
    }
}

static void do_after_tree(elementBinContent *tree)
{

    elementBinContent *temp_tree = tree;


    //计算长度直接赋值就好
    if(temp_tree->bigChild)
    {
        do_after_tree(temp_tree->bigChild);
    }

    do_after_action(temp_tree);

    temp_tree = temp_tree->littleBrother;

    for(;temp_tree;)
    {

        if(temp_tree->bigChild)
        {
            do_after_tree(temp_tree->bigChild);
        }

        do_after_action(temp_tree);

        temp_tree = temp_tree->littleBrother;
    }

}


void do_after(elementBinContent *tree)
{
    do_after_tree(tree);
}


#ifdef __cplusplus
}
#endif


