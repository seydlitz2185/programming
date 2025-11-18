# 生成 structure 库（包含所有子目录的源码）
add_library(
    structure INTERFACE

    composite/enum.h
    composite/union.h

    graph/graph.h

    list/list.h
    list/queue.h
    list/stack.h
    list/my_priority_queue_sample.h

    tree/disjoint_set.h

)

# 暴露头文件路径：将当前目录（src/structure）添加到包含路径
target_include_directories(structure INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}  # 编译器会搜索 src/structure/ 下的头文件
)