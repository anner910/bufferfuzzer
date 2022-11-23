



#include "Model.h"

#ifdef __cplusplus
extern "C"{
#endif

//所有属性在这里解析
void parseXmlAttribute(char* buf, elementXmlContent *tree)
{

    //去掉多余的空格
    while(*buf == ' ')
    {
        buf ++;
    }

    int length = mlib_strlen(buf);

    int k1 = mlib_findFirstLetter(buf, '\"');
    int k2 = mlib_findSecondQuotation(buf);

    if ((length>=4)&&(mlib_memcmp("name",buf,4)==0))
    {
        BF_memcpy(tree->attribute_name, buf + k1 + 1, k2 - k1 - 1);
    }

    //--------

    if ((length>=6)&&(mlib_memcmp("length",buf,6)==0))
    {	
        BF_memcpy(tree->attribute_length, buf + k1 + 1, k2 - k1 - 1);
    }

    if ((length>=4)&&(mlib_memcmp("size",buf,4)==0))
    {	
        BF_memcpy(tree->attribute_size, buf + k1 + 1, k2 - k1 - 1);
    }

    if ((length>=9)&&(mlib_memcmp("alignment",buf,9)==0))
    {	
        BF_memcpy(tree->attribute_alignment, buf + k1 + 1, k2 - k1 - 1);
    }

    if ((length>=4)&&(mlib_memcmp("type",buf,4)==0))
    {	
        BF_memcpy(tree->attribute_type, buf + k1 + 1, k2 - k1 - 1);
    }

    //class == type
    if ((length>=5)&&(mlib_memcmp("class",buf,5)==0))
    {	
        BF_memcpy(tree->attribute_type, buf + k1 + 1, k2 - k1 - 1);
    }

    if ((length>=9)&&(mlib_memcmp("valueType",buf,9)==0))
    {	
        BF_memcpy(tree->attribute_valueType, buf + k1 + 1, k2 - k1 - 1);
    }
    else if ((length>=5)&&(mlib_memcmp("value",buf,5)==0))
    {	
        int length = k2 - k1 - 1;
        tree->attribute_value = BF_malloc(length + 1);
        BF_memset(tree->attribute_value, 0, length + 1);

        char * value = BF_malloc(length + 1);

        BF_memset(value, 0, length + 1);
        BF_memcpy(value, buf + k1 + 1, k2 - k1 - 1);

        //支持xml转义

        int i;
        int k = 0;
        int pos;
        for (i = 0; i < length + 1; i++ )
        {
            if (value[i] == '&')
            {
                if (mlib_searchMemory("&lt;", 4, value + i, length + 1 - i) == 0)
                {
                    tree->attribute_value[k++] = '<';
                    i = i + 4;
                    continue;
                }

                if (mlib_searchMemory("&gt;", 4, value + i, length + 1 - i) == 0)
                {
                    tree->attribute_value[k++] = '>';
                    i = i + 4;
                    continue;
                }

                if (mlib_searchMemory("&amp;", 5, value + i, length + 1 - i) == 0)
                {
                    tree->attribute_value[k++] = '&';
                    i = i + 5;
                    continue;
                }

                if (mlib_searchMemory("&apos;", 6, value + i, length + 1 - i) == 0)
                {
                    tree->attribute_value[k++] = '\'';
                    i = i + 6;
                    continue;
                }

                if (mlib_searchMemory("&quot;", 6, value + i, length + 1 - i) == 0)
                {
                    tree->attribute_value[k++] = '\"';
                    i = i + 6;
                    continue;
                }
            }

            tree->attribute_value[k++] = value[i];
        }

        BF_free(value);
    }

    if ((length>=2)&&(mlib_memcmp("of",buf,2)==0))
    {	
        BF_memcpy(tree->attribute_of, buf + k1 + 1, k2 - k1 - 1);
    }

    if ((length>=5)&&(mlib_memcmp("token",buf,5)==0))
    {	
        BF_memcpy(tree->attribute_token, buf + k1 + 1, k2 - k1 - 1);
    }

    if ((length>=5)&&(mlib_memcmp("check",buf,5)==0))
    {	
        BF_memcpy(tree->attribute_check, buf + k1 + 1, k2 - k1 - 1);
    }

    if ((length>=10)&&(mlib_memcmp("constraint",buf,10)==0))
    {	
        BF_memcpy(tree->attribute_check, buf + k1 + 1, k2 - k1 - 1);
    }

    if ((length>=8)&&(mlib_memcmp("position",buf,8)==0))
    {	
        BF_memcpy(tree->attribute_position, buf + k1 + 1, k2 - k1 - 1);
    }

    if ((length>=3)&&(mlib_memcmp("ref",buf,3)==0))
    {	
        BF_memcpy(tree->attribute_ref, buf + k1 + 1, k2 - k1 - 1);
    }

    if ((length>=3)&&(mlib_memcmp("ref",buf,3)==0))
    {	
        BF_memcpy(tree->attribute_ref, buf + k1 + 1, k2 - k1 - 1);
    }

    if ((length>=6)&&(mlib_memcmp("endian",buf,6)==0))
    {	
        BF_memcpy(tree->attribute_endian, buf + k1 + 1, k2 - k1 - 1);
    }

    if ((length>=5)&&(mlib_memcmp("count",buf,5)==0))
    {	
        BF_memcpy(tree->attribute_count, buf + k1 + 1, k2 - k1 - 1);
    }

    if ((length>=8)&&(mlib_memcmp("minCount",buf,8)==0))
    {	
        BF_memcpy(tree->attribute_minCount, buf + k1 + 1, k2 - k1 - 1);
    }

    if ((length>=8)&&(mlib_memcmp("maxCount",buf,8)==0))
    {	
        BF_memcpy(tree->attribute_maxCount, buf + k1 + 1, k2 - k1 - 1);
    }

    if ((length>=6)&&(mlib_memcmp("occurs",buf,6)==0))
    {	
        BF_memcpy(tree->attribute_count, buf + k1 + 1, k2 - k1 - 1);
    }

    if ((length>=9)&&(mlib_memcmp("minOccurs",buf,9)==0))
    {	
        BF_memcpy(tree->attribute_minCount, buf + k1 + 1, k2 - k1 - 1);
    }

    if ((length>=9)&&(mlib_memcmp("maxOccurs",buf,9)==0))
    {	
        BF_memcpy(tree->attribute_maxCount, buf + k1 + 1, k2 - k1 - 1);
    }

    if ((length>=7)&&(mlib_memcmp("mutator",buf,7)==0))
    {	
        BF_memcpy(tree->attribute_mutator, buf + k1 + 1, k2 - k1 - 1);
    }
}


#ifdef __cplusplus
}
#endif

