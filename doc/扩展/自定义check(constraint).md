### 简介

我们可以参考工具自带的CheckType_Http程序实现自己的check类型  


1.参考[ECheckHttp.c](../../bufferfuzzer/expand/Check/ECheckHttp.c)文件中的下列函数实现检测过程

```
int do_check_http_bin(elementBinContent *tree, char* bin, int length)
int do_check_http_value(elementBinContent *tree, char* value, int length)
```

2.参考[MdoCheck.c](../../bufferfuzzer/model/MdoCheck.c)文件下列函数注册check函数

```
int do_check_bin(elementBinContent *tree, char* bin, int length)
int do_check_value(elementBinContent *tree, char* value, int length)
```

3.参考类型CheckType_Http增加自己的类型