

#include "Model.h"

#ifdef __cplusplus
extern "C"{
#endif

int parseXmlLine(char *buf, elementXmlContent *tree)
{
    //
    int type = Pc_notail;

    int k;

    //找开头
    k = mlib_findFirstLetter(buf, '<');

    //啥也没找到
    if (buf[k] == 0 )
    {
        buf[0] == 0;
        return Pc_no;
    }

    buf = buf + k + 1;

    //闭合符号先去不管他
    if (buf[0] == '/')
    {
        buf[0] == 0;
        return Pc_tail;
    }


    //找结尾
    k = mlib_findFirstLetter(buf, '>');

    //啥也没找到
    if (buf[k] == 0 )
    {
        buf[0] == 0;
        return Pc_no;
    }

    buf[k] = 0;

    if (buf[k - 1] == '/')
    {
        buf[k - 1] = 0;
        type = Pc_oneline;
    }

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("\r\nline is----------------%s\r\n" , buf);


    //找出类型字段

    k = mlib_findFirstSpace(buf);

    buf[k] = 0;

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("type      is-----%s\r\n",buf);
    //-------------------------
    parseXmlType(buf, tree);

    buf = buf + k + 1;

    int i = 0;

    while(buf[i] != 0)
    {
        k = mlib_findSecondQuotation(buf);

        if (k == -1)
            break;

        buf[k + 1] = 0;

        if (g_bufferFuzz.onoffDebugXml)
            BF_printf("attribute is-----%s\r\n",buf);
        
        //-------------------------
        parseXmlAttribute(buf,tree);

        buf = buf + k + 1 + 1;
    }

    return type;
}

#ifdef __cplusplus
}
#endif

