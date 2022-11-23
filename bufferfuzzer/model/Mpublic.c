#include "Model.h"


#ifdef __cplusplus
extern "C"{
#endif


SBufferFuzz g_bufferFuzz =
{
    .onoffDebugXml = 1, 
    .maxElementLength = 10000,
    .maxBufferLength = 10000000,

    .onoffBufferFuzz = 1,
};


char* g_user_buffer[Max_Buf_Number] = {0};


void IO_readFile(char* path, char** buf, int* len);

void bufferSetBuffer(int id, char* buf, int length)
{
    g_bufferFuzz.userBinBuf[id] = buf;
    g_bufferFuzz.userBinBufLength[id] = length;
}

void bufferDoModel(int id, char* modelPath, char* BinPath, char* DataModelName)
{
    char *file = NULL;
    char* temp;
    int length = 0;

    if (g_bufferFuzz.tempBuffer == NULL)
        g_bufferFuzz.tempBuffer = BF_malloc(g_bufferFuzz.maxBufferLength);

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("***************##BufferFuzz v.1.0.0 2022-11-23##**************\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("start prase xml file\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("model->tree->other->length->relation->value-bin->analyzer\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("modelPath %s;BinPath %s;DataModelName %s\r\n",modelPath,BinPath,DataModelName);

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("**************************************************************\r\n");

    IO_readFile(modelPath,&file,&length);
    if (length <= 0)
    {
        BF_printf("mode file is %s\r\n", modelPath);
        ASSERT("modelPath read error\r\n");
    }

    temp = file;

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("\r\n\r\n**************************************************************\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("start prase xml model file %p length %d\r\n", file, length);

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("**************************************************************\r\n");

    parseXmlModel(&g_bufferFuzz.treeXml[id], &file, &length);
    BF_free(temp);
    temp = NULL;

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("\r\n\r\n**************************************************************\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("start prase Defaults\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("**************************************************************\r\n");

    parseXmlDefaults(g_bufferFuzz.treeXml[id]);

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("\r\n\r\n**************************************************************\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("start prase xml ref\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("**************************************************************\r\n");

    parseXmlRef(g_bufferFuzz.treeXml[id], g_bufferFuzz.treeXml[id]);

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("\r\n\r\n**************************************************************\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("start prase xml tree\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("**************************************************************\r\n");

    parseXmlTree(g_bufferFuzz.treeXml[id]);

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("\r\n\r\n**************************************************************\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("start prase xml other\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("**************************************************************\r\n");

    parseXmlOther(g_bufferFuzz.treeXml[id]);

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("\r\n\r\n**************************************************************\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("start prase xml length\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("**************************************************************\r\n");

    parseXmlLength(g_bufferFuzz.treeXml[id], g_bufferFuzz.treeXml[id]);

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("\r\n\r\n**************************************************************\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("start prase xml relation\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("**************************************************************\r\n");

    do_relation_before(g_bufferFuzz.treeXml[id]);

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("\r\n\r\n**************************************************************\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("start prase xml fixup\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("**************************************************************\r\n");

    do_fixup_before(g_bufferFuzz.treeXml[id]);

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("\r\n\r\n**************************************************************\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("start prase xml value\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("**************************************************************\r\n");

    //搞完relation才能搞value  目前先不和relation联动
    parseXmlValue(g_bufferFuzz.treeXml[id], g_bufferFuzz.treeXml[id]);

    if (g_bufferFuzz.userBinBuf[id])
    {
        file = g_bufferFuzz.userBinBuf[id];
        length = g_bufferFuzz.userBinBufLength[id];
    }
    else if (BinPath)
    {
        IO_readFileRaw(BinPath,&file,&length);
        temp = file;

        if (length == 0)
        {
            BF_printf("bin file is %s\r\n",BinPath);
            ASSERT("Open bin file failed\r\n");
        }
    }
    else
    {
        file = NULL;
        length = 0;
        temp = file;
    }

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("\r\n\r\n**************************************************************\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("start prase bin, length is %d\r\n", length);

    if ((g_bufferFuzz.onoffDebugXml)&&(file))
        diag_dump_buf(file, length);

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("**************************************************************\r\n");

    parseBin(g_bufferFuzz.treeXml[id], DataModelName,file, length, &g_bufferFuzz.treeBin[id]);

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("\r\n\r\n**************************************************************\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("start prase analyzer\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("**************************************************************\r\n");

    do_analyzer_before(g_bufferFuzz.treeBin[id]);

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("\r\n\r\n**************************************************************\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("end prase xml file\r\n");

    if (g_bufferFuzz.onoffDebugXml)
        BF_printf("**************************************************************\r\n");

    if(temp)
        BF_free(temp);

    g_bufferFuzz.g_isPrint[id] = 0;
    do_bufferFuzzClear(id);
}

void bufferDoAction(int id, char ** buf,int* length)
{
    if (id == 0)
        g_paraNo = 0;

    if (g_bufferFuzz.onoffDebugDo)
        BF_printf("\r\n\r\n#########################################################\r\n");

    if (g_bufferFuzz.onoffDebugDo)
        BF_printf("start do\r\n");

    if (g_bufferFuzz.onoffDebugDo)
        BF_printf("fuzz->after->buffer\r\n");

    if (g_bufferFuzz.onoffDebugDo)
        BF_printf("#########################################################\r\n");

    if (g_bufferFuzz.onoffDebugDo)
        BF_printf("\r\n\r\n#########################################################\r\n");

    if (g_bufferFuzz.onoffDebugDo)
        BF_printf("start fuzz\r\n");

    if (g_bufferFuzz.onoffDebugDo)
        BF_printf("#########################################################\r\n");

    do_fuzz(g_bufferFuzz.treeBin[id]);

    if (g_bufferFuzz.onoffDebugDo)
        BF_printf("\r\n\r\n#########################################################\r\n");

    if (g_bufferFuzz.onoffDebugDo)
        BF_printf("start after\r\n");

    if (g_bufferFuzz.onoffDebugDo)
        BF_printf("#########################################################\r\n");

    do_after(g_bufferFuzz.treeBin[id]);

    if (g_bufferFuzz.onoffDebugDo)
        BF_printf("\r\n\r\n#########################################################\r\n");

    if (g_bufferFuzz.onoffDebugDo)
        BF_printf("start buffer\r\n");

    if (g_bufferFuzz.onoffDebugDo)
        BF_printf("#########################################################\r\n");

    do_buffer(g_bufferFuzz.treeBin[id], id);

    g_user_buffer[id] = BF_malloc(g_bufferFuzz.tempBufferLength);
    BF_memcpy(g_user_buffer[id], g_bufferFuzz.tempBuffer, g_bufferFuzz.tempBufferLength);

    *buf = g_user_buffer[id];
    *length = g_bufferFuzz.tempBufferLength;

    if ((g_bufferFuzz.onoffDebugXml) && (g_bufferFuzz.g_isPrint[id] == 0))
    {	
        g_bufferFuzz.g_isPrint[id] = 1;
        BF_printf("-----------!!! first buf lenght is %d, data is:\r\n", *length);

        diag_dump_buf(*buf, *length);
    }
    g_bufferFuzz.tempBufferLength = 0;
}

void bufferDoFree(void)
{
    int i;
    for (i = 0; i < Max_Buf_Number; i++)
    {
        if (g_user_buffer[i])
        {
            BF_free(g_user_buffer[i]);
            g_user_buffer[i] = NULL;
        }
    }
}

void bufferDoClear(void)
{
    int i;
    for (i = 0; i < Max_Buf_Number; i++)
    {
        //g_bufferFuzz.g_tree_bin
        if (g_bufferFuzz.treeBin[i])
            tree_free_bin(g_bufferFuzz.treeBin[i]);
        
        g_bufferFuzz.treeBin[i] = NULL;

        //g_bufferFuzz.g_tree_xml
        if (g_bufferFuzz.treeXml[i])
            tree_free_xml(g_bufferFuzz.treeXml[i]);
        
        g_bufferFuzz.treeXml[i] = NULL;
    }

    if (g_bufferFuzz.tempBuffer)
        BF_free(g_bufferFuzz.tempBuffer);
    
    g_bufferFuzz.tempBuffer = NULL;

}

void bufferDebugXmlOnoff(int onOff)
{
    g_bufferFuzz.onoffDebugXml = onOff;
}

void bufferDebugDoOnoff(int onOff)
{
    g_bufferFuzz.onoffDebugDo = onOff;
}

void bufferFuzzOnoff(int onOff)
{
    g_bufferFuzz.onoffBufferFuzz = onOff;
}

void bufferSetMaxElementLength(int length)
{
    g_bufferFuzz.maxElementLength = length;
}

void bufferSetMaxBufferLength(int length)
{
	g_bufferFuzz.maxBufferLength = length;
}


#ifdef __cplusplus
}
#endif

