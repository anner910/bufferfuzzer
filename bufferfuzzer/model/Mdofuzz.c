



#include "Model.h"


#ifdef __cplusplus
extern "C"{
#endif

int g_paraNo = 0;

void do_fuzzCall(elementBinContent *tree, char* mutator)
{
    if (g_bufferFuzz.onoffDebugDo)
        BF_printf("\r\n           para is %s\r\n", tree->xml->attribute_name);

    if (g_bufferFuzz.onoffDebugDo)
        BF_printf("           type is %s\r\n", mlib_getTypeName(tree->xml->type));

    if (tree->xml->type == ElementType_Bits)
        tree->after_lenght = tree->xml->xml_length;

    int isMutator = 1;

    if ((mutator) && (mlib_strcmp(mutator, "false") == 0))
        isMutator = 0;

    if (isMutator == 0)
    {
        if ((tree->xml->isAnalyzer == 1)
            ||(tree->xml->type == ElementType_String)
            ||(tree->xml->type == ElementType_Buf)
            ||(tree->xml->type == ElementType_Number)
            ||(tree->xml->type == ElementType_S8)
            ||(tree->xml->type == ElementType_S16)
            ||(tree->xml->type == ElementType_S32)
            ||(tree->xml->type == ElementType_S64)
            ||(tree->xml->type == ElementType_U8)
            ||(tree->xml->type == ElementType_U16)
            ||(tree->xml->type == ElementType_U32)
            ||(tree->xml->type == ElementType_U64)
            ||(tree->xml->type == ElementType_Bit)
            ||(tree->xml->type == ElementType_Float)
            ||(tree->xml->type == ElementType_Double))

            tree->after_buf = tree->value;
            tree->after_lenght = tree->value_length;

        return;
    }

    //解析吧
    if(tree->xml->isAnalyzer == 1)
    {
        if (do_analyzer_fuzz(tree) )
            return;
    }

    if (tree->xml->type == ElementType_String)
    {
        tree->after_buf = CF_GetString(g_paraNo, tree->value, tree->value_length+ 1, 1, g_bufferFuzz.maxElementLength);
        tree->after_lenght = CF_GetMutatorLen(g_paraNo++) - 1; //减一，以后再改
    }

    if (tree->xml->type == ElementType_Buf)
    {
        tree->after_buf = CF_GetBlob(g_paraNo, tree->value, tree->value_length, 0, g_bufferFuzz.maxElementLength);
        tree->after_lenght = CF_GetMutatorLen(g_paraNo++);
    }

    //Number其他长度以后再优化
    if ((tree->xml->type == ElementType_S8)
        ||((tree->xml->type == ElementType_Number) && (tree->value_length == 1))
        ||((tree->xml->type == ElementType_Bit) && (tree->value_length == 1)))
    {	
        tree->after_buf = CF_GetS8(g_paraNo, tree_getValue(tree));
        //有点傻，有点慢，以后再优化
        tree_setValue(tree, *(s8*)tree->after_buf);
        tree->after_lenght = CF_GetMutatorLen(g_paraNo++);
    }

    if ((tree->xml->type == ElementType_S16)
        ||((tree->xml->type == ElementType_Number) && (tree->value_length == 2))
        ||((tree->xml->type == ElementType_Bit) && (tree->value_length == 2)))
    {	
        tree->after_buf = CF_GetS16(g_paraNo, tree_getValue(tree));
        tree_setValue(tree, *(s16*)tree->after_buf);
        tree->after_lenght = CF_GetMutatorLen(g_paraNo++);
    }

    if ((tree->xml->type == ElementType_S32)
        ||((tree->xml->type == ElementType_Number) && (tree->value_length == 4))
        ||((tree->xml->type == ElementType_Bit) && (tree->value_length == 4)))
    {	
        tree->after_buf = CF_GetS32(g_paraNo, tree_getValue(tree));
        tree_setValue(tree, *(s32*)tree->after_buf);
        tree->after_lenght = CF_GetMutatorLen(g_paraNo++);
    }

    if ((tree->xml->type == ElementType_S64)
        ||((tree->xml->type == ElementType_Number) && (tree->value_length == 8))
        ||((tree->xml->type == ElementType_Bit) && (tree->value_length == 8)))
    {	
        tree->after_buf = CF_GetS64(g_paraNo, tree_getValue(tree));
        tree_setValue(tree, *(s64*)tree->after_buf);
        tree->after_lenght = CF_GetMutatorLen(g_paraNo++);
    }

    if (tree->xml->type == ElementType_U8)
    {	
        tree->after_buf = CF_GetU8(g_paraNo, tree_getValue(tree));
        tree_setValue(tree, *(u8*)tree->after_buf);
        tree->after_lenght = CF_GetMutatorLen(g_paraNo++);
    }

    if (tree->xml->type == ElementType_U16)
    {	
        tree->after_buf = CF_GetU16(g_paraNo, tree_getValue(tree));
        tree_setValue(tree, *(u16*)tree->after_buf);
        tree->after_lenght = CF_GetMutatorLen(g_paraNo++);
    }

    if (tree->xml->type == ElementType_U32)
    {	
        tree->after_buf = CF_GetU32(g_paraNo, tree_getValue(tree));
        tree_setValue(tree, *(u32*)tree->after_buf);
        tree->after_lenght = CF_GetMutatorLen(g_paraNo++);
    }

    if (tree->xml->type == ElementType_U64)
    {	
        tree->after_buf = CF_GetU64(g_paraNo, tree_getValue(tree));
        tree_setValue(tree, *(u64*)tree->after_buf);
        tree->after_lenght = CF_GetMutatorLen(g_paraNo++);
    }

    if (tree->xml->type == ElementType_Float)
    {	
        tree->after_buf = CF_GetFloat(g_paraNo, *((float*)tree->value));
        tree->after_lenght = CF_GetMutatorLen(g_paraNo++);
    }

    if (tree->xml->type == ElementType_Double)
    {	
        tree->after_buf = CF_GetDouble(g_paraNo, *((double*)tree->value));
        tree->after_lenght = CF_GetMutatorLen(g_paraNo++);
    }

    if (g_bufferFuzz.onoffDebugDo)
    {
        mlib_printfData(tree->after_buf, tree->after_lenght);
    }
}

void do_fuzzTree(elementBinContent *tree, char* mutator)
{
    elementBinContent *temp_tree = tree;

    //儿子有配置的话，覆盖父亲的
    char* temp_mutator = mutator;
    if (mlib_strlen(temp_tree->xml->attribute_mutator))
        temp_mutator = temp_tree->xml->attribute_mutator;

    do_fuzzCall(temp_tree, temp_mutator);


    if(temp_tree->bigChild)
    {
        do_fuzzTree(temp_tree->bigChild, temp_mutator);
    }

    temp_tree = temp_tree->littleBrother;

    for(;temp_tree;)
    {
        temp_mutator = mutator;
        if (mlib_strlen(temp_tree->xml->attribute_mutator))
            temp_mutator = temp_tree->xml->attribute_mutator;

        do_fuzzCall(temp_tree, temp_mutator);

        if(temp_tree->bigChild)
        {
            do_fuzzTree(temp_tree->bigChild, temp_mutator);
        }

        temp_tree = temp_tree->littleBrother;
    }
}


void do_fuzz(elementBinContent *tree)
{
    do_fuzzTree(tree, NULL);
}


#ifdef __cplusplus
}
#endif

