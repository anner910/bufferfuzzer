/*************************************************************************************************************
wanghao creat at shenzhen in 2022
6482543@qq.com
License. See LICENSE for details.

v.1.0.0 2022-11-23
*************************************************************************************************************/

#ifndef Bufferfuzzer_H
#define Bufferfuzzer_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

    
#ifdef __cplusplus
extern "C"{
#endif

//x86ÊÇÐ¡¶ËµÄ
#define isBigendian   		0


#define BF_Mode_AnalyzerJson
//#define BF_Mode_AnalyzerXml

extern int g_paraNo;

void bufferSetBuffer(int id, char* buf, int length);

void bufferDoModel(int id, char* modelPath, char* BinPath, char* DataModelName);

void bufferDoAction(int id, char ** buf,int* length);

void bufferDoFree(void);

void bufferDoClear(void);


//
void bufferDebugXmlOnoff(int onOff);
void bufferDebugDoOnoff(int onOff);
void bufferFuzzOnoff(int onOff);


void bufferSetMaxElementLength(int length);
void bufferSetMaxBufferLength(int length);

//
void diag_dump_buf(void *p, uint s);



#ifdef __cplusplus
	}
#endif

#endif

