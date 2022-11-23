### 简介
每个元素都可以通过name来起个名字

一些关系字段通过name来互相查找，引用

元素尽量不要定义重复的名字，以免引起歧义

### 模型清参考  
[test.xml](../../../test/test41/test.xml)

### 被测代码请参考  
[target.c](../../../test/test41/target.c)


### 用例清参考  
[test.c](../../../test/test41/test.c)


### 参考如下操作

```
解压工具后进入目录
cd bufferfuzzer/test/test41

编译

gcc -c  ../../bufferfuzzer/model/*.c ../../bufferfuzzer/otherLib/*.c ../../bufferfuzzer/expand/Analyzer/*.c  ../../bufferfuzzer/expand/Fixup/*.c  ../../bufferfuzzer/expand/Transform/*.c ../../bufferfuzzer/expand/Relation/*.c ../../bufferfuzzer/expand/Check/*.c  -g -O0 -fsanitize=address ;g++ target.c test.c *.o -fsanitize=address -fsanitize-coverage=trace-pc,trace-cmp  -Wl,--whole-archive ../testlib/libcodefuzzer.a -Wl,--no-whole-archive  -o anner910  -O0 -g ;rm *.o


运行
./anner910 --count 1000000
```
