


#include "Model.h"


#ifdef __cplusplus
extern "C"{
#endif

static void do_bits(elementBinContent *tree)
{
    elementBinContent *temp_tree = tree->bigChild;

    for(;temp_tree;)
    {
        s8 sss = *(u8*)temp_tree->after_buf;

        mlib_copyValueBits(tree->after_buf, temp_tree->after_buf, mlib_atoi(temp_tree->xml->attribute_position), temp_tree->xml->xml_size);

        temp_tree = temp_tree->littleBrother;
    }
}


void do_bits_after(elementBinContent *tree)
{
    if(tree->after_buf == NULL)
    {
        tree->after_lenght = tree->xml->xml_length;
        tree->after_buf = BF_malloc(tree->after_lenght);
    }

    BF_memset(tree->after_buf, 0, tree->after_lenght);

    do_bits(tree);
	
}


#ifdef __cplusplus
}
#endif


