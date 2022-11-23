### 简介
通过 Array元素定义数组 


在不解析bin文件情况下，数组出现的个数由occurs定义

在解析bin文件情况下，
如果有Relation的时候，数组个数由Relation count计算出来，
如果没有Relation的时候，数组个数由occurs定义
如果也没有occurs，数组个数由bin文件依次匹配得来，匹配的次数不能大于maxOccurs，不能小于minOccurs

### 模型清参考  
[test.xml](../../../test/test5/test.xml)

### bin文件清参考  
[test.bin](../../../test/test5/test.bin)

### 被测代码请参考  

[target.c](../../../test/test5/target.c)


### 用例清参考  
[test.c](../../../test/test5/test.c)


### 参考如下操作

```
解压工具后进入目录
cd bufferfuzzer/test/test5

编译

gcc -c  ../../bufferfuzzer/model/*.c ../../bufferfuzzer/otherLib/*.c ../../bufferfuzzer/expand/Analyzer/*.c  ../../bufferfuzzer/expand/Fixup/*.c  ../../bufferfuzzer/expand/Transform/*.c ../../bufferfuzzer/expand/Relation/*.c  ../../bufferfuzzer/expand/Check/*.c -g -O0 -fsanitize=address ;g++ target.c test.c *.o -fsanitize=address -fsanitize-coverage=trace-pc,trace-cmp  -Wl,--whole-archive ../testlib/libcodefuzzer.a -Wl,--no-whole-archive  -o anner910  -O0 -g ;rm *.o


运行
./anner910 --count 1000000
```
