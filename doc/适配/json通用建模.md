### 简介
我们可以使用简单的json通用模型，解析所有的json文件，目前支持对参数值的变异   
但如果想支持参数名字的变异，则需要修改代码去增加:)   

前提需要将bufferFuzz.h里边的下边宏提前定义   
#define BF_Mode_AnalyzerJson

json通用模型解析被默认支持

### 模型清参考  
[test.xml](../../test/test23/test.xml)

### Bin文件清参考  
[test.bin](../../test/test23/test.bin)

### 被测代码请参考  

[target.c](../../test/test23/target.c)


### 用例清参考  
[test.c](../../test/test23/test.c)


### 参考如下操作

```
解压工具后进入目录
cd bufferfuzzer/test/test23

编译

gcc -c  ../../bufferfuzzer/model/*.c ../../bufferfuzzer/otherLib/*.c ../../bufferfuzzer/expand/Analyzer/*.c  ../../bufferfuzzer/expand/Fixup/*.c  ../../bufferfuzzer/expand/Transform/*.c ../../bufferfuzzer/expand/Relation/*.c ../../bufferfuzzer/expand/Check/*.c  -g -O0 -fsanitize=address ;g++ target.c test.c *.o -fsanitize=address -fsanitize-coverage=trace-pc,trace-cmp  -Wl,--whole-archive ../testlib/libcodefuzzer.a -Wl,--no-whole-archive  -o anner910  -O0 -g ;rm *.o


运行
./anner910 --count 1000000
```
