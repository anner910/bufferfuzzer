
#include "Model.h"

#ifdef __cplusplus
extern "C"{
#endif

//Ϊ��array������ʱ�� �ÿ�xmlԪ��
elementXmlContent g_blobk_tree =  
{
    .type = ElementType_Struct, 
}; 


int parse_array_child(elementXmlContent *tree, char* bin, int length, elementBinContent *treeBin)
{
    int temp;
    int length_temp = 0;
    elementXmlContent *temp_tree = tree;


    treeBin->count = mlib_atoi(tree->attribute_count);
    treeBin->minCount = mlib_atoi(tree->attribute_count);
    treeBin->maxCount = mlib_atoi(tree->attribute_count);


    int minCount = 0;
    int	maxCount = 10000000;
    int count = 0;

    if (treeBin->count > 0)
    {
        minCount = treeBin->count;
        maxCount = treeBin->count;
    }
    else
    {
        if (treeBin->minCount > 0)
            minCount = treeBin->minCount;

        if (treeBin->maxCount > 0)
            maxCount = treeBin->maxCount;
    }

    //��relation�����������
    if (treeBin->isRelationCount == 1)
    {
        if (treeBin->relationCount < minCount)
            if (g_bufferFuzz.onoffDebugXml)
                BF_printf("failed***Array(%s) get relation count %d, < minCount %d\r\n",
                tree->attribute_name, treeBin->relationCount, minCount);


        if (treeBin->relationCount > maxCount)
            if (g_bufferFuzz.onoffDebugXml)
                BF_printf("failed***Array(%s) get relation count %d, > maxCount %d\r\n",
                tree->attribute_name, treeBin->relationCount, maxCount);

        minCount = treeBin->relationCount;
        maxCount = treeBin->relationCount;
    }

    if (maxCount < minCount)
    {
        if (g_bufferFuzz.onoffDebugXml)
            BF_printf("failed***Array(%s) maxCount %d < minCount %d\r\n",
            tree->attribute_name, maxCount, minCount);

        return -1;
    }


    if (count == maxCount)
    {
        if (g_bufferFuzz.onoffDebugXml)
            BF_printf("success***array1(%s) count is %d, return %d\r\n",tree->attribute_name, count, length_temp);

        return length_temp;
    }


    elementBinContent* temp_bin = (elementBinContent *)BF_malloc(sizeof(elementBinContent));
    BF_memset(temp_bin, 0, sizeof(elementBinContent));
    temp_bin->xml = temp_tree;

    treeBin->bigChild = temp_bin;
    temp_bin->parent = treeBin;

    temp = parse_struct_child(temp_tree, bin, length, temp_bin);

    if (temp < 0)
    {
        tree_free_bin1(temp_bin);
        treeBin->bigChild = NULL;
        BF_free(temp_bin);

        //һ��û�У�����
        if ((minCount <= count ) && (count <= maxCount ))
        {
            if (g_bufferFuzz.onoffDebugXml)
                BF_printf("success***array5(%s) count is %d, return %d\r\n",tree->attribute_name, count, 0);

            return 0;
        }


        return temp;
    }

    temp_bin->xml = &g_blobk_tree;

    if((temp != 0)&& (bin != NULL))
    {
        temp_bin->binPtr = bin;
        temp_bin->binLength = tree->fixLength;

        bin = temp + bin;
        length = length - temp;
        length_temp = length_temp + temp;
    }

    count ++;

    if (count == maxCount)
    {
        if (g_bufferFuzz.onoffDebugXml)
            BF_printf("success***array2(%s) count is %d, return %d\r\n",tree->attribute_name, count, length_temp);

        return length_temp;
    }


    for(;temp_tree;)
    {
        elementBinContent* temp_bin1 = (elementBinContent *)BF_malloc(sizeof(elementBinContent));
        BF_memset(temp_bin1, 0, sizeof(elementBinContent));
        temp_bin1->xml = temp_tree;

        temp_bin1->parent = treeBin;


        temp_bin->littleBrother= temp_bin1;
        temp_bin1->bigBrother= temp_bin;

        temp = parse_struct_child(temp_tree, bin, length, temp_bin1);

        if (temp < 0)
        {
            tree_free_bin1(temp_bin1);

            BF_free(temp_bin1);
            temp_bin->littleBrother = NULL;

            break;
        }

        temp_bin1->xml = &g_blobk_tree;

        if((temp != 0)&& (bin != NULL))
        {
            temp_bin1->binPtr = bin;
            temp_bin1->binLength = tree->fixLength;

            bin = temp + bin;
            length = length - temp;
            length_temp = length_temp + temp;
        }


        count ++;
        if (count == maxCount)
        {
            if (g_bufferFuzz.onoffDebugXml)
                BF_printf("success***array3(%s) count is %d, return %d\r\n",
                tree->attribute_name, count, length_temp);
            return length_temp;
        }

        temp_bin = temp_bin1;
    }


    if (count < minCount)
    {
        if (g_bufferFuzz.onoffDebugXml)
            BF_printf("failed***Array(%s) get count is %d < minCount %d\r\n",
            tree->attribute_name, count, minCount);

        return -1;
    }

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("success***array4(%s) count is %d, return %d\r\n",tree->attribute_name, count, length_temp);

    return length_temp;

}

int parse_union_child(elementXmlContent *tree, char* bin, int length, elementBinContent *treeBin)
{

    int length_temp = 0;
    elementXmlContent *temp_tree = tree->bigChild;

    elementBinContent* temp_bin = (elementBinContent *)BF_malloc(sizeof(elementBinContent));
    BF_memset(temp_bin, 0, sizeof(elementBinContent));


    treeBin->bigChild = temp_bin;
    temp_bin->parent = treeBin;

    for(;temp_tree;)
    {
        temp_bin->xml = temp_tree;
        length_temp = parse_element(temp_tree, bin, length, temp_bin);

        //û��ƥ�䣬�ͼ���
        if (length_temp < 0)
        {
            temp_tree = temp_tree->littleBrother;
            tree_free_bin1(temp_bin);

            temp_bin->bigChild = NULL;

            //BF_free �ڴ�
            continue;
        }

        if((length_temp != 0)&& (bin != NULL))
        {
            temp_bin->binPtr = bin;
            temp_bin->binLength = tree->fixLength;
        }

        if (g_bufferFuzz.onoffDebugXml)
            BF_printf("success***Union(%s) return %d\r\n",tree->attribute_name, length_temp);

        return length_temp;

    }

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("failed***Union(%s) not child been found\r\n",tree->attribute_name);

    //��ûƥ�䣬����ʧ��
    return -1;
}

int parse_struct_child(elementXmlContent *tree, char* bin, int length, elementBinContent *treeBin)
{

    int temp;
    int length_temp = 0;
    elementXmlContent *temp_tree = tree->bigChild;

    if (temp_tree == NULL )
        return 0;

    //�����
    elementBinContent* temp_bin = (elementBinContent *)BF_malloc(sizeof(elementBinContent));
    BF_memset(temp_bin, 0, sizeof(elementBinContent));
    temp_bin->xml = temp_tree;

    treeBin->bigChild = temp_bin;
    temp_bin->parent = treeBin;

    temp = parse_element(temp_tree, bin, length, temp_bin);
    if (temp < 0)
    {
        return temp;
    }

    if((temp != 0)&& (bin != NULL))
    {
        temp_bin->binPtr = bin;
        temp_bin->binLength = tree->fixLength;

        bin = temp + bin;
        length = length - temp;
        length_temp = length_temp + temp;
    }

    temp_tree = temp_tree->littleBrother;


    //��������
    for(;temp_tree;)
    {
        elementBinContent* temp_bin1 = (elementBinContent *)BF_malloc(sizeof(elementBinContent));
        BF_memset(temp_bin1, 0, sizeof(elementBinContent));
        temp_bin1->xml = temp_tree;

        temp_bin1->parent = treeBin;


        temp_bin->littleBrother= temp_bin1;
        temp_bin1->bigBrother= temp_bin;

        temp = parse_element(temp_tree, bin, length, temp_bin1);
        if (temp < 0)
        {
            return temp;
        }

        if((temp != 0)&& (bin != NULL))
        {
            temp_bin1->binPtr = bin;
            temp_bin1->binLength = tree->fixLength;

            bin = temp + bin;
            length = length - temp;
            length_temp = length_temp + temp;
        }

        temp_tree = temp_tree->littleBrother;

        temp_bin = temp_bin1;
    }

    if (g_bufferFuzz.onoffDebugXml)
    BF_printf("success***struct(%s) return %d\r\n",tree->attribute_name, length_temp);

    return length_temp;

}

#ifdef __cplusplus
}
#endif

