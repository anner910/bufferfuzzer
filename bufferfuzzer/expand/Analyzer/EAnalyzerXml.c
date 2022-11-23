#include "../../model/Model.h"


#ifdef __cplusplus
extern "C"{
#endif

#ifdef BF_Mode_AnalyzerXml

#include "../../../test/testlib/libxml/tree.h"
#include "../../../test/testlib/libxml/parser.h"
#include "../../../test/testlib/libxml/xmlerror.h"


char* g_xmlTempMemory[10000];
int g_xmlTempMemoryCount = 0;

void do_xml_call_free(xmlNodePtr xml1, xmlNodePtr xml2)
{

    if(xml1->type == XML_TEXT_NODE)
    {
        if(xml1->content)
        {
            //也不知道咋释放内存，先这样吧
            g_xmlTempMemory[g_xmlTempMemoryCount++] = (char*)xml2->content;
        }
    }

    if(xml1->properties)
    {
        xmlAttr* temp_tree1 =	xml1->properties;
        xmlAttr* temp_tree2 =	xml2->properties;

        for(;temp_tree1;)
        {

            if(temp_tree1->children->content)
                g_xmlTempMemory[g_xmlTempMemoryCount++] = (char*)temp_tree2->children->content;

            temp_tree1 = temp_tree1->next;
            temp_tree2 = temp_tree2->next;
        }
    }
}

void do_xml_free(xmlNodePtr xml1, xmlNodePtr xml2)
{
    xmlNodePtr temp_tree1 = xml1;
    xmlNodePtr temp_tree2 = xml2;

    do_xml_call_free(temp_tree1, temp_tree2);

    if(temp_tree1->children)
    {
        do_xml_free(temp_tree1->children, temp_tree2->children);
    }

    temp_tree1 = temp_tree1->next;
    temp_tree2 = temp_tree2->next;

    for(;temp_tree1;)
    {
        do_xml_call_free(temp_tree1, temp_tree2);

        if(temp_tree1->children)
        {
            do_xml_free(temp_tree1->children, temp_tree2->children);
        }

        temp_tree1 = temp_tree1->next;
        temp_tree2 = temp_tree2->next;
    }
}


void do_xml_before(elementBinContent *tree)
{

    tree->p1 = (char*)xmlReadMemory(tree->value,mlib_strlen(tree->value) + 1,NULL,"utf8",XML_PARSE_RECOVER);
    tree->p2 = (char*)xmlReadMemory(tree->value,mlib_strlen(tree->value) + 1,NULL,"utf8",XML_PARSE_RECOVER);

    if(tree->p1 == NULL)
        BF_printf("xml prase error, must assert\r\n");

    xmlDocPtr p1 = 	(xmlDocPtr)tree->p1;
    xmlDocPtr p2 = 	(xmlDocPtr)tree->p2;
    do_xml_free((xmlNodePtr)p1, (xmlNodePtr)p2);

}

void do_xml_call_fuzz(xmlNodePtr xml1, xmlNodePtr xml2)
{

    if(xml1->type == XML_TEXT_NODE)
    {
        if(xml1->content)
        {
            xml2->content = CF_GetString(g_paraNo++, xml1->content, mlib_strlen(xml1->content) + 1, 1, 1000);
        }
    }

    if(xml1->properties)
    {

        xmlAttr* temp_tree1 =	xml1->properties;
        xmlAttr* temp_tree2 =	xml2->properties;

        for(;temp_tree1;)
        {

            if(temp_tree1->children->content)
                temp_tree2->children->content = 
                    CF_GetString(g_paraNo++, temp_tree1->children->content, mlib_strlen(temp_tree1->children->content) + 1, 1, 1000);

            temp_tree1 = temp_tree1->next;
            temp_tree2 = temp_tree2->next;
        }

    }

}

void do_xml_fuzz(xmlNodePtr xml1, xmlNodePtr xml2)
{
    xmlNodePtr temp_tree1 = xml1;
    xmlNodePtr temp_tree2 = xml2;

    do_xml_call_fuzz(temp_tree1, temp_tree2);

    if(temp_tree1->children)
    {
        do_xml_fuzz(temp_tree1->children, temp_tree2->children);
    }

    temp_tree1 = temp_tree1->next;
    temp_tree2 = temp_tree2->next;

    for(;temp_tree1;)
    {
        do_xml_call_fuzz(temp_tree1, temp_tree2);

        if(temp_tree1->children)
        {
            do_xml_fuzz(temp_tree1->children, temp_tree2->children);
        }

        temp_tree1 = temp_tree1->next;
        temp_tree2 = temp_tree2->next;
    }
}


//短时间去掉xml错误打印
void xmlGenericErrorDefaultFuncNone(void *ctx ATTRIBUTE_UNUSED, const char *msg, ...) {

}
extern xmlGenericErrorFunc xmlGenericError;

xmlGenericErrorFunc xmlGenericErrorTemp;


int do_xml(elementBinContent *tree)
{
    xmlDocPtr p1 = (xmlDocPtr)tree->p1;
    xmlDocPtr p2 = (xmlDocPtr)tree->p2;

    do_xml_fuzz((xmlNodePtr)p1, (xmlNodePtr)p2);

    if(tree->after_buf)
        BF_free(tree->after_buf);

    xmlGenericErrorTemp = xmlGenericError;
    xmlGenericError= xmlGenericErrorDefaultFuncNone;

    xmlDocDumpMemory((xmlDocPtr)tree->p2,(xmlChar **)(&tree->after_buf),&tree->after_lenght);

    xmlGenericError = xmlGenericErrorTemp;

    return 1;
}

void do_xml_after_free(elementBinContent *tree)
{
    if(tree->p1)
        xmlFreeDoc((xmlDocPtr)tree->p1);

    if(tree->p2)
        xmlFreeDoc((xmlDocPtr)tree->p2);
}


#else

void do_xml_before(elementBinContent *tree)
{


}

int do_xml(elementBinContent *tree)
{
    return 0;
}

void do_xml_after_free(elementBinContent *tree)
{


}


#endif


#ifdef __cplusplus
}
#endif

