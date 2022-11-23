/*************************************************************************************************************
wanghao creat at beijing in 2022
6482543@qq.com
License. See LICENSE for details.

v.1.2.0 2022-11-22
*************************************************************************************************************/

#ifndef Codefuzzer_H
#define Codefuzzer_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#ifdef __cplusplus
extern "C"{
#endif

/*************************************************************************************************************
define
*************************************************************************************************************/
#ifndef u8
typedef uint8_t  u8;
#endif
#ifndef u16
typedef uint16_t u16;
#endif
#ifndef u32
typedef uint32_t u32;
#endif
#ifndef u64
typedef uint64_t u64;
#endif
#ifndef s8
typedef int8_t 	s8;
#endif
#ifndef s16
typedef int16_t s16;
#endif
#ifndef s32
typedef int32_t s32;
#endif
#ifndef s64
typedef int64_t s64;
#endif

#define CF_Mode_IO
#define CF_Mode_Leak
#define CF_Mode_Hook
#define CF_Mode_TracePc
#define CF_Mode_Crash
#define CF_Mode_CorpusTxt


#ifndef _WIN32
//#define CF_Mode_Kcov  //内核安装了kcov之后再打开
#define CF_Mode_CMD
#define CF_Mode_CorpusBin

#endif

/*************************************************************************************************************
config
*************************************************************************************************************/
extern void CF_SetMaxParaNumber(int number);
extern void CF_SetMaxMutatorLen(int len);
extern void CF_SetMaxPcNumber(int number);
extern void CF_SetMaxCorpusNumber(int number);

extern void CF_SetEnableLeak(int enable);
//默认关闭----0关闭 1打印分配释放过程2打印分配释放栈
extern void CF_SetDebugLeak(int enable);

extern void CF_SetReportPath(char* path);

//设置用例超时当作bug的时间，默认180秒
extern void CF_SetTimeOut(int time);


extern void CF_SetCloseAllMutator(void);
//1打开  0关闭
extern void CF_SetOpenOneMutator(int noM, int value);

//设置变异算法权重
extern void CF_SetOneMutatorWeight(int noM, int weight);

//设置样本权重
//默认 1  pc 30, 2 edge 3 , 3 cycle 10, 4 path 1
extern void CF_SetCorpusWeight(int mode, int weight);


extern void CF_SetCloseAllParaMutator(int no);
//0 打开  1 关闭
extern void CF_SetOpenOneParaMutator(int no, int noM, int value);



//0为参数整体变异，101为不变异，1-100为按此频率变异，默认为0
extern void CF_SetParaMutatorFrequency(int no, int number);


extern void CF_Cmd(int argc,char *argv[]);
extern void CF_CrashShow(void);

//weight为0为没有新样本，多次效用权重累加，   只能在循环体中调用有效
extern void CF_SetNewFeacher(int weight);

//设置监控大内存分配，M为单位   0为不监控,默认1024M
extern void CF_SetCheckLargeMemorySize(int size);

//设置监控大内存使用，M为单位   0为不监控,默认1024M
extern void CF_SetCheckLargeMemoryUse(int size);

//是指将crash打印到串口，默认开启
extern void CF_SetPrintCrashCorpus(int enable);

//当只有一个参数，并且是blob时，支持设置bin样本路径
extern void CF_SetInBinCorpusPath(char* path);
extern void CF_SetOutBinCorpusPath(char* path);

//一些长度变异，再开始100万变异时降低变异权重，以提高变异速度
extern void CF_SetEnableScheduleMutatorWeight(int enable);

//得到正在运行的用例随机，用于外部扩展变异联动
extern int CF_GetCorpusRandom(void);


/*************************************************************************************************************
getvalue
*************************************************************************************************************/
//设置初始样本部分变异，在Get系列函数之前调用，可以随时根据需要调节
extern void	 CF_SetMutatorPos(int no, int enable, int pos, int len, int minLen, int maxLen);

/* char* blob = CF_GetBlob(2, "123457", 6, 0, 1000) */
//int len = CF_GetMutatorLen(2);
extern int   CF_GetMutatorLen(int no);
extern char* CF_GetS8( int no, s8 initValue);
extern char* CF_GetS16(int no, s16 initValue);
//int a = *(s32*)CF_GetS32(0, 0x345678);
extern char* CF_GetS32(int no, s32 initValue);
extern char* CF_GetS64(int no, s64 initValue);
extern char* CF_GetU8( int no, u8 initValue);
extern char* CF_GetU16(int no, u16 initValue);
extern char* CF_GetU32(int no, u32 initValue);
extern char* CF_GetU64(int no, u64 initValue);
extern char* CF_GetFloat(int no, float initValue);
extern char* CF_GetDouble(int no, double initValue);

//范围变异，包括边界值
//CF_GetNumberRange(0, 100, 0, 1000)
extern char* CF_GetNumberRange(int no, s32 initValue, int minValue, int maxValue);

//只在枚举里边变异
//int table[] = {5678,55555,7890123,44444,4321,88888888};
//CF_GetNumberOnlyTable(0,44444, table,6)
extern char* CF_GetNumberOnlyTable(int no, s32 initValue, int* table, int count);

//只在枚举外边变异
//int table[] = {5678,55555,7890123,44444,4321,88888888};
//CF_GetNumberOutOfTable(0,12345, table,6)
extern char* CF_GetNumberOutOfTable(int no, s32 initValue, int* table, int count);

//以枚举为初始值变异
//int table[] = {5678,55555,7890123,44444,4321,88888888};
//CF_GetNumberBasedOnTable(0,44444, table,6)
extern char* CF_GetNumberBasedOnTable(int no, s32 initValue, int* table, int count);

/* char* string = CF_GetString(0, "changchu!", 10, 0, 1000)*/
extern char* CF_GetString(int no, char* initValue, int initLen, int minLen, int maxLen);

//只在枚举里边变异
//char* table[] = {"5678","55555","7890123","44444","4321","88888888"};
//CF_GetStringOnlyTable(0, "55555", 6,0, 1000, table, 6)
extern char* CF_GetStringOnlyTable(int no, char* initValue, int initLen,int minLen, int maxLen, char** table, int count);

//只在枚举外边变异
//char* table[] = {"5678","55555","7890123","44444","4321","88888888"};
//CF_GetStringOutOfTable(0, "11111", 6,0, 1000, table, 6)
extern char* CF_GetStringOutOfTable(int no, char* initValue, int initLen,int minLen, int maxLen, char** table, int count);

//以枚举为初始值变异
//char* table[] = {"5678","55555","7890123","44444","4321","88888888"};
//CF_GetStringBasedOnTable(0, "55555", 6,0, 1000, table, 6)
extern char* CF_GetStringBasedOnTable(int no, char* initValue, int initLen,int minLen, int maxLen, char** table, int count);

/* char* blob = CF_GetBlob(2, "123457", 6, 0, 1000) */
//int len = CF_GetMutatorLen(2);
extern char* CF_GetBlob(int no, char* initValue, int initLen, int minLen, int maxLen);

//只在枚举里边变异\
//char* table[] = {"\x05\x06\x07\x00","\x00\xff\xff\x00","7890123","44444","4321","\x00\x00\x00\x00\x00\x00"};
//int tableLen[] = {4, 4, 7, 5, 4, 6};
//CF_GetBlobOnlyTable(3, "44444", 5, 0, 1000, table, tableLen, 6);
extern char* CF_GetBlobOnlyTable(int no, char* initValue, int initLen, int minLen, int maxLen, char** table, int* tablelen, int count);

//只在枚举外边变异
//char* table[] = {"\x05\x06\x07\x00","\x00\xff\xff\x00","7890123","44444","4321","\x00\x00\x00\x00\x00\x00"};
//int tableLen[] = {4, 4, 7, 5, 4, 6};
//CF_GetBlobOutOfTable(3, "12345", 5, 0, 1000, table, tableLen, 6);
extern char* CF_GetBlobOutOfTable(int no, char* initValue, int initLen, int minLen, int maxLen, char** table, int* tablelen, int count);

//以枚举为初始值变异
//char* table[] = {"\x05\x06\x07\x00","\x00\xff\xff\x00","7890123","44444","4321","\x00\x00\x00\x00\x00\x00"};
//int tableLen[] = {4, 4, 7, 5, 4, 6};
//CF_GetBlobBasedOnTable(3, "44444", 5, 0, 1000, table, tableLen, 6);
extern char* CF_GetBlobBasedOnTable(int no, char* initValue, int initLen, int minLen, int maxLen, char** table, int* tablelen, int count);


extern char* CF_GetMySelf(int no, char* initValue, int initLen, int minLen, int maxLen);


/*************************************************************************************************************
for
*************************************************************************************************************/

extern void CF_SetRunSeed(int seed);
extern void CF_SetRunTime(int time);
extern void CF_SetRunCount(u64 count);
extern void CF_SetTestCaseName(char* name);
extern void CF_SetRunMode(int mode);

extern void CF_Start(void);
extern void CF_End(void);
extern void CF_ForStart(void);
extern int  CF_ForEnd(void);

extern void CF_Fork(void);
extern int  CF_IsFather(void);
extern void CF_Exit(void);
extern void CF_Wait(void);
extern int  CF_isOk(void);


#define CodeFuzz_start(seed,time,count,name,mode) \
	{\
		CF_Fork();\
		if (!CF_IsFather())\
		{\
			CF_SetRunSeed(seed);\
			CF_SetRunTime(time);\
			CF_SetRunCount(count);\
			CF_SetTestCaseName(name);\
			CF_SetRunMode(mode);\
			CF_Start();\
			for (;;)\
			{\
				CF_ForStart();\


#define CodeFuzz_end() \
				if (CF_ForEnd() != 0)\
					break;\
			}\
			CF_End();\
			CF_Exit();\
		}\
		CF_Wait();\
	}\

extern char* g_cfTestCaseName;

#define CodeFuzz_start_cmd(name) \
	{\
		CF_Fork();\
		if (!CF_IsFather())\
		{\
			if (g_cfTestCaseName) \
				CF_SetTestCaseName(g_cfTestCaseName);\
			else\
				CF_SetTestCaseName(name);\
			CF_Start();\
			for (;;)\
			{\
				CF_ForStart();\



extern void CF_ForPassive(char* testcase, int mode);
extern void CF_OverPassive(void);


#ifdef __cplusplus
	}
#endif

#endif

