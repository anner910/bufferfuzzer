### 简介
通过Transform建模，使得工具知道被测buffer某个字段是被加解密的  
通过对解密字段进行变异，变异后再加密  
可以使测试更加有效率，发现更深层次的问题   


### 模型清参考  
[test.xml](../../../test/test8/test.xml)

### 被测代码请参考  

[target.c](../../../test/test8/target.c)


### 用例清参考  
[test.c](../../../test/test8/test.c)


### 参考如下操作

```
解压工具后进入目录
cd bufferfuzzer/test/test8

编译

gcc -c  ../../bufferfuzzer/model/*.c ../../bufferfuzzer/otherLib/*.c ../../bufferfuzzer/expand/Analyzer/*.c ../../bufferfuzzer/expand/Fixup/*.c  ../../bufferfuzzer/expand/Transform/*.c ../../bufferfuzzer/expand/Relation/*.c ../../bufferfuzzer/expand/Check/*.c  -g -O0 -fsanitize=address ;g++ target.c test.c *.o -fsanitize=address -fsanitize-coverage=trace-pc,trace-cmp  -Wl,--whole-archive ../testlib/libcodefuzzer.a -Wl,--no-whole-archive  -o anner910  -O0 -g ;rm *.o


运行
./anner910 --count 1000000
```
