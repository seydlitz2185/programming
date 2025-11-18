# 生成 algorithm 库（包含所有子目录的源码）
add_library(
    algorithm INTERFACE

    pattern_matching/KMP.h
    sort/sort.h

)

# 暴露头文件路径：将当前目录（src/algorithm）添加到包含路径
target_include_directories(algorithm INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}  # 编译器会搜索 src/algorithm/ 下的头文件
)