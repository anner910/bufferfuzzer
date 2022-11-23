### 简介

我们可以参考工具自带的base64程序实现自己的加解密Transform类型  


1.参考[ETransformBase64.c](../../bufferfuzzer/expand/Transform/ETransformBase64.c)文件中的下列函数实现加密解密过程

```
void doBase64Encode(elementBinContent *tree)  
void doBase64Decode(elementBinContent *tree)  
```

2.参考[MdoTransform.c](../../bufferfuzzer/model/MdoTransform.c)文件下列函数注册加解密函数

```
void do_transform_before(elementBinContent *tree)
void do_transform_after(elementBinContent *tree)
```

3.参考类型TransformType_Bas64增加自己的类型