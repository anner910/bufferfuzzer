
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
	
	//��һ��������ģ���ļ�·�����֣��ڶ�������������bin�ļ�·����������������ģ��Ҫ����������ģ������
	bufferDoModel(0, (char*)"./test.xml", (char*)"./test.bin", (char*)"http_packet");

	CodeFuzz_start_cmd((char*)"test_target")
	{
		static int i = 0;
		printf("\r%d",i++);
		fflush(stdout);

		int len;
		char* buf;

		//������buf�����Լ��ͷ�
		bufferDoAction(0, &buf,&len);


		targer(10, buf, len, (char*)"12345");

		//�����ͷ�ÿ�α�������е���ʱ�ڴ�
		bufferDoFree();
	}
	CodeFuzz_end()

	//�����ͷ�ģ�ͽ��������е��ڴ�
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


