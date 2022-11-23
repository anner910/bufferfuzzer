
#include <stdio.h>
#include "../../bufferfuzzer/bufferfuzzer.h"

#include "../testlib/codefuzzer.h"



#ifdef __cplusplus
extern "C"{
#endif

/* icmp Frame (74 bytes) */
static const unsigned char pkt1[74] = {
0xd0, 0xd7, 0x83, 0x99, 0xf3, 0x06, 0x4c, 0xd5, /* ......L. */
0x77, 0xb7, 0xa9, 0x73, 0x08, 0x00, 0x45, 0x00, /* w..s..E. */
0x00, 0x3c, 0xaa, 0xc0, 0x00, 0x00, 0x80, 0x01, /* .<...... */
0x62, 0x30, 0xc0, 0xa8, 0x03, 0x82, 0x27, 0x9c, /* b0....'. */
0x42, 0x0a, 0x08, 0x00, 0x4d, 0x58, 0x00, 0x01, /* B...MX.. */
0x00, 0x03, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, /* ..abcdef */
0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, /* ghijklmn */
0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, /* opqrstuv */
0x77, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, /* wabcdefg */
0x68, 0x69                                      /* hi */
};



extern void targer(int num, char* blob,int len, char* string);

void test_target(void)
{
	printf("test_target start\r\n");

	bufferSetBuffer(0, (char*)pkt1, sizeof(pkt1) );
	
	//第一个参数是模型文件路径名字，第二个参数是样本bin文件路径，第三个参数是模型要解析的数据模型名称
	bufferDoModel(0, (char*)"./test.xml", (char*)"./test.bin", (char*)"icmp_packet");

	CodeFuzz_start_cmd((char*)"test_target")
	{
		static int i = 0;
		printf("\r%d",i++);
		fflush(stdout);

		int len;
		char* buf;

		//变异后的buf工具自己释放
		bufferDoAction(0, &buf,&len);


		targer(10, buf, len, (char*)"12345");

		//工具释放每次变异过程中的临时内存
		bufferDoFree();
	}
	CodeFuzz_end()

	//工具释放模型解析过程中的内存
	bufferDoClear();

	printf("test_target end\r\n");

}

int main(int argc, char* argv[])
{

	CF_Cmd(argc, argv);

	test_target();

    return 0;
}

#ifdef __cplusplus
}
#endif


