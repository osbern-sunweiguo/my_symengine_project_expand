#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundefined-internal"

#include <iostream>
// 包含 SymEngine 的主要头文件
#include <symengine/basic.h>
#include <symengine/symbol.h>
#include <symengine/integer.h>
#include <symengine/add.h>
#include <symengine/mul.h>
#include <symengine/pow.h>

#pragma clang diagnostic pop

using namespace SymEngine;

int main() {
    // std::cout << "你好，SymEngine!" << std::endl;

    // 创建符号和表达式
    RCP<const Basic> x = symbol("x");
    RCP<const Basic> y = symbol("y");
    RCP<const Basic> z = symbol("z");
    RCP<const Basic> w = symbol("w");

    // 创建一个表达式: (x + 2*y)**2
    RCP<const Basic> expr = pow(add(x, mul(integer(2), y)), integer(2));

    // 展开表达式
    RCP<const Basic> expanded = expand(expr);

    std::cout << "请展开这个表达式： " << *expr << std::endl;
    std::cout << "表达式展开后的结果是： " << *expanded << std::endl;

    return 0;
}

