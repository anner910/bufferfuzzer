### 简介
工具仅支持以BufferFuzzer标签定义的模型

### 模型清参考  
[test.xml](../../../test/test16/test.xml)



### 被测代码请参考  

[target.c](../../../test/test16/target.c)


### 用例清参考  
[test.c](../../../test/test16/test.c)


### 参考如下操作

```
解压工具后进入目录
cd bufferfuzzer/test/test16

编译

gcc -c  ../../bufferfuzzer/model/*.c ../../bufferfuzzer/otherLib/*.c ../../bufferfuzzer/expand/Analyzer/*.c  ../../bufferfuzzer/expand/Fixup/*.c  ../../bufferfuzzer/expand/Transform/*.c ../../bufferfuzzer/expand/Relation/*.c ../../bufferfuzzer/expand/Check/*.c  -g -O0 -fsanitize=address ;g++ target.c test.c *.o -fsanitize=address -fsanitize-coverage=trace-pc,trace-cmp  -Wl,--whole-archive ../testlib/libcodefuzzer.a -Wl,--no-whole-archive  -o anner910  -O0 -g ;rm *.o


运行
./anner910 --count 1000000
```
