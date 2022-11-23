### 简介

token只在使用模型解析bin文件的的时候有效   
bin文件里该字段的值必须严格与模型的value值相同，否则该元素当时解析失败  

很多时候一些不确定长度的元素会紧接着一个token元素来确定长度   
有时候一些union的儿子会以token开头来确定是那个儿子

### 模型请参考  
[test.xml](../../../test/test29/test.xml)

### bin文件请参考  
[test.bin](../../../test/test29/test.bin)


### 被测代码请参考  

[target.c](../../../test/test29/target.c)


### 用例清参考  
[test.c](../../../test/test29/test.c)



### 参考如下操作

```
解压工具后进入目录
cd bufferfuzzer/test/test29

编译

gcc -c  ../../bufferfuzzer/model/*.c ../../bufferfuzzer/otherLib/*.c ../../bufferfuzzer/expand/Analyzer/*.c  ../../bufferfuzzer/expand/Fixup/*.c  ../../bufferfuzzer/expand/Transform/*.c ../../bufferfuzzer/expand/Relation/*.c ../../bufferfuzzer/expand/Check/*.c  -g -O0 -fsanitize=address ;g++ target.c test.c *.o -fsanitize=address -fsanitize-coverage=trace-pc,trace-cmp  -Wl,--whole-archive ../testlib/libcodefuzzer.a -Wl,--no-whole-archive  -o anner910  -O0 -g ;rm *.o


运行
./anner910 --count 1000000
```
