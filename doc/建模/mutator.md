### 简介
通过这个例子说明如何配置某个元素或者某个结构是否变异

冲突时以最接近的配置为准

没有配置默认变异


### 模型请参考  
[test.xml](../../test/test38/test.xml)

### 被测代码请参考  
[target.c](../../test/test38/target.c)


### 用例请参考  
[test.c](../../test/test38/test.c)




### 参考如下操作

```
解压工具后进入目录
cd bufferfuzzer/test/test38/

编译

gcc -c  ../../bufferfuzzer/model/*.c ../../bufferfuzzer/otherLib/*.c ../../bufferfuzzer/expand/Analyzer/*.c  ../../bufferfuzzer/expand/Fixup/*.c  ../../bufferfuzzer/expand/Transform/*.c ../../bufferfuzzer/expand/Relation/*.c ../../bufferfuzzer/expand/Check/*.c   -g -O0 -fsanitize=address; g++ target.c test.c *.o -fsanitize=address -fsanitize-coverage=trace-pc,trace-cmp -Wl,--whole-archive ../testlib/libcodefuzzer.a -Wl,--no-whole-archive  -o anner910  -O0 -g ;rm *.o


运行
./anner910 --count 1000000
```
