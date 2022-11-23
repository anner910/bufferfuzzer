### 简介

我们可以参考工具自带的crc32程序实现自己的Fixup类型  


1.参考[EFixupCrc32.c](../../bufferfuzzer/expand/Fixup/EFixupCrc32.c)文件中的下列函数实现加密解密过程

```
void doCrc32(elementBinContent *value, elementBinContent *blob) 
```

2.参考[MdoFixup.c](../../bufferfuzzer/model/MdoFixup.c)文件下列函数注册Fixup函数

```
void do_fixup_after(elementBinContent *tree)
```

3.参考类型FixupType_Crc32增加自己的类型