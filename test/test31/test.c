
#include <stdio.h>
#include "../../bufferfuzzer/bufferfuzzer.h"

#include "../testlib/codefuzzer.h"



#ifdef __cplusplus
extern "C"{
#endif

/* arp Frame (42 bytes) */
static const unsigned char pkt1[42] = {
0xd0, 0xd7, 0x83, 0x99, 0xf3, 0x06, 0x4c, 0xd5, /* ......L. */
0x77, 0xb7, 0xa9, 0x73, 0x08, 0x06, 0x00, 0x01, /* w..s.... */
0x08, 0x00, 0x06, 0x04, 0x00, 0x01, 0x4c, 0xd5, /* ......L. */
0x77, 0xb7, 0xa9, 0x73, 0xc0, 0xa8, 0x03, 0x82, /* w..s.... */
0xd0, 0xd7, 0x83, 0x99, 0xf3, 0x06, 0xc0, 0xa8, /* ........ */
0x03, 0x01                                      /* .. */
};


extern void targer(int num, char* blob,int len, char* string);

void test_target(void)
{
	printf("test_target start\r\n");

	bufferSetBuffer(0, (char*)pkt1, sizeof(pkt1) );
	
	//��һ��������ģ���ļ�·�����֣��ڶ�������������bin�ļ�·����������������ģ��Ҫ����������ģ������
	bufferDoModel(0, (char*)"./test.xml", (char*)"./test.bin", (char*)"arp_packet");

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

