### 简介
通过fixup建模，使得工具知道被测buffer字段之间类似校验和 和value之间的关系  
校验和在大多数时间根据value的实际数值计算  
可以使测试更加有效率，发现更深层次的问题   


### 模型清参考  
[test.xml](../../test/test7/test.xml)

### 被测代码请参考  

[target.c](../../test/test7/target.c)


### 用例清参考  
[test.c](../../test/test7/test.c)


### 参考如下操作

```
解压工具后进入目录
cd bufferfuzzer/test/test7

编译

gcc -c  ../../bufferfuzzer/model/*.c ../../bufferfuzzer/otherLib/*.c ../../bufferfuzzer/expand/Analyzer/*.c ../../bufferfuzzer/expand/Fixup/*.c  ../../bufferfuzzer/expand/Transform/*.c ../../bufferfuzzer/expand/Relation/*.c ../../bufferfuzzer/expand/Check/*.c -g -O0 -fsanitize=address ;g++ target.c test.c *.o -fsanitize=address -fsanitize-coverage=trace-pc,trace-cmp  -Wl,--whole-archive ../testlib/libcodefuzzer.a -Wl,--no-whole-archive  -o anner910  -O0 -g ;rm *.o


运行
./anner910 --count 1000000
```
