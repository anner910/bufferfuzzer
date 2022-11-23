### 简介
check(constraint)修饰只在使用模型解析bin文件时起作用，其他时候忽略  
  
在使用模型解析bin文件时，可以使用check(constraint)来检验元素是否符合某种条件     
如果不符合，则检测失败（一般用于Union选择那个儿子和array是否结束）  
和token原理基本相同，不过适用范围要比token更广    
  
比如当前元素值是否是以回车开头，长度是否大于等于3等等    
  
例子中checkHttp就是检测当前元素，不能以回车（0d0a）开头   
本例子的模型检测例子bin文件就会检测失败
  
### 模型请参考  
[test.xml](../../../test/test30/test.xml)


### bin文件请参考  
[test.bin](../../../test/test30/test.bin)

### 被测代码请参考  

[target.c](../../../test/test30/target.c)


### 用例清参考  
[test.c](../../../test/test30/test.c)



### 参考如下操作

```
解压工具后进入目录
cd bufferfuzzer/test/test30

编译

gcc -c  ../../bufferfuzzer/model/*.c ../../bufferfuzzer/otherLib/*.c ../../bufferfuzzer/expand/Analyzer/*.c  ../../bufferfuzzer/expand/Fixup/*.c  ../../bufferfuzzer/expand/Transform/*.c ../../bufferfuzzer/expand/Relation/*.c ../../bufferfuzzer/expand/Check/*.c  -g -O0 -fsanitize=address ;g++ target.c test.c *.o -fsanitize=address -fsanitize-coverage=trace-pc,trace-cmp  -Wl,--whole-archive ../testlib/libcodefuzzer.a -Wl,--no-whole-archive  -o anner910  -O0 -g ;rm *.o


运行
./anner910 --count 1000000
```
