cmake_minimum_required(VERSION 3.10)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(test001 LANGUAGES CXX)

# 硬编码 Conda 环境路径
set(CONDA_ENV_PATH "/home/osbernsun/miniconda3/envs/cpp_symengine")
message(STATUS "Using Conda environment at: ${CONDA_ENV_PATH}")

# 手动设置头文件和库路径
set(SymEngine_INCLUDE_DIRS "${CONDA_ENV_PATH}/include")
set(SymEngine_LIBRARIES "${CONDA_ENV_PATH}/lib/libsymengine.so")
set(GMP_LIBRARIES
    "${CONDA_ENV_PATH}/lib/libgmp.so.10.5.0"
    "${CONDA_ENV_PATH}/lib/libgmpxx.so.4.7.0"
)
set(MPFR_LIBRARIES "${CONDA_ENV_PATH}/lib/libmpfr.so.6.2.1")
set(FLINT_LIBRARIES "${CONDA_ENV_PATH}/lib/libflint.so.20.0.1")

# 添加可执行文件
add_executable(test001 main.cpp)

# 使用 target_include_directories (这是正确的！)
target_include_directories(test001 PRIVATE ${SymEngine_INCLUDE_DIRS})
# 链接 SymEngine 库
target_link_libraries(test001 PRIVATE ${SymEngine_LIBRARIES})
# 根据你的错误提示，很可能还需要链接 GMP 和 MPC 库
target_link_libraries(test001 PRIVATE
    ${SymEngine_LIBRARIES}
    ${GMP_LIBRARIES}
    ${MPFR_LIBRARIES}
    ${FLINT_LIBRARIES}
)



# 可选：安装规则
install(TARGETS test001 RUNTIME DESTINATION bin)


