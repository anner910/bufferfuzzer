

[toc]


# 前言


开发bufferfuzzer的初衷，主要是想白盒fuzz工具拥有这样的能力  
```
对于那些带有结构的buffer测试目标，无论是文件，协议，消息，还是json,xml等类型，
通过建模，让白盒fuzz工具了解buffer的内部结构，
并针对结构内子元素的类型，大小，初值，元素之间的关系等，
进行针对性变异，以提高变异效率，从而发现更多安全问题
```
希望我的工具可以帮助到你

# 简介

工具基于codefuzzer工具扩展开发，需要同时连接libcodefuzzer.a使用，并引用工具的头文件bufferfuzzer.h，  
就可以编写你的测试用例，针对函数接口进行fuzzing测试

# 如何编译工具
[工具如何编译](./doc/工具如何编译.md)  

# 如何编译被测代码
[如何编译被测代码](./doc/如何编译被测代码.md)  

# 简单使用举例
[例子1](./doc/例子1.md)   
[例子2](./doc/例子2.md)   

# 用例编写
[单独模型用例](./doc/用例编写/单独模型用例.md)  
[模型+bin文件用例.md](./doc/用例编写/模型+bin文件用例.md)  
[多模型用例.md](./doc/用例编写/多模型用例.md)   
[单程序多用例](./doc/用例编写/单程序多用例.md)  
[模型+setget直接调用](./doc/用例编写/模型+setget直接调用.md)  

# 建模

### 普通元素
[元素Number建模](./doc/建模/元素/元素Number建模.md)   
[元素S32等建模](./doc/建模/元素/元素S32等建模.md)   
[元素String建模](./doc/建模/元素/元素String建模.md)   
[元素Buf(Blob)建模](./doc/建模/元素/元素Buf(Blob)建模.md)   
[元素Bit(Flag)建模](./doc/建模/元素/元素Bit(Flag)建模.md)   
[元素Padding建模](./doc/建模/元素/元素Padding建模.md)  
 

### 结构元素
[结构BufferFuzzer建模](./doc/建模/结构/结构BufferFuzzer建模.md)  
[结构Buffer(DataModel)建模](./doc/建模/结构/结构Buffer(DataModel)建模.md)  
[结构Struct(Block)建模](./doc/建模/结构/结构Struct(Block)建模.md)  
[结构Union(Choice)建模](./doc/建模/结构/结构Union(Choice)建模.md)  
[结构Array建模](./doc/建模/结构/结构Array建模.md)  
[结构Bits(Flags)建模](./doc/建模/结构/结构Bits(Flags)建模.md)  
[结构Transform建模](./doc/建模/结构/结构Transform建模.md)  


### 属性
[属性name](./doc/建模/属性/属性name.md)   
[属性length](./doc/建模/属性/属性length.md)  
[属性size](./doc/建模/属性/属性size.md)  
[属性valueType](./doc/建模/属性/属性valueType.md)  
[属性token](./doc/建模/属性/属性token.md)  
[属性check(constraint)](./doc/建模/属性/属性check(constraint).md)  

### 关系修饰元素
[ref建模](./doc/建模/ref建模.md)  
[Relation(Size)建模](./doc/建模/Relation(Size)建模.md)  
[Relation(Count)建模](./doc/建模/Relation(Count)建模.md)  
[Fixup建模](./doc/建模/Fixup建模.md)  
[Analyzer建模](./doc/建模/Analyzer建模.md)  


### 配置
[Configure](./doc/建模/Configure.md)    
[Defaults](./doc/建模/Defaults.md)    
[mutator](./doc/建模/mutator.md)    

# 适配

### 场景
[适配gtest](./doc/适配/适配gtest.md)  

### 协议
[arp](./doc/适配/arp.md)    
[ipv4](./doc/适配/ipv4.md)    
[dhcp](./doc/适配/dhcp.md)  
[http](./doc/适配/http.md)  
[httpRest](./doc/适配/httpRest.md) 

### 文件
[jpg](./doc/适配/jpg.md)  
[mp4](./doc/适配/mp4.md) 

### 通用建模

[json通用建模](./doc/适配/json通用建模.md)  
[xml通用建模](./doc/适配/xml通用建模.md)  

# 工具原理
[基本原理](./doc/工具原理/基本原理.md)   
[模型元素类型](./doc/工具原理/模型元素类型.md)   
[变异算法](./doc/工具原理/变异算法.md)   

# 扩展
[自定义Transform](./doc/扩展/自定义Transform.md)   
[自定义Fixup](./doc/扩展/自定义Fixup.md)   
[自定义Relation](./doc/扩展/自定义Relation.md)   
[自定义Analyzer](./doc/扩展/自定义Analyzer.md)  
[自定义check(constraint)](./doc/扩展/自定义check(constraint).md)  

# 调试 
[调试](./doc/调试.md)   
[模型测试](./doc/模型测试.md)   
[解析bin测试](./doc/解析bin测试.md)   
[普通测试](./doc/普通测试.md)   

# 其他
[bug复现](./doc/bug复现.md)    
[报告生成](./doc/报告生成.md) 

# 作者
6482543@qq.com   
wanghao  

