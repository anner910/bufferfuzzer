### 简介
通过这个例子说明如何使用Analyzer

例子里使用的Analyzer，使得解析的字符串被逗号分割，工具只变异逗号之间的字符串，然后分别变异后再重新组合

### 模型请参考  
[test.xml](../../test/test39/test.xml)

### 被测代码请参考  
[target.c](../../test/test39/target.c)


### 用例请参考  
[test.c](../../test/test39/test.c)




### 参考如下操作

```
解压工具后进入目录
cd bufferfuzzer/test/test39/

编译

gcc -c  ../../bufferfuzzer/model/*.c ../../bufferfuzzer/otherLib/*.c ../../bufferfuzzer/expand/Analyzer/*.c  ../../bufferfuzzer/expand/Fixup/*.c  ../../bufferfuzzer/expand/Transform/*.c ../../bufferfuzzer/expand/Relation/*.c ../../bufferfuzzer/expand/Check/*.c   -g -O0 -fsanitize=address; g++ target.c test.c *.o -fsanitize=address -fsanitize-coverage=trace-pc,trace-cmp -Wl,--whole-archive ../testlib/libcodefuzzer.a -Wl,--no-whole-archive  -o anner910  -O0 -g ;rm *.o


运行
./anner910 --count 1000000
```
