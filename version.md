# 版本发布时间与内容

```
v1.0.0 2022-11-1123
1.第一个正式版本


v0.31 2022-11-1122
1.模型变异算法支持开关
2.整理全局变量声明
3.封装对外接口，方便移植
4.增加自定义check(constraint)说明
5.增加工具原理说明
6.整体修改元素名称
7.修改Relation count计算错误的bug
8.适配mp4文件格式
9.支持与codefuzzer变异样本联动，方便复现

v0.30 2022-11-1120
1.增加使用举例
2.增加gtest场景使用举例
3.支持基于模型的变异算法


v0.29 2022-11-1119
1.第一次变异增加debug打印
2.修改无长度Buf元素第一次变异出一字节的bug
3.修改整数变异后大小端赋值错误的bug
4.修改Bits变异后大小端赋值错误的bug
5.修改paddinng后期长度计算错误


v0.28 2022-11-1118
1.支持mutator配置
2.增加analyzer说明


v0.27 2022-11-1117
1.支持Configure修改模型中value值
2.支持Defaults修改整数类型的大小端全局设置


v0.26 2022-11-1117
1.适配jpg文件格式


v0.25 2022-11-1117
1.支持bin样本以buf,size形式输入
2.增加arp协议适配
3.增加ipv4协议适配
4.增加dhcp协议适配
5.增加http协议适配


v0.24 2022-11-1117
1.优化建模说明文档
2.修改relation count找不到relation bug
3.修改读样本文件多结尾0的bug
4.文档目录调整


v0.23 2022-11-1115
1.优化数组个数建模
2.支持relation count
3.增加模型解析bin过程各种失败原因打印
4.修改ref拷贝内存泄漏的bug
5.修改内部解析失败resolvedNoLength被置空的bug
6.修改bits大小端解析错误
7.修改ref引用次数过多relation字段查找不到的问题
8.修改数组不支持多个儿子的问题


v0.22 2022-11-1110
1.支持带儿子覆盖的的ref
2.支持数字设置大小端

v0.21 2022-11-1109
1.修改choice在没有bin时候解析bug
2.优化fixup查找
3.支持icmpchecksum类型的fixup
4.优化hex赋值
5.支持整数类型hex赋值
6.修改属性之间多空格丢属性问题
7.支持padding

v0.20 2022-11-1107
1.最大输出buf改为可调节
2.单个元素最大变异长度改为可调节
3.优化data调试打印
4.优化mlib函数名称
5.优化临时buf使用
6.优化结构体中各value，改为使用malloc

v0.19 2022-11-1107
1.优化relation查找
2.修改bit是relation的取值bug
3.支持ref

v0.18 2022-11-03
1.支持bits(flags)

v0.17 2022-11-02
1.支持多模型多buf用例

v0.16 2022-11-02
1.优化relation,支持s32等数据类型
2.支持 模型+setget直接混合调用
3.修改relation长度解析bug
4.优化解析bin时数据打印，方便定位
5.优化fuzz变异过程打印


v0.15 2022-11-01
1.支持自定义新的Analyzer类型

v0.14 2022-11-01
1.支持transform类型建模
2.支持自定义新的transform类型
3.支持自定义新的fixup类型
4.支持自定义新的relation类型

v0.13 2022-10-29
1.支持fixip类型建模

v0.12 2022-10-29
1.支持hex类型的value赋值
2.支持ipv4类型的value赋值

v0.11 2022-10-29
1.优化模型元素类型

v0.10 2022-10-29
1.增加s8,s16,s32,s64
u8,u16,u32,u64,float,double类型

v0.9 2022-10-28
1.支持数组建模

v0.8 2022-10-28
1.支持可选结构体建模

v0.7 2022-10-22
1.优化测试用例头文件路径
2.增加工具cmake编译方式

v0.6 2022-10-21
1.增加xml解析过程debug打印

v0.5 2022-10-21
1.支持josn通用模型
2.支持xml通用模型

v0.4 2022-10-21
1.支持解析bin文件
2.支持单进程多用例编写

v0.3 2022-10-20
1.支持tlv建模
2.优化xml value解析

v0.2  2022-10-20
1.支持结构体建模，block
2.修改整数value赋值bug

v0.1  2022-10-20
支持普通元素建模，支持blob,string,number   

```
