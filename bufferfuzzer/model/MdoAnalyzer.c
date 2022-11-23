
#include "Model.h"


#ifdef __cplusplus
extern "C"{
#endif


//数据类型
enum AnalyzerType
{
    AnalyzerType_Json = 1, 
    AnalyzerType_Xml, 
    AnalyzerType_Test, 
};


static void found_analyzer1(elementBinContent *tree)
{
    //现在只支持json
    if(tree->xml->isAnalyzer == 1)
    {
        if (g_bufferFuzz.onoffDebugXml)
        {
            BF_printf("     -------type  is  %s \r\n",mlib_getTypeName(tree->xml->type));
            BF_printf("            name  is  %s \r\n",tree->xml->attribute_name);
            BF_printf("   Analyzer type  is  %s \r\n",tree->xml->bigChild->attribute_type);
        }

        char* type = tree->xml->bigChild->attribute_type;
        int length = mlib_strlen(type);

        if ((length==4)&&(mlib_memcmp("json",type,4)==0))
        {
            tree->typeAnalyzer = AnalyzerType_Json;

            do_json_before(tree);
        }


        if ((length==3)&&(mlib_memcmp("xml",type,3)==0))
        {
            tree->typeAnalyzer = AnalyzerType_Xml;

            do_xml_before(tree);
        }

        if ((length==4)&&(mlib_memcmp("test",type,4)==0))
        {
            tree->typeAnalyzer = AnalyzerType_Test;

            do_test_before(tree);
        }
    }
}


static void found_analyzer(elementBinContent *tree)
{
    elementBinContent *temp_tree = tree;
    found_analyzer1(tree);


    if(temp_tree->bigChild)
    {
        found_analyzer(temp_tree->bigChild);
    }

    temp_tree = temp_tree->littleBrother;

    for(;temp_tree;)
    {
        found_analyzer1(temp_tree);

        if(temp_tree->bigChild)
        {
            found_analyzer(temp_tree->bigChild);
        }

        temp_tree = temp_tree->littleBrother;
    }
}


void do_analyzer_before(elementBinContent *tree)
{
    found_analyzer(tree);
}

int do_analyzer_fuzz(elementBinContent *tree)
{
    if(tree->typeAnalyzer == AnalyzerType_Json)
    {
        return do_json(tree);
    }

    if(tree->typeAnalyzer == AnalyzerType_Xml)
    {
        return do_xml(tree);
    }

    if(tree->typeAnalyzer == AnalyzerType_Test)
    {
        return do_test(tree);
    }
}

void do_analyzer_free(elementBinContent *tree)
{
    if(tree->typeAnalyzer == AnalyzerType_Json)
    {
        do_json_after_free(tree);
    }

    if(tree->typeAnalyzer == AnalyzerType_Xml)
    {
        do_xml_after_free(tree);
    }

    if(tree->typeAnalyzer == AnalyzerType_Test)
    {
        do_test_after_free(tree);
    }
}

#ifdef __cplusplus
}
#endif

