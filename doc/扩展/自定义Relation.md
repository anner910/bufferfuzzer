### 简介

我们可以参考工具自带的sizeAddSub程序实现一些size字段与value值有偏移的情况


1.参考[ERelationSizeAdjust.c](../../bufferfuzzer/expand/Relation/ERelationSizeAdjust.c)文件中的下列函数实现加密解密过程

```
int doSizeAddSub4Get(int size)  
int doSizeAddSub4Set(int size) 
```

2.参考[MdoRelation.c](../../bufferfuzzer/model/MdoRelation.c)文件下列函数注册调整函数

```
int do_relation_get(elementBinContent *tree)
int do_relation_set(elementBinContent *tree)
```

3.参考类型RelationType_SizeAddSub4增加自己的类型