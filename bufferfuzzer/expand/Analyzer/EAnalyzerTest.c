
#include "../../model/Model.h"


#ifdef __cplusplus
extern "C"{
#endif

typedef struct AnalyzerTest AnalyzerTestContent;


struct AnalyzerTest {
    struct AnalyzerTest *next;
    char * value;	

    int    isNeedMutator;

    char * after_buf;
    int    after_lenght;
};

AnalyzerTestContent* do_test_Parse(char *value)
{
    int length = mlib_strlen(value);

    AnalyzerTestContent* return_bin = NULL;
    AnalyzerTestContent* bin = NULL;
    AnalyzerTestContent* temp_bin = NULL;

    while(length > 0)
    {
        int pos = mlib_searchMemory(",", 1, value, length);
        if (pos >= 0)
        {
            //value
            temp_bin = (AnalyzerTestContent *)BF_malloc(sizeof(AnalyzerTestContent));
            BF_memset(temp_bin, 0, sizeof(AnalyzerTestContent));

            temp_bin->value = BF_malloc(pos + 1);
            BF_memset(temp_bin->value, 0, pos + 1);
            BF_memcpy(temp_bin->value, value, pos);

            temp_bin->isNeedMutator = 1;

            if (bin == NULL)
            {
                bin = temp_bin;
                return_bin = temp_bin; 
            }
            else
            {
                bin->next = temp_bin;
                bin = temp_bin;
            }

            //,
            temp_bin = (AnalyzerTestContent *)BF_malloc(sizeof(AnalyzerTestContent));
            BF_memset(temp_bin, 0, sizeof(AnalyzerTestContent));

            temp_bin->value = BF_malloc(1 + 1);
            BF_memset(temp_bin->value, 0, 1 + 1);
            BF_memcpy(temp_bin->value, ",", 1);

            bin->next = temp_bin;
            bin = temp_bin;

            value = value + pos + 1;
            length = length - pos - 1;
        }

        else
        {
            //value
            temp_bin = (AnalyzerTestContent *)BF_malloc(sizeof(AnalyzerTestContent));
            BF_memset(temp_bin, 0, sizeof(AnalyzerTestContent));

            temp_bin->value = BF_malloc(length + 1);
            BF_memset(temp_bin->value, 0, length + 1);
            BF_memcpy(temp_bin->value, value, length);

            temp_bin->isNeedMutator = 1;

            if (bin == temp_bin)
            {
                bin = temp_bin;
                return_bin = temp_bin; 
            }
            else
            {
                bin->next = temp_bin;
                bin = temp_bin;

                value = value + length;
                length = 0;
            }
        }
    }

    return return_bin;
}


void do_test_before(elementBinContent *tree)
{
    tree->p1 = (char*)do_test_Parse(tree->value);
}


void do_test_call_fuzz(AnalyzerTestContent *json1)
{
    if(json1->isNeedMutator == 1)
    {
        json1->after_buf = CF_GetString(g_paraNo, json1->value, mlib_strlen(json1->value) + 1, 1, 1000);
        json1->after_lenght = CF_GetMutatorLen(g_paraNo++);
    }
    else
    {
        json1->after_buf = json1->value;
        json1->after_lenght = mlib_strlen(json1->value);
    }
}


void do_test_fuzz(AnalyzerTestContent *json1)
{
    AnalyzerTestContent *temp_tree = json1;

    for(;temp_tree;)
    {
        do_test_call_fuzz(temp_tree);
        temp_tree = temp_tree->next;
    }
}

void test_print(AnalyzerTestContent *tree)
{
    AnalyzerTestContent *temp_tree = tree;

    for(;temp_tree;)
    {
        BF_memcpy(g_bufferFuzz.tempBuffer + g_bufferFuzz.tempBufferLength, temp_tree->after_buf, temp_tree->after_lenght);
        g_bufferFuzz.tempBufferLength = g_bufferFuzz.tempBufferLength + temp_tree->after_lenght;

        temp_tree = temp_tree->next;
    }
}

int do_test(elementBinContent *tree)
{
    do_test_fuzz((AnalyzerTestContent *)tree->p1);

    if(tree->after_buf)
        BF_free(tree->after_buf);

    g_bufferFuzz.tempBufferLength = 0;

    test_print((AnalyzerTestContent *)tree->p1);

    tree->after_buf = BF_malloc(g_bufferFuzz.tempBufferLength);

    BF_memcpy(tree->after_buf, g_bufferFuzz.tempBuffer, g_bufferFuzz.tempBufferLength);
    tree->after_lenght = g_bufferFuzz.tempBufferLength;

    g_bufferFuzz.tempBufferLength = 0;
    return 1;
}

void do_test_after_free(elementBinContent *tree)
{
    AnalyzerTestContent* temp_tree = (AnalyzerTestContent*)tree->p1;

    AnalyzerTestContent* temp_bin = temp_tree;

    for(;temp_tree;)
    {
        //BF_free(temp_tree->after_buf);
        BF_free(temp_tree->value);
        temp_bin = temp_tree;
        temp_tree = temp_tree->next;
        BF_free(temp_bin);
    }
}


#ifdef __cplusplus
}
#endif

