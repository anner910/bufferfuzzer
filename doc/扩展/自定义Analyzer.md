### 简介

我们可以参考工具自带的Analyzer程序实现自己的Analyzer类型  


1.参考[EAnalyzerJson.c](../../bufferfuzzer/expand/Analyzer/EAnalyzerJson.c)文件中的下列解析过程

```
void do_json_before(elementBinContent *tree)
int do_json(elementBinContent *tree)
void do_json_after_free(elementBinContent *tree)
```

2.参考[MdoAnalyzer.c](../../bufferfuzzer/model/MdoAnalyzer.c)文件下列函数注册相关函数

```
void found_analyzer1(elementBinContent *tree)
int do_analyzer_fuzz(elementBinContent *tree)
void do_analyzer_free(elementBinContent *tree)
```

3.参考类型AnalyzerType_Json增加自己的类型