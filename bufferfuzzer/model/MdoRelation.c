
#include "Model.h"


#ifdef __cplusplus
extern "C"{
#endif

enum RelationType
{
    RelationType_Unknow = 0,
    RelationType_Size = 1, 
    RelationType_SizeAddSub4 = 2, 
    RelationType_Count = 3,
    RelationType_SizeJpg = 4,
    RelationType_SizeString = 5,
    RelationType_SizeIpv4 = 6,
};



//找到之后 ，互相指引
void found_relation1(elementXmlContent *tree)
{
    if(tree->type == ElementType_Relation)
    {
        if (g_bufferFuzz.onoffDebugXml)
        {
            BF_printf("----Relation type  is  %s \r\n",tree->attribute_type);
            BF_printf("       value type  is  %s \r\n",mlib_getTypeName(tree->parent->type));
            BF_printf("             name  is  %s \r\n",tree->parent->attribute_name);
        }

        int isParent = 0;
        elementXmlContent* temp1 = found_relationOfXmlBlob(tree->parent, &isParent, tree->attribute_of);

        if (isParent == 1)
        {
            tree->parent->isRelationParent = 1;
            temp1->isRelationParent = 1;
        }

        if (g_bufferFuzz.onoffDebugXml)
        {
            BF_printf("        blob type  is  %s \r\n",mlib_getTypeName(temp1->type));
            BF_printf("             name  is  %s \r\n",temp1->attribute_name);

            BF_printf("         isParent  is  %d \r\n",isParent);
        }

        temp1->isRelationBlob = 1;
        tree->parent->isRelationValue = 1;

        tree->parent->relationBlob = temp1;
        temp1->relationValue = tree->parent;
    }
}

//正常查找 
void found_relation(elementXmlContent *tree)
{
    elementXmlContent *temp_tree = tree;

    found_relation1(tree);


    if(temp_tree->bigChild)
    {
        found_relation(temp_tree->bigChild);
    }

    temp_tree = temp_tree->littleBrother;

    for(;temp_tree;)
    {
        found_relation1(temp_tree);

        if(temp_tree->bigChild)
        {
            found_relation(temp_tree->bigChild);
        }

        temp_tree = temp_tree->littleBrother;
    }
}


void do_relation_before(elementXmlContent *tree)
{
    found_relation(tree);
}


void do_relation_after(elementBinContent *treevalue,elementBinContent *treeBlob)
{
    if (treeBlob)
    {
        if (treeBlob->relationValue == NULL)
        {

            BF_printf("----------   %s   \r\n",treeBlob->xml->relationValue->attribute_name);
            treeBlob->relationValue = found_relationOfBinValue(treeBlob, treeBlob, treeBlob->xml->relationValue->attribute_name, 1);
            treeBlob->relationValue->relationBlob = treeBlob;
        }

        do_relation_set(treeBlob);
    }

    if (treevalue)
    {
        if (treevalue->relationBlob == NULL)
        {
            treevalue->relationBlob = found_relationOfBinBlob(treevalue, treevalue->xml->relationBlob->attribute_name, 0);
            treevalue->relationBlob->relationValue = treevalue;
        }

        do_relation_set(treevalue->relationBlob);
    }
}


int do_relation_get(elementBinContent *tree)
{
    elementBinContent* temp_bin1 = found_relationOfBinValue(tree, tree, tree->xml->relationValue->attribute_name, 1);

    //只赋值一次，提高速度，减少以后内存比较的速度
    //fixup必须是大儿子
    if (temp_bin1->xml->isRelationValue == 1)
    {
        char* buf = temp_bin1->xml->bigChild->attribute_type;
        int length = mlib_strlen(temp_bin1->xml->bigChild->attribute_type);

        if ((length == 4)&&(mlib_memcmp("size",buf,4) == 0))
        {
            temp_bin1->typeRelation = RelationType_Size;
        }
        else if ((length == 7)&&(mlib_memcmp("sizeJpg",buf,7) == 0))
        {
            temp_bin1->typeRelation = RelationType_SizeJpg;
        }
        else if ((length == 10)&&(mlib_memcmp("sizeAddSub",buf,10) == 0))
        {
            temp_bin1->typeRelation = RelationType_SizeAddSub4;
        }
        else if ((length == 5)&&(mlib_memcmp("count",buf,5) == 0))
        {
            temp_bin1->typeRelation = RelationType_Count;
        }
        else if ((length == 10)&&(mlib_memcmp("sizeString",buf,10) == 0))
        {
            temp_bin1->typeRelation = RelationType_SizeString;
        }
        else if ((length == 8)&&(mlib_memcmp("sizeIpv4",buf,8) == 0))
        {
            temp_bin1->typeRelation = RelationType_SizeIpv4;
        }
        else
        {
            BF_printf("RelationType %s is unknow\r\n",temp_bin1->xml->bigChild->attribute_type);
            ASSERT("RelationType check failed\r\n");
        }
    }

    tree->typeRelation = temp_bin1->typeRelation;

    int temp_length = 0;

    //需要 增加各种s32等类型
    if (temp_bin1->typeRelation == RelationType_Size)
    {
        s64 value = tree_getValue(temp_bin1);
        temp_length = doSizeGet(value);
    }

    if (temp_bin1->typeRelation == RelationType_SizeString)
    {
        s64 value = tree_getValue(temp_bin1);
        temp_length = doSizeGet(value);
    }

    if (temp_bin1->typeRelation == RelationType_Count)
    {
        s64 value = tree_getValue(temp_bin1);
        temp_length = doSizeGet(value);
    }

    if (temp_bin1->typeRelation == RelationType_SizeAddSub4)
    {
        s64 value = tree_getValue(temp_bin1);
        temp_length = doSizeAddSub4Get(value);
    }

    if (temp_bin1->typeRelation == RelationType_SizeJpg)
    {
        s64 value = tree_getValue(temp_bin1);
        temp_length = doSizeAddSub2Get(value);
    }

    if (temp_bin1->typeRelation == RelationType_SizeIpv4)
    {
        s64 value = tree_getValue(temp_bin1);
        temp_length = doSizeIpv4Get(value);
    }

    return temp_length;
}

int do_relation_set(elementBinContent *tree)
{

    elementBinContent *treeValue = tree->relationValue;

    //只赋值一次，提高速度，减少以后内存比较的次数
    //必须是大儿子
    if (treeValue->typeRelation == RelationType_Unknow)
    {
        char* buf = treeValue->xml->bigChild->attribute_type;
        int length = mlib_strlen(treeValue->xml->bigChild->attribute_type);

        if ((length == 4)&&(mlib_memcmp("size",buf,4) == 0))
        {
            treeValue->typeRelation = RelationType_Size;
        }
        else if ((length == 7)&&(mlib_memcmp("sizeJpg",buf,7) == 0))
        {
            treeValue->typeRelation = RelationType_SizeJpg;
        }
        else if ((length == 10)&&(mlib_memcmp("sizeAddSub",buf,10) == 0))
        {
            treeValue->typeRelation = RelationType_SizeAddSub4;
        }
        else if ((length == 5)&&(mlib_memcmp("count",buf,5) == 0))
        {
            treeValue->typeRelation = RelationType_Count;
        }
        else if ((length == 10)&&(mlib_memcmp("sizeString",buf,10) == 0))
        {
            treeValue->typeRelation = RelationType_SizeString;
        }
        else if ((length == 8)&&(mlib_memcmp("sizeIpv4",buf,8) == 0))
        {
            treeValue->typeRelation = RelationType_SizeIpv4;
        }
        else
        {
            BF_printf("RelationType %s is unknow\r\n",tree->xml->bigChild->attribute_type);
            ASSERT("RelationType check failed\r\n");
        }
    }


    tree->typeRelation = treeValue->typeRelation;

    if (treeValue->typeRelation == RelationType_Size)
    {
        g_bufferFuzz.tempBufferLength = 0;
        tree_bufferValueGet(tree, 1);
        int value = doSizeSet(g_bufferFuzz.tempBufferLength);

        tree_setValue(treeValue, value);
    }

    if (treeValue->typeRelation == RelationType_SizeString)
    {
        g_bufferFuzz.tempBufferLength = 0;
        tree_bufferValueGet(tree, 1);
        int value = doSizeSet(g_bufferFuzz.tempBufferLength);

        tree_setValue(treeValue, value);
    }

    if (treeValue->typeRelation == RelationType_Count)
    {
        g_bufferFuzz.tempBufferLength = 0;
        int count = tree_bufferCountGet(tree);
        int value = doSizeSet(count);

        tree_setValue(treeValue, value);
    }

    if (treeValue->typeRelation == RelationType_SizeAddSub4)
    {
        g_bufferFuzz.tempBufferLength = 0;
        tree_bufferValueGet(tree, 1);
        int value = doSizeAddSub4Set(g_bufferFuzz.tempBufferLength);

        tree_setValue(treeValue, value);
    }

    if (treeValue->typeRelation == RelationType_SizeJpg)
    {
        g_bufferFuzz.tempBufferLength = 0;
        tree_bufferValueGet(tree, 1);
        int value = doSizeAddSub2Set(g_bufferFuzz.tempBufferLength);

        tree_setValue(treeValue, value);
    }

    if (treeValue->typeRelation == RelationType_SizeIpv4)
    {
        g_bufferFuzz.tempBufferLength = 0;

        tree_bufferValueGet(tree, 1);

        int value = doSizeIpv4Set(g_bufferFuzz.tempBufferLength);


        tree_setValue(treeValue, value);
    }
}

#ifdef __cplusplus
}
#endif

