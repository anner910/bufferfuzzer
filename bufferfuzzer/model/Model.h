#ifndef Model_H
#define Model_H

#include "../bufferfuzzer.h"
#include "../../test/testlib/codefuzzer.h"
#include <math.h>

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


#define ASSERT(condition)    \
BF_printf(condition);			 \
do{                          \
}while(1)


#define Pc_tail 			1
#define Pc_notail 			2
#define Pc_oneline 			3

#define Pc_no 			    4

#define Max_Buf_Number 		16

#define Max_Buf_Prinf_Length 250

#define BigEndian 10
#define LittleEndian 11




//数据类型
enum ElementType
{
	ElementType_Unknown = 0,
	ElementType_Buf, 
	ElementType_String, 
	ElementType_Number, 
	ElementType_Bit, 

	ElementType_S8, 
	ElementType_S16, 
	ElementType_S32, 
	ElementType_S64, 
	ElementType_U8, 
	ElementType_U16, 
	ElementType_U32, 
	ElementType_U64, 
	ElementType_Float, 
	ElementType_Double, 

	ElementType_Padding,
	
	ElementType_Struct, 
	ElementType_Array,
	ElementType_Union,
	ElementType_Bits,

	ElementType_Buffer,
	ElementType_BufferFuzzer,

	ElementType_Relation,
	ElementType_Fixup,
	ElementType_Transform,
	ElementType_Analyzer,
	ElementType_Param,

	ElementType_Defaults,
	ElementType_Configure,

	ElementType_max, 
};


typedef struct elementXml elementXmlContent;

struct elementXml {
	struct elementXml *bigChild;
    struct elementXml *littleBrother;
	struct elementXml *bigBrother;
    struct elementXml *parent;
	
    int     type;

	//number
	int isbigEndian;


	//目前的长度
	int xml_length;
	int xml_size;
	char* xml_value;


	//如果为0，则说明长度不确定
	int fixLength;

	//如果为0.则说明内容不确定
	int istoken;


	//属性大全
	char attribute_name[128];
	char attribute_size[32];
	char attribute_length[32];
	char attribute_alignment[32];

	char attribute_type[32];
	char attribute_valueType[32];
	
	char attribute_of[128];
	char attribute_token[32];
	char attribute_check[32];
	char attribute_position[32];
	char attribute_ref[128];

	char attribute_refOK[128];
	char attribute_refOK1[128];
	char attribute_refOK2[128];
	char attribute_refOK3[128];

	char attribute_endian[32];

	char attribute_para1[64];
	char attribute_para2[64];
	char attribute_para3[64];
	char attribute_para4[64];

	char attribute_count[32];
	char attribute_minCount[32];
	char attribute_maxCount[32];

	char attribute_mutator[32];
	
	char *attribute_value;

	//属性值

	//transform
	int isTransformValue;
	struct elementXml *transformValue;
	int isTransformBlob;
	struct elementXml *transformBlob;

	//fixup
	int isFixupValue;
	struct elementXml *fixupValue;
	int isFixupBlob;
	struct elementXml *fixupBlob;

	//relation
	int isRelationValue;
	struct elementXml *relationValue;
	int isRelationBlob;
	struct elementXml *relationBlob;

	int isRelationParent;

	int isFixupParent;

	//analyzer
	int isAnalyzer;

	
	
};

typedef struct elementBin elementBinContent;

struct elementBin {

	struct elementBin *bigChild;
    struct elementBin *littleBrother;
	struct elementBin *bigBrother;
    struct elementBin *parent;
    struct elementXml *xml;

	//
	struct elementBin *resolvedlTree;

	//transform
	struct elementBin *transformBlob;
	int typeTransform;

	//fixup
	struct elementBin *fixupBlob;
	struct elementBin *fixupValue;
	int typeFixup;

	//relation
	struct elementBin *relationValue;
	struct elementBin *relationBlob;
	int typeRelation;
	
	//analyzer
	int typeAnalyzer;

	//check
	int typeCheck;
	
	char* p1;
	char* p2;
	char* p3;

	//array
	int relationCount;
	int isRelationCount;
	
	int count;
	int minCount;
	int maxCount;

	//

	int value_length;
	char *value;   //这个以后必须改

	//bin
	char* binPtr;
	int binLength;

	//变异整理后
	int after_lenght;
	char* after_buf;


};

typedef struct {

	elementBinContent *nolength_tree;

	elementXmlContent *treeXml[Max_Buf_Number];
	elementBinContent *treeBin[Max_Buf_Number];	

	//用户输入的bin
	char *userBinBuf[Max_Buf_Number];
	int userBinBufLength[Max_Buf_Number];

	int tempBufferLength;
	char *tempBuffer;


	//变异相关
	int isdeleteElement[Max_Buf_Number];
	int isdeleteStruct[Max_Buf_Number];
	int iscopyElement[Max_Buf_Number];
	int iscopyStruct[Max_Buf_Number];
	int isinsertget[Max_Buf_Number];
	int isinsertset[Max_Buf_Number];
	elementBinContent *insert_tree[Max_Buf_Number];
	int element_no[Max_Buf_Number];
	int element_count[Max_Buf_Number];


	int onoffDebugXml;
	int onoffDebugDo;
	int onoffBufferFuzz;

	int maxElementLength;
	int maxBufferLength;

	int g_isPrint[Max_Buf_Number];
	int g_isBigEndian;

} SBufferFuzz;

extern SBufferFuzz g_bufferFuzz;

#define BF_printf(fmt, ...)  		printf(fmt, ##__VA_ARGS__)


//parseXmlModel.c
int parseXmlModel(elementXmlContent **tree, char** file, int* length);

//parseXmlLine
int parseXmlLine(char *buf, elementXmlContent *tree);

//parseXmlType
void parseXmlType(char* buf, elementXmlContent *tree);


//parseXmlAttribute
void parseXmlAttribute(char* buf, elementXmlContent *tree);

//parseXmlDefaults.c
void parseXmlDefaults(elementXmlContent *tree);

//parseXmlConfigure.c
char* parseXmlConfigure(elementXmlContent *tree, char* value);

//parseXmlRef.c
void parseXmlRef(elementXmlContent *tree, elementXmlContent *root);

//parseXmlTree.c
void parseXmlTree(elementXmlContent *tree);

//parseXmlOther.c
void parseXmlOther(elementXmlContent *tree);


//parseXmlLength.c
void parseXmlLength(elementXmlContent *tree, elementXmlContent *root);


//parseXmlValue.c
void parseXmlValue(elementXmlContent *tree, elementXmlContent *root);


//bin
void parseBin(elementXmlContent *treeXml, char* DataModelName,char* bin, int length, elementBinContent **treeBin);

int parse_element(elementXmlContent *tree, char* bin, int length, elementBinContent *treeBin);
int parse_array_child(elementXmlContent *tree, char* bin, int length, elementBinContent *treeBin);
int parse_union_child(elementXmlContent *tree, char* bin, int length, elementBinContent *treeBin);
int parse_struct_child(elementXmlContent *tree, char* bin, int length, elementBinContent *treeBin);

//Mfuzz.c
void do_fuzz(elementBinContent *tree);


//after
void do_after(elementBinContent *tree);


//bits
void do_bits_after(elementBinContent *tree);

//check
int do_check_bin(elementBinContent *tree, char* bin, int length);
int do_check_value(elementBinContent *tree, char* value, int length);


//relation
void do_relation_before(elementXmlContent *tree);
void do_relation_after(elementBinContent *treevalue,elementBinContent *treeBlob);

int do_relation_get(elementBinContent *tree);
int do_relation_set(elementBinContent *tree);

//Padding
int do_padding_get(elementBinContent *tree);
void do_padding_after(elementBinContent *tree);



//fixup
void do_fixup_before(elementXmlContent *tree);
void do_fixup_after(elementBinContent *treevalue,elementBinContent *treeBlob);

//transform
void do_transform_before(elementBinContent *tree);
void do_transform_after(elementBinContent *tree);


//Analyzer
void do_analyzer_before(elementBinContent *tree);
void do_analyzer_after(elementBinContent *tree);
int do_analyzer_fuzz(elementBinContent *tree);
void do_analyzer_free(elementBinContent *tree);

//buffer
void do_bufferFuzzClear(int id);
void do_buffer(elementBinContent *tree, int id);


//mlib
u32 mlib_strToIp(char* ipStr);

void mlib_hexToAscii(unsigned char *pHex, unsigned char *pAscii, int nLen);
int mlib_stringToHex(char *str, int inlen, unsigned char *out, unsigned int *outlen);

//
int mlib_findFirstLetter(char *buf, char a);
int mlib_findFirstSpace(char *buf);
int mlib_findSecondQuotation(char *buf);

//
void mlib_getLineBuf(char* buf, char** file, int* length);
int mlib_searchMemory(char* mem, int lenmem, char* buf, int lenbuf);

char* mlib_getTypeName(int type);

int mlib_fromSizeToLength(int size);
void mlib_copyBitsValue(char* mem1,char* mem2, int pos, int size, int length);
void mlib_copyValueBits(char* mem1,char* mem2, int pos, int size);
void mlib_printfData(void *p, uint s);

int   mlib_isprint(u8 v);
int   mlib_isspace(u8 v);
int   mlib_isxdigit(u8 v);
int   mlib_isdigit(u8 v);
long  mlib_strtol(const char * nptr, char ** endptr, int base);
char* mlib_itoa(int num,char* str,int radix);

int   mlib_memcmp(void *d,void *s,size_t n);
char* mlib_strcpy(char *dst,char *src);
int   mlib_strcmp(void *d,void *s);
int   mlib_strnlen(const char* s, int len);
int   mlib_strlen(const char* s);
int   mlib_atoi(const char *nptr);

//treelib
elementBinContent* tree_relation_parent(elementBinContent *treebin, elementXmlContent *treexml);

void free_xml(elementXmlContent *treexml);
void tree_free_xml(elementXmlContent *treexml);
void tree_free_xml1(elementXmlContent *treexml);
void tree_free_bin(elementBinContent *treebin);
void tree_free_bin1(elementBinContent *treebin);

s64 tree_getValue(elementBinContent *tree);
void tree_setValue(elementBinContent *tree, s64 value);

void tree_bufferCopy(elementBinContent *tree, int only_length);
void tree_bufferValueGet(elementBinContent *tree, int only_length);
int tree_bufferCountGet(elementBinContent *tree);
int tree_PaddingOffSetGet(elementBinContent *tree, elementBinContent *padding, int isAfter);


elementBinContent* found_relationOfBinBlob(elementBinContent *tree, char *name, int type);
elementBinContent* found_relationOfBinValue(elementBinContent *tree, elementBinContent *me, char *name, int type);
elementXmlContent* found_relationOfXmlBlob(elementXmlContent *tree, int* isParent, char *name);

elementBinContent* found_relationOfPadding(elementBinContent *tree, char *name);

//MPlatForm
int BF_random(void);
void* BF_malloc(size_t size);
void BF_free(void* s);
void* BF_memset(void *s,int ch,size_t n);
void* BF_memcpy(void *d,void *s,size_t n);

uint8_t  BF_swap8(uint8_t x); 
uint16_t BF_swap16(uint16_t x);
uint32_t BF_swap32(uint32_t x); 
uint64_t BF_swap64(uint64_t x);

void BF_seed(int setSeed);


void IO_readFileRaw(char* path, char** buf, int* len);


//self
void do_xml_before(elementBinContent *tree);
int do_xml(elementBinContent *tree);
void do_xml_after_free(elementBinContent *tree);

void do_json_before(elementBinContent *tree);
int do_json(elementBinContent *tree);
void do_json_after_free(elementBinContent *tree);

void do_test_before(elementBinContent *tree);
int do_test(elementBinContent *tree);
void do_test_after_free(elementBinContent *tree);


//
int do_check_http_bin(elementBinContent *tree, char* bin, int length);
int do_check_http_value(elementBinContent *tree, char* value, int length);

//
void doCrc32(elementBinContent *value, elementBinContent *blob);
void doIcmpCheckSum(elementBinContent *value, elementBinContent *blob);


//
void doBase64Encode(elementBinContent *tree);
void doBase64Decode(elementBinContent *tree);

//
int doSizeGet(int size);
int doSizeSet(int size);


int doSizeAddSub4Get(int size);
int doSizeAddSub4Set(int size);

int doSizeAddSub2Get(int size);
int doSizeAddSub2Set(int size);

int doSizeIpv4Get(int size);
int doSizeIpv4Set(int size);

#ifdef __cplusplus
	}
#endif

#endif

