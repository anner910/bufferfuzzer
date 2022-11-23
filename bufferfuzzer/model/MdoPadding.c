
#include "Model.h"


#ifdef __cplusplus
extern "C"{
#endif

int do_padding_get(elementBinContent *tree)
{
    elementBinContent* temp_bin1 = found_relationOfPadding(tree, tree->xml->attribute_of);

    int div = mlib_atoi(tree->xml->attribute_alignment)/8;

    int length = tree_PaddingOffSetGet(temp_bin1, tree, 0);

    int value = length % div;

    if (value == 0)
        return 0;

    return div - value;
}

void do_padding_after(elementBinContent *tree)
{
    elementBinContent* temp_bin1 = found_relationOfPadding(tree, tree->xml->attribute_of);


    int div = mlib_atoi(tree->xml->attribute_alignment)/8;

    int length = tree_PaddingOffSetGet(temp_bin1, tree, 1);

    tree->after_lenght = div - length % div;

    if (tree->after_buf)
        BF_free(tree->after_buf);

    tree->after_buf = BF_malloc(tree->after_lenght + 1);
    BF_memset(tree->after_buf, 0, tree->after_lenght + 1);

    return;
}


#ifdef __cplusplus
}
#endif

