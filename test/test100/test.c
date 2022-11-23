
#include <stdio.h>
#include "../../bufferfuzzer/bufferfuzzer.h"

#include "../testlib/codefuzzer.h"


#ifdef __cplusplus
extern "C"{
#endif


extern void targer(int num, char* blob,int len, char* string);

int main(int argc, char* argv[])
{

	printf("main 1111111111111111111111111111111111\r\n");

	CF_Cmd(argc, argv);

	//bufferDebugXmlOnoff(0);


	bufferDoModel(0, (char*)"./test.xml", (char*)"./test.bin", (char*)"DataModel1");

	CodeFuzz_start_cmd((char*)"test_target")
	{
		static int i = 0;
		printf("\r%d",i++);
		fflush(stdout);

		int len;
		char* buf;
		bufferDoAction(0, &buf,&len);


		//printf("test------------%s\r\n",buf);
		targer(10, buf, len, (char*)"12345");
		
		bufferDoFree();
	}
	CodeFuzz_end()
	

	bufferDoClear();
    return 1234;
}

#ifdef __cplusplus
}
#endif


