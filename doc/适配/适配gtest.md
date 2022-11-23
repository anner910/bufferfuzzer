### 简介

gtest场景适配

同codefuzzer一样，bufferfuzzer同样可以被内嵌到gtest里进行用例编写   

### 模型清参考  
[test.xml](../../test/test40/test.xml)

### 被测代码请参考  

[target.c](../../test/test40/target.c)

### 用例清参考  
[test.c](../../test/test40/test.c)


### 参考如下操作

```
解压工具后进入目录
cd bufferfuzzer/test/test40

编译

gcc -c  ../../bufferfuzzer/model/*.c ../../bufferfuzzer/otherLib/*.c ../../bufferfuzzer/expand/Analyzer/*.c  ../../bufferfuzzer/expand/Fixup/*.c  ../../bufferfuzzer/expand/Transform/*.c ../../bufferfuzzer/expand/Relation/*.c ../../bufferfuzzer/expand/Check/*.c  -g -O0 -fsanitize=address ;g++ target.c test.c *.o -fsanitize=address -fsanitize-coverage=trace-pc,trace-cmp  -Wl,--whole-archive ../testlib/libcodefuzzer.a -Wl,--no-whole-archive -lgtest -o anner910  -O0 -g ;rm *.o


运行
./anner910 --count 1000000
```
