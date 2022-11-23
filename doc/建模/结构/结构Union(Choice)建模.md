### 简介
通过 Choice元素定义可选结构体   

再不解析bin文件情况下，默认选择大儿子
解析bin文件的情况下，一次进行匹配，第一个完全匹配的儿子被选中

### 模型清参考  
[test.xml](../../../test/test4/test.xml)


### 被测代码请参考  

[target.c](../../../test/test4/target.c)


### 用例清参考  
[test.c](../../../test/test4/test.c)


### 参考如下操作

```
解压工具后进入目录
cd bufferfuzzer/test/test4

编译

gcc -c  ../../bufferfuzzer/model/*.c ../../bufferfuzzer/otherLib/*.c ../../bufferfuzzer/expand/Analyzer/*.c  ../../bufferfuzzer/expand/Fixup/*.c  ../../bufferfuzzer/expand/Transform/*.c ../../bufferfuzzer/expand/Relation/*.c  ../../bufferfuzzer/expand/Check/*.c  -g -O0 -fsanitize=address ;g++ target.c test.c *.o -fsanitize=address -fsanitize-coverage=trace-pc,trace-cmp  -Wl,--whole-archive ../testlib/libcodefuzzer.a -Wl,--no-whole-archive  -o anner910  -O0 -g ;rm *.o


运行
./anner910 --count 1000000
```
