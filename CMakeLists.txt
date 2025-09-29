cmake_minimum_required(VERSION 3.10)
project(SymEngineDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置 Conda 环境路径
set(CONDA_PREFIX "/home/osbernsun/miniconda3/envs/cpp_symengine")

# 手动链接所有必需的库
find_library(SYMENGINE_LIB symengine PATHS ${CONDA_PREFIX}/lib REQUIRED)
find_library(GMP_LIB gmp PATHS ${CONDA_PREFIX}/lib REQUIRED)
find_library(GMPXX_LIB gmpxx PATHS ${CONDA_PREFIX}/lib REQUIRED)
find_library(MPFR_LIB mpfr PATHS ${CONDA_PREFIX}/lib REQUIRED)

message(STATUS "SymEngine library: ${SYMENGINE_LIB}")
message(STATUS "GMP library: ${GMP_LIB}")
message(STATUS "GMP++ library: ${GMPXX_LIB}")
message(STATUS "MPFR library: ${MPFR_LIB}")

add_executable(test001 main.cpp)

# 链接所有必需的库
target_link_libraries(test001 PRIVATE
    ${SYMENGINE_LIB}
    ${GMPXX_LIB}
    ${GMP_LIB}
    ${MPFR_LIB}
)

# 添加包含目录
target_include_directories(test001 PRIVATE ${CONDA_PREFIX}/include)
