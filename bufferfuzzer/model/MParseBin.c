



#include "Model.h"

#ifdef __cplusplus
extern "C"{
#endif

void parseBin(elementXmlContent *treeXml,char* DataModelName, char* bin, int length, elementBinContent **treeBin)
{

    int length_temp = -1;
    g_bufferFuzz.nolength_tree = NULL;

    if (treeXml->type != ElementType_BufferFuzzer)
    {
        ASSERT("bin parse error, type is not BufferFuzzer\r\n");
    }


    elementXmlContent *tempXmlTree = treeXml;
    elementBinContent* temp_bin = (elementBinContent *)BF_malloc(sizeof(elementBinContent));
    BF_memset(temp_bin, 0, sizeof(elementBinContent));
    *treeBin = temp_bin;
    temp_bin->xml = treeXml;

    temp_bin->binPtr = bin;
    temp_bin->binLength = length;

    elementXmlContent* temp_tree = treeXml->bigChild;

    for(;temp_tree;)
    {
        if (mlib_strcmp(temp_tree->attribute_name, DataModelName) == 0)
        {
            elementBinContent* temp_bin1 = (elementBinContent *)BF_malloc(sizeof(elementBinContent));
            BF_memset(temp_bin1, 0, sizeof(elementBinContent));
            temp_bin->bigChild = temp_bin1;
            temp_bin1->xml = temp_tree;

            temp_bin1->binPtr = bin;
            temp_bin1->binLength = length;

            length_temp = parse_element(temp_tree, bin, length, temp_bin1);
            break;
        }

        temp_tree = temp_tree->littleBrother;
    }

    if (temp_tree == NULL)
    {
        BF_printf("Buffer %s is not found\r\n",DataModelName);
    }

    if (length_temp < 0)
    {
        ASSERT("bin parse error, because check failed\r\n");
    }


    return ;
}


#ifdef __cplusplus
}
#endif

