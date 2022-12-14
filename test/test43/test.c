
#include <stdio.h>
#include "../../bufferfuzzer/bufferfuzzer.h"

#include "../testlib/codefuzzer.h"



#ifdef __cplusplus
extern "C"{
#endif

extern void targer(int num, char* blob,int len, char* string);

void test_target(void)
{
	printf("test_target start\r\n");

	CF_SetMaxParaNumber(10000);
	
	//第一个参数是模型文件路径名字，第二个参数是样本bin文件路径，第三个参数是模型要解析的数据模型名称
	bufferDoModel(0, (char*)"./test.xml", (char*)"./test.mp4", (char*)"mp4_packet");

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


