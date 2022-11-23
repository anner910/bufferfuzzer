



#include "Model.h"



#ifdef __cplusplus
extern "C"{
#endif


//这里的变异慢慢优化吧
//先解决有无的问题
// 与codefuzz联动以后再说
static int do_bufferChildValueGet(elementBinContent *tree, int count, int id)
{
    elementBinContent *temp_tree = tree->bigChild;

    for(;temp_tree;)
    {
        if((g_bufferFuzz.isdeleteElement[id] == 1)&&(count == g_bufferFuzz.element_no[id]))
        {
            g_bufferFuzz.isdeleteElement[id] = 0;
            ;
        }
        else
        {
            tree_bufferCopy(temp_tree, 0);
            if((g_bufferFuzz.iscopyElement[id] == 1)&&(count == g_bufferFuzz.element_no[id]))
            {
                g_bufferFuzz.iscopyElement[id] = 0;
                tree_bufferCopy(temp_tree, 0);
            }
        }

        if ((g_bufferFuzz.isinsertget[id] == 1) && (count == g_bufferFuzz.element_no[id]))
        {
            g_bufferFuzz.isinsertget[id] = 0;
            g_bufferFuzz.insert_tree[id] = temp_tree;
        }

        if ((g_bufferFuzz.isinsertset[id] == 1) && (count == g_bufferFuzz.element_no[id]))
        {
            g_bufferFuzz.isinsertset[id] = 0;
            if (g_bufferFuzz.insert_tree[id])
                tree_bufferCopy(g_bufferFuzz.insert_tree[id], 0);
        }

        count ++;

        if(temp_tree->bigChild 
            && (temp_tree->after_lenght == 0))
        {
            if((g_bufferFuzz.isdeleteStruct[id] == 1)&&(count == g_bufferFuzz.element_no[id]))
            {
                g_bufferFuzz.isdeleteStruct[id] = 0;
                ;
            }
            else
            {
                count = do_bufferChildValueGet(temp_tree, count, id);
                if((g_bufferFuzz.iscopyStruct[id] == 1)&&(count == g_bufferFuzz.element_no[id]))
                {
                    g_bufferFuzz.iscopyStruct[id] = 0;
                    do_bufferChildValueGet(temp_tree, count, id);
                }
            }

            if ((g_bufferFuzz.isinsertget[id] == 1) && (count == g_bufferFuzz.element_no[id]))
            {
                g_bufferFuzz.isinsertget[id] = 0;
                g_bufferFuzz.insert_tree[id] = temp_tree;
            }

            if ((g_bufferFuzz.isinsertset[id] == 1) && (count == g_bufferFuzz.element_no[id]))
            {
                g_bufferFuzz.isinsertset[id] = 0;
                if (g_bufferFuzz.insert_tree[id])
                    do_bufferChildValueGet(g_bufferFuzz.insert_tree[id], 0, id);
            }

            count ++;
        }
        temp_tree = temp_tree->littleBrother;
    }

    return count;
}


void do_bufferFuzzClear(int id)
{
    g_bufferFuzz.isdeleteElement[id] = 0;
    g_bufferFuzz.isdeleteStruct[id] = 0;
    g_bufferFuzz.iscopyElement[id] = 0;
    g_bufferFuzz.iscopyStruct[id] = 0;
    g_bufferFuzz.isinsertget[id] = 0;
    g_bufferFuzz.isinsertset[id] = 0;
    g_bufferFuzz.insert_tree[id] = NULL;
    g_bufferFuzz.element_no[id] = 0;
    g_bufferFuzz.element_count[id] = 0;
}


static void do_bufferFuzzPrepare(int id)
{
    g_bufferFuzz.isdeleteElement[id] = 0;
    g_bufferFuzz.isdeleteStruct[id] = 0;
    g_bufferFuzz.iscopyElement[id] = 0;
    g_bufferFuzz.iscopyStruct[id] = 0;
    g_bufferFuzz.isinsertget[id] = 0;
    g_bufferFuzz.isinsertset[id] = 0;

    int seed = CF_GetCorpusRandom();

    if (seed != 0)
    {
        BF_seed(seed);
        //百分之十用做模型变异

        int weight = BF_random()% 100;
        if (weight < 10)
        {
            if (weight == 1)
                g_bufferFuzz.isdeleteElement[id] = 1;

            if (weight == 2)
                g_bufferFuzz.isdeleteStruct[id] = 1;

            if ((weight == 3) || (weight == 4) || (weight == 5))
                g_bufferFuzz.iscopyElement[id] = 1;

            if ((weight == 6) || (weight == 7))
                g_bufferFuzz.iscopyStruct[id] = 1;

            if (weight == 8)
                g_bufferFuzz.isinsertget[id] = 1;

            if (weight == 9)
                g_bufferFuzz.isinsertset[id] = 1;

            g_bufferFuzz.element_no[id] = BF_random() % g_bufferFuzz.element_count[id];
        }
    }
	
}

static void do_bufferValueGet(elementBinContent *tree, int id)
{
    if (g_bufferFuzz.onoffBufferFuzz)
    {
        g_bufferFuzz.tempBufferLength = 0;
        if (g_bufferFuzz.element_count[id] == 0)
        {
            if (tree->bigChild)
                g_bufferFuzz.element_count[id] = do_bufferChildValueGet(tree, 0, id);
        }

        do_bufferFuzzPrepare(id);
    }

    g_bufferFuzz.tempBufferLength = 0;
    
    if (tree->bigChild)
        do_bufferChildValueGet(tree, 0, id);
}


void do_buffer(elementBinContent *tree, int id)
{
    do_bufferValueGet(tree, id);

    if (g_bufferFuzz.onoffDebugDo)
    {
        BF_printf("-------------------------------------------------------\r\n");
        BF_printf("                              buf       is %p\r\n", g_bufferFuzz.tempBuffer);
        BF_printf("                              length    is %d\r\n", g_bufferFuzz.tempBufferLength);

        BF_printf("-----------bin is :\r\n");
        mlib_printfData(g_bufferFuzz.tempBuffer, g_bufferFuzz.tempBufferLength);
    }
}


#ifdef __cplusplus
}
#endif

