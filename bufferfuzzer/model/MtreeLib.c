



#include "Model.h"

#ifdef __cplusplus
extern "C"{
#endif


elementBinContent* tree_relation_parent(elementBinContent *treebin, elementXmlContent *treexml)
{
    elementBinContent* temp_tree = treebin->parent;

    for(;temp_tree;)
    {

        if(temp_tree->xml == treexml)
            return temp_tree;

        temp_tree = temp_tree->parent;
    }

    ASSERT("tree_relation_parent not found\r\n");
    return NULL;
}


void free_xml(elementXmlContent *treexml)
{
    if (treexml->xml_value)
    {
        BF_free(treexml->xml_value);
        treexml->xml_value = NULL;
    }

    if (treexml->attribute_value)
    {
        BF_free(treexml->attribute_value);
        treexml->attribute_value = NULL;
    }
}

void tree_free_xml(elementXmlContent *treexml)
{
    elementXmlContent *temp_tree = treexml;
    elementXmlContent *temp_tree1;

    free_xml(treexml);

    if(temp_tree->bigChild)
    {
        tree_free_xml(temp_tree->bigChild);
    }

    temp_tree1 = temp_tree;
    temp_tree = temp_tree->littleBrother;
    BF_free(temp_tree1);

    for(;temp_tree;)
    {
        free_xml(temp_tree);

        if(temp_tree->bigChild)
        {
            tree_free_xml(temp_tree->bigChild);
        }

        temp_tree1 = temp_tree;
        temp_tree = temp_tree->littleBrother;
        BF_free(temp_tree1);
    }
}

void tree_free_xml1(elementXmlContent *treexml)
{
    elementXmlContent *temp_tree = treexml;
    elementXmlContent *temp_tree1;

    free_xml(treexml);

    if(temp_tree->bigChild)
    {
        tree_free_xml(temp_tree->bigChild);
    }

    temp_tree1 = temp_tree;
    temp_tree = temp_tree->littleBrother;
    //BF_free(temp_tree1);

    for(;temp_tree;)
    {
        free_xml(temp_tree);

        if(temp_tree->bigChild)
        {
            tree_free_xml(temp_tree->bigChild);
        }

        temp_tree1 = temp_tree;
        temp_tree = temp_tree->littleBrother;
        BF_free(temp_tree1);
    }
}

static void free_bin(elementBinContent *treebin)
{
    if (treebin->typeAnalyzer != 0)
    {
        do_analyzer_free(treebin);
    }

    if (treebin->value != NULL)
    {
        BF_free(treebin->value);
        treebin->value = NULL;
    }

    //��������Ȳ�֧�֣��Ժ� ������˵
    //if ((treebin->resolvedlTree != NULL) && (g_bufferFuzz.nolength_tree == NULL))
    //g_bufferFuzz.nolength_tree = treebin->resolvedlTree;

    //�����ͷ��ˣ������Ÿ���
    if (treebin == g_bufferFuzz.nolength_tree)
        g_bufferFuzz.nolength_tree = NULL;

    //if (treebin->xml_value)
    {
        //BF_free(treebin->xml_value);
        //treebin->xml_value = NULL;
    }
}


void tree_free_bin(elementBinContent *treebin)
{
    elementBinContent *temp_tree = treebin;
    elementBinContent *temp_tree1;

    free_bin(treebin);

    if(temp_tree->bigChild)
    {
        tree_free_bin(temp_tree->bigChild);
    }

    temp_tree1 = temp_tree;
    temp_tree = temp_tree->littleBrother;
    BF_free(temp_tree1);

    for(;temp_tree;)
    {

        free_bin(temp_tree);

        if(temp_tree->bigChild)
        {
            tree_free_bin(temp_tree->bigChild);
        }

        temp_tree1 = temp_tree;
        temp_tree = temp_tree->littleBrother;
        BF_free(temp_tree1);
    }
}

void tree_free_bin1(elementBinContent *treebin)
{
    elementBinContent *temp_tree = treebin;
    elementBinContent *temp_tree1;

    free_bin(treebin);

    if(temp_tree->bigChild)
    {
        tree_free_bin(temp_tree->bigChild);
    }

    temp_tree1 = temp_tree;
    temp_tree = temp_tree->littleBrother;
    //BF_free(temp_tree1);

    for(;temp_tree;)
    {

        free_bin(temp_tree);

        if(temp_tree->bigChild)
        {
            tree_free_bin(temp_tree->bigChild);
        }

        temp_tree1 = temp_tree;
        temp_tree = temp_tree->littleBrother;
        BF_free(temp_tree1);
    }
}

s64 tree_getValue(elementBinContent *tree)
{
    if ((tree->xml->type == ElementType_S8)
        ||((tree->xml->type == ElementType_Number) && (tree->value_length == 1))
        ||((tree->xml->type == ElementType_Bit) && (tree->value_length == 1))
        ||((tree->xml->type == ElementType_Bits) && (tree->value_length == 1)))
    {	
        //�����ֽ��򲻵����ⲿ�ֽ���
        if (isBigendian != tree->xml->isbigEndian)
            return *((s8*)tree->value);
        else
            return *((s8*)tree->value);
    }

    if ((tree->xml->type == ElementType_S16)
        ||((tree->xml->type == ElementType_Number) && (tree->value_length == 2))
        ||((tree->xml->type == ElementType_Bit) && (tree->value_length == 2))
        ||((tree->xml->type == ElementType_Bits) && (tree->value_length == 2)))
    {	
        if (isBigendian != tree->xml->isbigEndian)
            return BF_swap16(*((s16*)tree->value));
        else
            return *((s16*)tree->value);
    }

    if ((tree->xml->type == ElementType_S32)
        ||((tree->xml->type == ElementType_Number) && (tree->value_length == 4))
        ||((tree->xml->type == ElementType_Bit) && (tree->value_length == 4))
        ||((tree->xml->type == ElementType_Bits) && (tree->value_length == 4)))
    {	
        if (isBigendian != tree->xml->isbigEndian)
            return BF_swap32(*((s32*)tree->value));
        else
            return *((s32*)tree->value);
    }

    if ((tree->xml->type == ElementType_S64)
        ||((tree->xml->type == ElementType_Number) && (tree->value_length == 8))
        ||((tree->xml->type == ElementType_Bit) && (tree->value_length == 8))
        ||((tree->xml->type == ElementType_Bits) && (tree->value_length == 8)))
    {	
        if (isBigendian != tree->xml->isbigEndian)
            return BF_swap64(*((s64*)tree->value));
        else
            return *((s64*)tree->value);
    }

    if (tree->xml->type == ElementType_U8)
    {	
        if (isBigendian != tree->xml->isbigEndian)
            return *((u8*)tree->value);
        else
            return *((u8*)tree->value);
    }

    if (tree->xml->type == ElementType_U16)
    {	
        if (isBigendian != tree->xml->isbigEndian)
            return BF_swap16(*((u16*)tree->value));
        else
            return *((u16*)tree->value);
    }

    if (tree->xml->type == ElementType_U32)
    {	
        if (isBigendian != tree->xml->isbigEndian)
            return BF_swap32(*((u32*)tree->value));
        else
            return *((u32*)tree->value);
    }

    if (tree->xml->type == ElementType_U64)
    {	
        if (isBigendian != tree->xml->isbigEndian)
            return BF_swap64(*((u64*)tree->value));
        else
            return *((u64*)tree->value);
    }

    if (tree->xml->type == ElementType_String)
    {
        return mlib_atoi(tree->value);
    }

    return 0;
}

void tree_setValue(elementBinContent *tree, s64 value)
{
    if ((tree->xml->type == ElementType_S8)
        ||((tree->xml->type == ElementType_Number) && (tree->after_lenght== 1))
        ||((tree->xml->type == ElementType_Bit) && (tree->after_lenght == 1))
        ||((tree->xml->type == ElementType_Bits) && (tree->after_lenght == 1)))
    {	
        s8 temp = value;

        if (isBigendian != tree->xml->isbigEndian)
            temp = temp;

        *((s8*)tree->after_buf) = temp;
    }

    if ((tree->xml->type == ElementType_S16)
        ||((tree->xml->type == ElementType_Number) && (tree->after_lenght == 2))
        ||((tree->xml->type == ElementType_Bit) && (tree->after_lenght == 2))
        ||((tree->xml->type == ElementType_Bits) && (tree->after_lenght == 1)))
    {	
        s16 temp = value;

        if (isBigendian != tree->xml->isbigEndian)
            temp = BF_swap16(temp);

        *((s16*)tree->after_buf) = temp;
    }

    if ((tree->xml->type == ElementType_S32)
        ||((tree->xml->type == ElementType_Number) && (tree->after_lenght == 4))
        ||((tree->xml->type == ElementType_Bit) && (tree->after_lenght == 4))
        ||((tree->xml->type == ElementType_Bits) && (tree->after_lenght == 4)))
    {	
        s32 temp = value;

        if (isBigendian != tree->xml->isbigEndian)
            temp = BF_swap32(temp);

        *((s32*)tree->after_buf) = temp;
    }

    if ((tree->xml->type == ElementType_S64)
        ||((tree->xml->type == ElementType_Number) && (tree->after_lenght == 8))
        ||((tree->xml->type == ElementType_Bit) && (tree->after_lenght == 8))
        ||((tree->xml->type == ElementType_Bits) && (tree->after_lenght == 8)))
    {	
        s64 temp = value;

        if (isBigendian != tree->xml->isbigEndian)
            temp = BF_swap64(temp);

        *((s64*)tree->after_buf) = temp;
    }

    if (tree->xml->type == ElementType_U8)
    {	
        u8 temp = value;

        if (isBigendian != tree->xml->isbigEndian)
            temp =temp;

        *((u8*)tree->after_buf) = temp;
    }

    if (tree->xml->type == ElementType_U16)
    {	
        u16 temp = value;

        if (isBigendian != tree->xml->isbigEndian)
            temp = BF_swap16(temp);

        *((u16*)tree->after_buf) = temp;
    }

    if (tree->xml->type == ElementType_U32)
    {	
        u32 temp = value;

        if (isBigendian != tree->xml->isbigEndian)
            temp = BF_swap32(temp);

        *((u32*)tree->after_buf) = temp;
    }

    if (tree->xml->type == ElementType_U64)
    {	
        u64 temp = value;

        if (isBigendian != tree->xml->isbigEndian)
            temp = BF_swap64(temp);

        *((u64*)tree->after_buf) = temp;
    }

    if (tree->xml->type == ElementType_String)
    {	
        char str[16];
        str[0] = 0;
        //itoa(value,str,10);

        sprintf(str, "%ld" , value);

        int length = tree->after_lenght;

        if (mlib_strlen(str) < length)
            length = mlib_strlen(str);

        BF_memcpy(tree->after_buf, str, length);
    }

    return;
}


void tree_bufferCopy(elementBinContent *tree, int only_length)
{
    if (g_bufferFuzz.onoffDebugDo)
    {
        BF_printf("\r\n           name   is %s\r\n", tree->xml->attribute_name);
        BF_printf("           type   is %s\r\n", mlib_getTypeName(tree->xml->type));
        BF_printf("           length is %d\r\n", tree->after_lenght);
    }

    //һ����Ҫ������󳤶�
    if(tree->after_lenght + g_bufferFuzz.tempBufferLength < g_bufferFuzz.maxBufferLength)
    {
        if(only_length == 0)
            BF_memcpy(g_bufferFuzz.tempBuffer + g_bufferFuzz.tempBufferLength, tree->after_buf, tree->after_lenght);
                g_bufferFuzz.tempBufferLength = g_bufferFuzz.tempBufferLength + tree->after_lenght;
    }

    else if (g_bufferFuzz.tempBufferLength < g_bufferFuzz.maxBufferLength)
    {
        if(only_length == 0)
            BF_memcpy(g_bufferFuzz.tempBuffer + g_bufferFuzz.tempBufferLength, tree->after_buf, g_bufferFuzz.maxBufferLength - tree->after_lenght);
                g_bufferFuzz.tempBufferLength = g_bufferFuzz.maxBufferLength;
    }
}

static void tree_bufferChildValueGet(elementBinContent *tree, int only_length)
{
    elementBinContent *temp_tree = tree->bigChild;

    tree_bufferCopy(temp_tree, only_length);

    //����߶���δ����Ҫ��ȥ
    if(temp_tree->bigChild 
        && (temp_tree->after_lenght == 0))
    {
        tree_bufferChildValueGet(temp_tree, only_length);
    }

    temp_tree = temp_tree->littleBrother;

    for(;temp_tree;)
    {
        //�ֵ�
        tree_bufferCopy(temp_tree, only_length);

        if(temp_tree->bigChild 
            && (temp_tree->after_lenght == 0))
        {
            tree_bufferChildValueGet(temp_tree, only_length);
        }

        temp_tree = temp_tree->littleBrother;
    }
}


void tree_bufferValueGet(elementBinContent *tree, int only_length)
{
    elementBinContent *temp_tree = tree;

    //�Լ�
    tree_bufferCopy(temp_tree, only_length);

    if ((temp_tree->after_lenght > 0))
        return;

    if (tree->bigChild)
        tree_bufferChildValueGet(tree, only_length);
}

int tree_bufferCountGet(elementBinContent *tree)
{
    elementBinContent *temp_tree = tree->bigChild;
    int count = 0;

    for(;temp_tree;)
    {
        count++;
        temp_tree = temp_tree->littleBrother;
    }

    return count;
}


static void tree_paddingCopy(elementBinContent *tree,int isAfter)
{
    //һ����Ҫ������󳤶�
    if (isAfter)
        g_bufferFuzz.tempBufferLength = g_bufferFuzz.tempBufferLength + tree->after_lenght;
    else
        g_bufferFuzz.tempBufferLength = g_bufferFuzz.tempBufferLength + tree->value_length;

}

static int tree_paddingChildValueGet(elementBinContent *tree, elementBinContent *padding,int isAfter)
{
    elementBinContent *temp_tree = tree->bigChild;

    if (temp_tree == padding)
        return 1;

    tree_paddingCopy(temp_tree,isAfter);

    //����߶���δ����Ҫ��ȥ
    if(temp_tree->bigChild 
        && (((isAfter == 1)&&(temp_tree->after_lenght == 0)) ||((isAfter == 0)&&(temp_tree->value_length == 0))))
    {
        if (tree_paddingChildValueGet(temp_tree, padding,isAfter))
            return 1;
    }

    temp_tree = temp_tree->littleBrother;

    for(;temp_tree;)
    {
        if (temp_tree == padding)
            return 1;

        //�ֵ�
        tree_paddingCopy(temp_tree,isAfter);

        if(temp_tree->bigChild 
            && (((isAfter == 1)&&(temp_tree->after_lenght == 0)) ||((isAfter == 0)&&(temp_tree->value_length == 0))))
        {
            if(tree_paddingChildValueGet(temp_tree, padding,isAfter))
                return 1;
        }

        temp_tree = temp_tree->littleBrother;
    }

    return 0;
}


int tree_isParent(elementBinContent *tree, elementBinContent *padding)
{
    elementBinContent *parent = padding->parent;
    if (parent)
    {
        if (parent == tree)
            return 1;
        else
            return tree_isParent(tree, parent);
    }

    return 0;
}

int tree_PaddingOffSetGet(elementBinContent *tree, elementBinContent *padding, int isAfter)
{
    elementBinContent *temp_tree = tree;

    g_bufferFuzz.tempBufferLength = 0;

    //�Լ�

    if (tree_isParent(tree, padding) == 0)
        tree_paddingCopy(temp_tree, isAfter);
    //�����ȣ���ֱ�ӴӶ�������
    else if (tree_paddingChildValueGet(temp_tree, padding, isAfter))
        return g_bufferFuzz.tempBufferLength;

    //����
    if(temp_tree->bigChild 
        && (((isAfter == 1)&&(temp_tree->after_lenght == 0)) ||((isAfter == 0)&&(temp_tree->value_length == 0))))
    {
        if (tree_paddingChildValueGet(temp_tree, padding, isAfter))
            return g_bufferFuzz.tempBufferLength;
    }

    temp_tree = temp_tree->littleBrother;

    //�ֵ�
    for(;temp_tree;)
    {
        if (temp_tree == padding)
            return g_bufferFuzz.tempBufferLength;


        tree_paddingCopy(temp_tree,isAfter);

        if(temp_tree->bigChild 
            && (((isAfter == 1)&&(temp_tree->after_lenght == 0)) ||((isAfter == 0)&&(temp_tree->value_length == 0))))
        {
            if(tree_paddingChildValueGet(temp_tree, padding, isAfter))
            return g_bufferFuzz.tempBufferLength;
        }

        temp_tree = temp_tree->littleBrother;
    }

    //�Ҳ����ǲ��Ե�
    BF_printf("padding %s setget \r\n",tree->xml->attribute_name);
    ASSERT("tree_PaddingOffSetGet  error\r\n");
}


static int isXmlNameSame(elementXmlContent *tree, char *name, int type) 
{
    //BF_printf("isXmlNameSame  %s     %s      %d   %d \r\n",tree->attribute_name, name, type, tree->isRelationValue);

    if ((type == 1) && (tree->isRelationValue == 0))
        return 0;

    if(mlib_strcmp(tree->attribute_name,name) == 0)
        return 1;

    if(mlib_strlen(tree->attribute_refOK) 
    && (mlib_strcmp(tree->attribute_refOK,name) == 0))
        return 1;


    if(mlib_strlen(tree->attribute_refOK1) 
    && (mlib_strcmp(tree->attribute_refOK1,name) == 0))
        return 1;


    if(mlib_strlen(tree->attribute_refOK2) 
    && (mlib_strcmp(tree->attribute_refOK2,name) == 0))
        return 1;


    if(mlib_strlen(tree->attribute_refOK3) 
    && (mlib_strcmp(tree->attribute_refOK3,name) == 0))
        return 1;

    return 0;
}


//xml��bin�Ĳ��ҹ������һ��
elementBinContent* found_relationOfBinBlob(elementBinContent *tree, char *name, int type)
{
    //�����ֵܣ����Ҹ���   �����ֵܵĶ��ӣ����ø��׵ݹ�
    elementBinContent *temp_tree = tree;

    //�ֵ�
    temp_tree = temp_tree->littleBrother;
    for(;temp_tree;)
    {
        if(isXmlNameSame(temp_tree->xml,name, type))
            return temp_tree;

        temp_tree = temp_tree->littleBrother;
    }

    //����
    temp_tree = tree->parent;
    if(isXmlNameSame(temp_tree->xml,name, type))
    {
        return temp_tree;
    }

    //�ֵܵĶ���
    temp_tree = tree->littleBrother;
    for(;temp_tree;)
    {
        elementBinContent *temp_tree1 = temp_tree->bigChild;
        for(;temp_tree1;)
        {
            if(isXmlNameSame(temp_tree1->xml,name, type))
                return temp_tree1;

            temp_tree1 = temp_tree1->littleBrother;
        }

        temp_tree = temp_tree->littleBrother;
    }


    //�ֵܵ�����
    temp_tree = tree->littleBrother;
    for(;temp_tree;)
    {
        elementBinContent *temp_tree1 = temp_tree->bigChild;
        for(;temp_tree1;)
        {
            elementBinContent *temp_tree2 = temp_tree1->bigChild;
            for(;temp_tree2;)
            {
                if(isXmlNameSame(temp_tree2->xml,name, type))
                    return temp_tree2;

                temp_tree2 = temp_tree2->littleBrother;
            }

            temp_tree1 = temp_tree1->littleBrother;
        }

        temp_tree = temp_tree->littleBrother;
    }


    if(tree->parent)
        return found_relationOfBinBlob(tree->parent, name, type);

    //
    BF_printf("padding %s found %s \r\n",tree->xml->attribute_name, name);
    ASSERT("found_relationOfBinBlob, notfound\r\n");
    return NULL;

}


//�������� 
elementBinContent* found_relation_all_child(elementBinContent *tree, elementBinContent *me, char *name ,int type)
{
    elementBinContent *temp_tree = tree->bigChild;

    for(;temp_tree;)
    {
        if( (isXmlNameSame(temp_tree->xml, name, type)) 
        && (found_relationOfBinBlob(temp_tree, me->xml->attribute_name, 0) == me))
            return temp_tree;

        if(temp_tree->bigChild)
        {
            elementBinContent *temp_tree111 = found_relation_all_child(temp_tree, me ,name, type);

            if (temp_tree111)
                return temp_tree111;
        }

        temp_tree = temp_tree->littleBrother;
    }

    return NULL;

}

// 1 isRelationValue  ������˵
elementBinContent* found_relationOfBinValue(elementBinContent *tree, elementBinContent *me, char *name, int type)
{
    //���ж���
    elementBinContent *temp_tree111 = found_relation_all_child(tree, me, name, type);

    if (temp_tree111)
        return temp_tree111;

    //���и��
    elementBinContent *temp_tree = tree->bigBrother;
    for(;temp_tree;)
    {
        if((isXmlNameSame(temp_tree->xml,name, type)) 
        && (found_relationOfBinBlob(temp_tree, me->xml->attribute_name, 0) == me))
            return temp_tree;

        if(temp_tree->bigChild)
        {
            elementBinContent *temp_tree111 = found_relation_all_child(temp_tree, me, name, type);

            if (temp_tree111)
                return temp_tree111;
        }

        temp_tree = temp_tree->bigBrother;
    }

    if(tree->parent)
    {	
        return found_relationOfBinValue(tree->parent, me, name, type);
    }

    //
    BF_printf("padding %s found %s \r\n",tree->xml->attribute_name, name);
    ASSERT("found_relationOfBinValue, notfound\r\n");
    return NULL;
	
}


elementXmlContent* found_relationOfXmlBlob(elementXmlContent *tree, int* isParent, char *name)
{
    //�����ֵܣ����Ҹ���   �����ֵܵĶ��ӣ����ø��׵ݹ�
    elementXmlContent *temp_tree = tree;

    //�ֵ�
    temp_tree = temp_tree->littleBrother;
    for(;temp_tree;)
    {
        if(isXmlNameSame(temp_tree,name, 0))
            return temp_tree;

        temp_tree = temp_tree->littleBrother;
    }


    //����
    temp_tree = tree->parent;
    if(isXmlNameSame(temp_tree,name, 0))
    {
        *isParent = 1;
        return temp_tree;
    }

    //�ֵܵĶ���
    temp_tree = tree->littleBrother;
    for(;temp_tree;)
    {
        elementXmlContent *temp_tree1 = temp_tree->bigChild;
        for(;temp_tree1;)
        {
            if(isXmlNameSame(temp_tree1,name, 0))
                return temp_tree1;

            temp_tree1 = temp_tree1->littleBrother;
        }

        temp_tree = temp_tree->littleBrother;
    }

    //�ֵܵ�����?
    temp_tree = tree->littleBrother;
    for(;temp_tree;)
    {
        elementXmlContent *temp_tree1 = temp_tree->bigChild;
        for(;temp_tree1;)
        {
            elementXmlContent *temp_tree2 = temp_tree1->bigChild;
            for(;temp_tree2;)
            {
                if(isXmlNameSame(temp_tree2,name, 0))
                    return temp_tree2;

                temp_tree2 = temp_tree2->littleBrother;
            }

            temp_tree1 = temp_tree1->littleBrother;
        }

        temp_tree = temp_tree->littleBrother;
    }

    if(tree->parent)
        return found_relationOfXmlBlob(tree->parent, isParent, name);

    //
    BF_printf("relation %s found %s \r\n",tree->attribute_name, name);
    ASSERT("found_relationOfXmlBlob, notfound\r\n");
    return NULL;

}


elementBinContent* found_relationOfPadding(elementBinContent *tree, char *name)
{
    //
    elementBinContent *temp_tree = tree;

    //���
    temp_tree = temp_tree->bigBrother;
    for(;temp_tree;)
    {
        if(isXmlNameSame(temp_tree->xml,name, 0))
            return temp_tree;

        temp_tree = temp_tree->bigBrother;
    }

    //���Ķ��Ӹо�����Ҫ��   ��Ҫ���ڼ�


    //����
    temp_tree = tree->parent;
    if(isXmlNameSame(temp_tree->xml,name, 0))
    {
        return temp_tree;
    }

    if(tree->parent)
        return found_relationOfPadding(tree->parent, name);

    //
    BF_printf("padding %s found %s \r\n",tree->xml->attribute_name, name);
    ASSERT("found_relationOfPadding, notfound\r\n");
    return NULL;

}


#ifdef __cplusplus
}
#endif

