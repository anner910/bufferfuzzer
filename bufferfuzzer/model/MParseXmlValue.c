#include "Model.h"

#ifdef __cplusplus
extern "C"{
#endif


s64 get_number_from_str(elementXmlContent *tree, char* str)
{
    if((mlib_strlen(tree->attribute_valueType)>=3)&&(mlib_memcmp("hex",tree->attribute_valueType,3) == 0))
    {
        return mlib_strtol(str, NULL, 16);
    }

    return mlib_atoi(tree->attribute_value);
}

static void integration_value(elementXmlContent *tree, elementXmlContent *root)
{
    if (g_bufferFuzz.onoffDebugXml)
    {
    BF_printf("     -------type  is  %s \r\n",mlib_getTypeName(tree->type));
    BF_printf("            name  is  %s \r\n",tree->attribute_name);
    }



    //分配内存，到这里长度都有了   block这种没有的不管他
    if (tree->xml_length > 0)
    {
        char* attribute_value = NULL;

        if (tree->attribute_value)
        {
            attribute_value = parseXmlConfigure(root, tree->attribute_value);
        }

        tree->xml_value = BF_malloc(tree->xml_length);
        BF_memset(tree->xml_value, 0, tree->xml_length);

        if ((tree->type == ElementType_S8)
            ||((tree->type == ElementType_Number) && (tree->fixLength == 1))
            ||((tree->type == ElementType_Bit) && (tree->fixLength == 1)))
        {	
            if (attribute_value)
                *(s8*)tree->xml_value = get_number_from_str(tree, attribute_value);
            else
                *(s8*)tree->xml_value = 0;


            if (isBigendian != tree->isbigEndian)
                *(s8*)tree->xml_value = (*(s8*)tree->xml_value);
        }

        else if ((tree->type == ElementType_S16)
            ||((tree->type == ElementType_Number) && (tree->fixLength == 2))
            ||((tree->type == ElementType_Bit) && (tree->fixLength == 2)))
        {	
            if (attribute_value)
                *(s16*)tree->xml_value = get_number_from_str(tree, attribute_value);
            else
                *(s16*)tree->xml_value = 0;

            if (isBigendian != tree->isbigEndian)
                *(s16*)tree->xml_value = BF_swap16(*(s16*)tree->xml_value);
        }

        else if ((tree->type == ElementType_S32)
            ||((tree->type == ElementType_Number) && (tree->fixLength == 4))
            ||((tree->type == ElementType_Bit) && (tree->fixLength == 4)))
        {	
            if (attribute_value)
                *(s32*)tree->xml_value = get_number_from_str(tree, attribute_value);
            else
                *(s32*)tree->xml_value = 0;

            if (isBigendian != tree->isbigEndian)
                *(s32*)tree->xml_value = BF_swap32(*(s32*)tree->xml_value);
        }

        else if ((tree->type == ElementType_S64)
            ||((tree->type == ElementType_Number) && (tree->fixLength == 8))
            ||((tree->type == ElementType_Bit) && (tree->fixLength == 8)))
        {	
            if (attribute_value)
                *(s64*)tree->xml_value = get_number_from_str(tree, attribute_value);
            else
                *(s64*)tree->xml_value = 0;

            if (isBigendian != tree->isbigEndian)
                *(s64*)tree->xml_value = BF_swap64(*(s64*)tree->xml_value);
        }

        else if (tree->type == ElementType_U8)
        {	
            if (attribute_value)
                *(u8*)tree->xml_value = get_number_from_str(tree, attribute_value);
            else
                *(u8*)tree->xml_value = 0;

            if (isBigendian != tree->isbigEndian)
                *(u8*)tree->xml_value = (*(u8*)tree->xml_value);
        }

        else if (tree->type == ElementType_U16)
        {	
            if (attribute_value)
                *(u16*)tree->xml_value = get_number_from_str(tree, attribute_value);
            else
                *(u16*)tree->xml_value = 0;

            if (isBigendian != tree->isbigEndian)
                *(u16*)tree->xml_value = BF_swap16(*(u16*)tree->xml_value);
        }

        else if (tree->type == ElementType_U32)
        {
            if (attribute_value)
                *(u32*)tree->xml_value = get_number_from_str(tree, attribute_value);
            else
                *(u32*)tree->xml_value = 0;

            if (isBigendian != tree->isbigEndian)
                *(u32*)tree->xml_value = BF_swap32(*(u32*)tree->xml_value);
        }

        else if (tree->type == ElementType_U64)
        {	
            if (attribute_value)
                *(u64*)tree->xml_value = get_number_from_str(tree, attribute_value);
            else
                *(u64*)tree->xml_value = 0;

            if (isBigendian != tree->isbigEndian)
                *(u64*)tree->xml_value = BF_swap64(*(u64*)tree->xml_value);
        }

        else if (tree->type == ElementType_Float)
        {	
            if (attribute_value)
                *(float*)tree->xml_value = mlib_atoi(attribute_value);
            else
                *(float*)tree->xml_value = 0;
        }

        else if (tree->type == ElementType_Double)
        {	
            if (attribute_value)
                *(double*)tree->xml_value = mlib_atoi(attribute_value);
            else
                *(double*)tree->xml_value = 0;
        }

        //ElementType_String
        //ElementType_Buf
        else
        {
            if((mlib_strlen(tree->attribute_valueType)>=3)&&(mlib_memcmp("hex",tree->attribute_valueType,3) == 0))
            {
                tree->xml_length = mlib_stringToHex(attribute_value, mlib_strlen(attribute_value), tree->xml_value, NULL);

                if (tree->istoken == 1)
                    tree->fixLength = tree->xml_length;
            }

            else if((mlib_strlen(tree->attribute_valueType)>=4)&&(mlib_memcmp("ipv4",tree->attribute_valueType,4) == 0))
            {
                *(u32*)tree->xml_value = mlib_strToIp (attribute_value);
            }
            else
            {
                //实际长度不够的相当于补充0了
                if (attribute_value)
                {
                    BF_memcpy(tree->xml_value, attribute_value, mlib_strlen(attribute_value));
                }
            }
        }

        if (g_bufferFuzz.onoffDebugXml)
        {
            BF_printf("      xml_length  is  %d \r\n",tree->xml_length);
            mlib_printfData(tree->xml_value, tree->xml_length);
        }
    }
}


void parseXmlValue(elementXmlContent *tree, elementXmlContent *root)
{
    elementXmlContent *temp_tree = tree;
    integration_value(temp_tree, root);

    if(temp_tree->bigChild)
    {
        parseXmlValue(temp_tree->bigChild, root);
    }

    temp_tree = temp_tree->littleBrother;

    for(;temp_tree;)
    {
        integration_value(temp_tree, root);

        if(temp_tree->bigChild)
        {
            parseXmlValue(temp_tree->bigChild, root);
        }
        temp_tree = temp_tree->littleBrother;
    }
}


#ifdef __cplusplus
}
#endif

