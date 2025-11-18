cmake_minimum_required(VERSION 3.10)

# 编译器选项设置
option(USE_CLANG "Build with clang" OFF)
option(USE_GCC "Build with gcc" OFF)

# 设置MSYS2环境下的编译器路径
# 请根据实际安装路径修改
set(MSYS2_GCC_PATH "C:/msys64/mingw64/bin" CACHE PATH "MSYS2 MinGW-w64 GCC installation directory")
set(MSYS2_CLANG_PATH "C:/msys64/clang64/bin" CACHE PATH "MSYS2 Clang64 installation directory")

# 根据选项设置编译器
if(USE_CLANG)
    if(WIN32)
        set(CMAKE_C_COMPILER "${MSYS2_CLANG_PATH}/clang.exe")
        set(CMAKE_CXX_COMPILER "${MSYS2_CLANG_PATH}/clang++.exe")
        # 添加编译器目录到系统路径
        set(ENV{PATH} "${MSYS2_CLANG_PATH};$ENV{PATH}")
    endif()
elseif(USE_GCC)
    if(WIN32)
        set(CMAKE_C_COMPILER "${MSYS2_GCC_PATH}/gcc.exe")
        set(CMAKE_CXX_COMPILER "${MSYS2_GCC_PATH}/g++.exe")
        set(CMAKE_MAKE_PROGRAM "${MSYS2_GCC_PATH}/make.exe")
        # 强制使用MinGW Makefiles
        set(CMAKE_GENERATOR "MinGW Makefiles" CACHE INTERNAL "" FORCE)
        # 添加编译器目录到系统路径
        set(ENV{PATH} "${MSYS2_GCC_PATH};$ENV{PATH}")
    endif()
endif()

project(data_structure_with_gtest)
enable_testing()
include(GoogleTest)

# 设置运行时库为动态链接（MD/MDd）
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

# 设置编译器特定选项
if(MSVC)
    # MSVC特定选项
    add_compile_options(/utf-8 /wd4819)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)  # 禁用不安全函数警告
else()
    # GCC/Clang通用选项
    add_compile_options(-Wall -Wextra)
    if(USE_CLANG)
        add_compile_options(-Wno-missing-braces)
    endif()
endif()

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
include_directories(${GTEST_INCLUDE_DIRS})

# 添加算法和数据结构模块（先编译库）
add_subdirectory(src/algorithm)
add_subdirectory(src/structure)

# 最后添加测试目录（确保测试能链接到已定义的库）
add_subdirectory(src/test)


