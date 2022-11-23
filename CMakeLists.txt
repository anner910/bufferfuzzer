cmake_minimum_required(VERSION 3.22)

# 声明一个 cmake 工程
project(bufferfuzzer)

aux_source_directory(bufferfuzzer/model/ DIR_SRCS)
aux_source_directory(bufferfuzzer/otherLib/ DIR_SRCS)
aux_source_directory(bufferfuzzer/expand/Analyzer/ DIR_SRCS)
aux_source_directory(bufferfuzzer/expand/Fixup/ DIR_SRCS)
aux_source_directory(bufferfuzzer/expand/Transform/ DIR_SRCS)
aux_source_directory(bufferfuzzer/expand/Relation/ DIR_SRCS)
aux_source_directory(bufferfuzzer/expand/Check/ DIR_SRCS)

set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -O0 -g -fno-omit-frame-pointer")
set(CMAKE_C_FLAGS " ${CMAKE_C_FLAGS} -O0 -g -fno-omit-frame-pointer")

# 添加库( 库名（自己设置） 库的实现文件及路径 ）
add_library(bufferfuzzer SHARED ${DIR_SRCS})
