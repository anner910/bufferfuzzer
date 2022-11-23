
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
	
	bufferDoModel(0, (char*)"./test.xml", NULL, (char*)"DataModel1");

    CodeFuzz_start(0,3600,1000000,(char*)"test_target",0)
	{
		static int i = 0;
		printf("\r%d",i++);
		fflush(stdout);

		int len;
		char* buf;
		bufferDoAction(0, &buf,&len);

		targer(10, buf, len, (char*)"12345");
		
		bufferDoFree();
	}
	CodeFuzz_end()
	
	bufferDoClear();

	printf("test_target end\r\n");

}

int main(int argc, char* argv[])
{

	test_target();

    return 0;
}

#ifdef __cplusplus
}
#endif


