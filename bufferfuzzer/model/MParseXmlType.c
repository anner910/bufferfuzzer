#include "Model.h"

#ifdef __cplusplus
extern "C"{
#endif


void parseXmlType(char* buf, elementXmlContent *tree)
{
    int length = mlib_strlen(buf);

    tree->type = ElementType_Unknown;

    if ((length==4)&&(mlib_memcmp("Blob",buf,4)==0))
    {
        tree->type = ElementType_Buf;
    }

    if ((length==3)&&(mlib_memcmp("Buf",buf,3)==0))
    {
        tree->type = ElementType_Buf;
    }

    if ((length==6)&&(mlib_memcmp("String",buf,6)==0))
    {
        tree->type = ElementType_String;
    }

    if ((length==6)&&(mlib_memcmp("Number",buf,6)==0))
    {
        tree->type = ElementType_Number;
    }

    if ((length==7)&&(mlib_memcmp("Padding",buf,7)==0))
    {
        tree->type = ElementType_Padding;
    }

    if ((length==4)&&(mlib_memcmp("Flag",buf,4)==0))
    {
        tree->type = ElementType_Bit;
    }

    if ((length==3)&&(mlib_memcmp("Bit",buf,3)==0))
    {
        tree->type = ElementType_Bit;
    }

    if ((length==2)&&(mlib_memcmp("S8",buf,2)==0))
    {
        tree->type = ElementType_S8;
    }

    if ((length==3)&&(mlib_memcmp("S16",buf,3)==0))
    {
        tree->type = ElementType_S16;
    }

    if ((length==3)&&(mlib_memcmp("S32",buf,3)==0))
    {
        tree->type = ElementType_S32;
    }

    if ((length==3)&&(mlib_memcmp("S64",buf,3)==0))
    {
        tree->type = ElementType_S64;
    }

    if ((length==2)&&(mlib_memcmp("U8",buf,2)==0))
    {
        tree->type = ElementType_U8;
    }

    if ((length==3)&&(mlib_memcmp("U16",buf,3)==0))
    {
        tree->type = ElementType_U16;
    }

    if ((length==3)&&(mlib_memcmp("U32",buf,3)==0))
    {
        tree->type = ElementType_U32;
    }

    if ((length==3)&&(mlib_memcmp("U64",buf,3)==0))
    {
        tree->type = ElementType_U64;
    }

    if ((length==5)&&(mlib_memcmp("Float",buf,5)==0))
    {
        tree->type = ElementType_Float;
    }

    if ((length==6)&&(mlib_memcmp("Double",buf,6)==0))
    {
        tree->type = ElementType_Double;
    }

    if ((length==5)&&(mlib_memcmp("Block",buf,5)==0))
    {
        tree->type = ElementType_Struct;
    }

    if ((length==6)&&(mlib_memcmp("Struct",buf,6)==0))
    {
        tree->type = ElementType_Struct;
    }

    if ((length==5)&&(mlib_memcmp("Flags",buf,5)==0))
    {
        tree->type = ElementType_Bits;
    }

    if ((length==4)&&(mlib_memcmp("Bits",buf,4)==0))
    {
        tree->type = ElementType_Bits;
    }

    if ((length==5)&&(mlib_memcmp("Array",buf,5)==0))
    {
        tree->type = ElementType_Array;
    }

    if ((length==6)&&(mlib_memcmp("Choice",buf,6)==0))
    {
        tree->type = ElementType_Union;
    }

    if ((length==5)&&(mlib_memcmp("Union",buf,5)==0))
    {
        tree->type = ElementType_Union;
    }

    if ((length== 8)&&(mlib_memcmp("Analyzer",buf,8)==0))
    {
        tree->type = ElementType_Analyzer;
    }

    if ((length== 8)&&(mlib_memcmp("Relation",buf,8)==0))
    {
        tree->type = ElementType_Relation;
    }

    if ((length== 5)&&(mlib_memcmp("Fixup",buf,5)==0))
    {
        tree->type = ElementType_Fixup;
    }

    if ((length== 5)&&(mlib_memcmp("Param",buf,5)==0))
    {
        tree->type = ElementType_Param;
    }

    if ((length== 9)&&(mlib_memcmp("Transform",buf,9)==0))
    {
        tree->type = ElementType_Transform;
    }

    if ((length==9)&&(mlib_memcmp("DataModel",buf,9)==0))
    {
        tree->type = ElementType_Buffer;
    }

    if ((length==6)&&(mlib_memcmp("Buffer",buf,6)==0))
    {
        tree->type = ElementType_Buffer;
    }

    if ((length==12)&&(mlib_memcmp("BufferFuzzer",buf,12)==0))
    {
        tree->type = ElementType_BufferFuzzer;
    }

    if ((length==8)&&(mlib_memcmp("Defaults",buf,8)==0))
    {
        tree->type = ElementType_Defaults;
    }

    if ((length==9)&&(mlib_memcmp("Configure",buf,9)==0))
    {
        tree->type = ElementType_Configure;
    }

}



#ifdef __cplusplus
}
#endif

