### 简介
很多时候，不仅有buf参数，还有其他类型参数，  
我们还可以直接调用codefuzz的其他setget函数来同时变异  
本用例对这种情况做出样例  

### 模型清参考  
[test.xml](../../test/test25/test.xml)

### 被测代码请参考  

[target.c](../../test/test25/target.c)


### 用例清参考  
[test.c](../../test/test25/test.c)


```

extern void targer(int num, char* blob,int len, char* string);

void test_target(void)
{
	printf("test_target start\r\n");
	
	//第一个参数是模型文件路径名字，第二个参数是样本bin文件路径，第三个参数是模型要解析的数据模型名称
	bufferDoModel((char*)"./test.xml", (char*)"./test.bin", (char*)"DataModel1");

	CodeFuzz_start_cmd((char*)"test_target")
	{
		static int i = 0;
		printf("\r%d",i++);
		fflush(stdout);

		int len;
		char* buf;

		//变异后的buf工具自己释放
		bufferDoAction(&buf,&len);

		char* string = CF_GetString(g_paraNo++, "12345", 6, 1, 1000);

		targer(10, buf, len, string);

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

```

 
### 参考如下操作

```
解压工具后进入目录
cd bufferfuzzer/test/test25

编译

gcc -c  ../../bufferfuzzer/model/*.c ../../bufferfuzzer/otherLib/*.c ../../bufferfuzzer/expand/Analyzer/*.c  ../../bufferfuzzer/expand/Fixup/*.c  ../../bufferfuzzer/expand/Transform/*.c ../../bufferfuzzer/expand/Relation/*.c ../../bufferfuzzer/expand/Check/*.c  -g -O0 -fsanitize=address ;g++ target.c test.c *.o -fsanitize=address -fsanitize-coverage=trace-pc,trace-cmp  -Wl,--whole-archive ../testlib/libcodefuzzer.a -Wl,--no-whole-archive  -o anner910  -O0 -g ;rm *.o

运行
./anner910 --count 1000000
```
