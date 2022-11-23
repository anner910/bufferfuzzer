### 简介
通过这个例子说明如何使用Defaults更改全局配置

endian默认为和执行机器相同配置（isBigendiand定义），  
例子通过Defaults配置将全局配置改为大端   
因此看到port1已经被当做大端处理   
port2自己的设置为小端，有冲突时以自己的配置为准，忽略全局配置和默认配置   

运行后可以看到port1和port2的值在内存中分布是不一样的   

### 模型请参考  
[test.xml](../../test/test37/test.xml)

### 被测代码请参考  
[target.c](../../test/test37/target.c)


### 用例请参考  
[test.c](../../test/test37/test.c)




### 参考如下操作

```
解压工具后进入目录
cd bufferfuzzer/test/test37/

编译

gcc -c  ../../bufferfuzzer/model/*.c ../../bufferfuzzer/otherLib/*.c ../../bufferfuzzer/expand/Analyzer/*.c  ../../bufferfuzzer/expand/Fixup/*.c  ../../bufferfuzzer/expand/Transform/*.c ../../bufferfuzzer/expand/Relation/*.c ../../bufferfuzzer/expand/Check/*.c   -g -O0 -fsanitize=address; g++ target.c test.c *.o -fsanitize=address -fsanitize-coverage=trace-pc,trace-cmp -Wl,--whole-archive ../testlib/libcodefuzzer.a -Wl,--no-whole-archive  -o anner910  -O0 -g ;rm *.o


运行
./anner910 --count 1000000
```
