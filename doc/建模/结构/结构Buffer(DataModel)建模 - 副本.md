### 简介
通过 Block元素定义结构体 

### 模型清参考  
[test.xml](../../test/test2/test.xml)

```

<BufferFuzzer name="BufferFuzzer1" >


//数据模型
<DataModel name="DataModel1" >

	<Number name="Number1" size="32" value="1"/>
	
	//一个block里边可以放置多个子元素
    <Block name="Block1" >
	<Number name="Number2" size="32" value="1234"/>
        <String name="String4" value="ddd"/>
        <Blob name="Blob4" value="ggg"/>
    </Block>
	
	<Block name="Block2" >
            <Number name="Number3" size="32" value="123456"/>
            <String name="String2" value="ffffffffff"/>
        <Blob name="Blob3" value="ggggggggggg"/>
    </Block>
</DataModel>


</BufferFuzzer>
```

### 被测代码请参考  

[target.c](../../test/test2/target.c)


### 用例清参考  
[test.c](../../test/test2/test.c)


### 参考如下操作

```
解压工具后进入目录
cd bufferfuzzer/test/test2

编译

gcc -c  ../../bufferfuzzer/model/*.c ../../bufferfuzzer/otherLib/*.c ../../bufferfuzzer/expand/Analyzer/*.c  ../../bufferfuzzer/expand/Fixup/*.c  ../../bufferfuzzer/expand/Transform/*.c ../../bufferfuzzer/expand/Relation/*.c   -g -O0 -fsanitize=address ;g++ target.c test.c *.o -fsanitize=address -fsanitize-coverage=trace-pc,trace-cmp  -Wl,--whole-archive ../testlib/libcodefuzzer.a -Wl,--no-whole-archive  -o anner910  -O0 -g ;rm *.o


运行
./anner910 --count 1000000
```
