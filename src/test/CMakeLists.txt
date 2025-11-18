# 生成测试可执行文件
add_executable(
    data_structure_test
    
    hello_test.cc
    
    algorithm/pattern_matching/kmp_test.cc
    algorithm/sort/sort_test.cc

    structure/composite/composite_test.cc
    structure/list/list_test.cc
    structure/list/stack_test.cc
    structure/list/queue_test.cc
    
    structure/tree/disjoint_set_test.cc
    
    structure/graph/graph_test.cc

    )

# 链接 structure  algorithm库，继承其头文件路径
target_link_libraries(
  data_structure_test
  structure
  algorithm 
  gtest 
  gtest_main
)
# Now simply link against gtest or gtest_main as needed. Eg
include(GoogleTest)
gtest_discover_tests(data_structure_test)