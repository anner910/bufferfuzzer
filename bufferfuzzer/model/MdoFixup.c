


#include "Model.h"


#ifdef __cplusplus
extern "C"{
#endif

//fixup目前不做解析bin校验  不知道以后有没有必要 

//数据类型
enum FixupType
{
    FixupType_Unknow = 0,
    FixupType_Crc32 = 1, 
    FixupType_IcmpCheckSum = 2, 
};


//找到之后 ，互相指引

void found_fixup1(elementXmlContent *tree)
{
    if(tree->type == ElementType_Fixup)
    {

        int isParent = 0;
        elementXmlContent* temp1 = found_relationOfXmlBlob(tree->parent, &isParent, tree->attribute_para1);

        if (isParent == 1)
        {
            tree->parent->isFixupParent = 1;
            temp1->isFixupParent = 1;
        }

        if (g_bufferFuzz.onoffDebugXml)
        {
            BF_printf("-------value type  is  %s \r\n",mlib_getTypeName(tree->parent->type));
            BF_printf("             name  is  %s \r\n",tree->parent->attribute_name);

            BF_printf(" -------blob type  is  %s \r\n",mlib_getTypeName(temp1->type));
            BF_printf("             name  is  %s \r\n",temp1->attribute_name);

            BF_printf("             type  is  %s \r\n",tree->attribute_type);
            BF_printf("         isParent  is  %d \r\n",isParent);
        }

        temp1->isFixupBlob = 1;
        tree->parent->isFixupValue = 1;

        tree->parent->fixupBlob = temp1;
        temp1->fixupValue = tree->parent;

    }
}

void found_fixup(elementXmlContent *tree)
{
    elementXmlContent *temp_tree = tree;

    found_fixup1(tree);

    if(temp_tree->bigChild)
    {
        found_fixup(temp_tree->bigChild);
    }

    temp_tree = temp_tree->littleBrother;

    for(;temp_tree;)
    {
        found_fixup1(temp_tree);

        if(temp_tree->bigChild)
        {
            found_fixup(temp_tree->bigChild);
        }

        temp_tree = temp_tree->littleBrother;
    }
}

void do_fixup_before(elementXmlContent *tree)
{
    found_fixup(tree);
}

//----------------------------------------------


void do_fixup_set(elementBinContent *tree)
{
    //只赋值一次，提高速度，减少以后内存比较的速度
    //fixup必须是大儿子
    if (tree->typeFixup == FixupType_Unknow)
    {
        char* buf = tree->xml->bigChild->attribute_type;
        int length = mlib_strlen(tree->xml->bigChild->attribute_type);

        if ((length == 5)&&(mlib_memcmp("crc32",buf,5) == 0))
        {
            tree->typeFixup = FixupType_Crc32;
        }
        else if ((length == 12)&&(mlib_memcmp("icmpChecksum", buf, 12) == 0))
        {
            tree->typeFixup = FixupType_IcmpCheckSum;
        }
        else
        {
            BF_printf("FixupType %s is unknow\r\n",tree->xml->bigChild->attribute_type);
            ASSERT("FixupType check failed\r\n");
        }
    }

    //
    if (tree->typeFixup == FixupType_Crc32)
    {
        doCrc32(tree, tree->fixupBlob);
    }

    if (tree->typeFixup == FixupType_IcmpCheckSum)
    {
        doIcmpCheckSum(tree, tree->fixupBlob);
    }
}

//看样子这样查找是不对的，得改
//和部分应该要改，应该和relation统一管理
void do_fixup_after(elementBinContent *treevalue,elementBinContent *treeBlob)
{
    //没有就去找，只找一次比较节省时间
    if (treevalue)
    {
        if (treevalue->fixupBlob == NULL)
        {
            treevalue->fixupBlob = found_relationOfBinBlob(treevalue, treevalue->xml->fixupBlob->attribute_name, 0);
            treevalue->fixupBlob->fixupValue = treevalue;

            do_fixup_set(treevalue);
        }
    }

    if (treeBlob)
    {
        if (treeBlob->fixupValue == NULL)
        {
            treeBlob->fixupValue = found_relationOfBinValue(treeBlob, treeBlob, treeBlob->xml->fixupValue->attribute_name, 0);
            treeBlob->fixupValue->fixupBlob = treeBlob;

            do_fixup_set(treeBlob->fixupValue);
        }
    }
}


#ifdef __cplusplus
}
#endif


