
#include <stdio.h>
#include "../../bufferfuzzer/bufferfuzzer.h"

#include "../testlib/codefuzzer.h"

#include <gtest/gtest.h>



#ifdef __cplusplus
extern "C"{
#endif


extern void targer(int num, char* blob,int len, char* string);

#ifdef __cplusplus
}
#endif


TEST(fuzzTest, Test1)
 {

	printf("test_target start\r\n");
	
	bufferDoModel(0, (char*)"./test.xml", NULL, (char*)"DataModel1");

	CodeFuzz_start_cmd((char*)"test_target")
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
	CF_Cmd(argc, argv);
	
    testing::InitGoogleTest(&argc, argv);

    int result =  RUN_ALL_TESTS();


    return result;
}





