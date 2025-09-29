#include <iostream>
#include <fstream> // 用于写入文件

// 包含 SymEngine 的主要头文件
#include <symengine/basic.h>
#include <symengine/symbol.h>
#include <symengine/integer.h>
#include <symengine/add.h>
#include <symengine/mul.h>
#include <symengine/pow.h>
#include <symengine/printers/latex.h> // 包含 Latex 的输出功能

using namespace SymEngine;

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("无法打开文件: " + filename);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void generateLatexDocument(const std::string& latex_document_section) {
    std::string latex_template = readFile("../template.tex");
    std::string latex_footer = readFile("../footer.tex");

    std::stringstream latex_doc_stream;
    latex_doc_stream << latex_template << latex_document_section << latex_footer;

    std::string latex_doc = latex_doc_stream.str();

    // 写入 .tex 文件
    std::ofstream outfile("output.tex");
    outfile << latex_doc;
    outfile.close();
}

int main() {
    // 创建 LaTeX 文档内容
    std::stringstream latex_doc_stream;

    // 创建符号和表达式
    RCP<const Basic> x = symbol("x");
    RCP<const Basic> y = symbol("y");
    RCP<const Basic> z = symbol("z");
    RCP<const Basic> w = symbol("w");

    // 创建一个表达式: (x + 2*y)**2
    RCP<const Basic> expr = pow(add(x, mul(integer(2), y)), integer(2));
    std::string expr_latex = latex(*expr); // 转化为 Latex 字符串

    // 展开表达式
    RCP<const Basic> expanded = expand(expr);
    std::string expanded_latex = latex(*expanded); // 转化为 Latex 字符串

    latex_doc_stream << R"(\item \textcolor{red}{\textbf{第一题：请把下面的表达式展开}})" << R"(\\)" << "\n";
    latex_doc_stream << "原始表达式： " << R"($)" << expr_latex << R"($)" << R"(\\)" << "\n";
    latex_doc_stream << "展开表达式： " << R"($)" << expanded_latex << R"($)" << R"(\\)" << "\n";

    // latex_doc_stream最终生成为一个.tex文档的document部分。通过下面的函数，把头和尾加上，就形成了完整的的output.tex文档。
    generateLatexDocument(latex_doc_stream.str());
    // 编译生成最新的 PDF。调用系统命令编译 LaTeX （需要系统安装有 xelatex）
    system("xelatex -synctex=1 -shell-escape -interaction=nonstopmode output.tex");
    system("okular --unique --qwindowgeometry 1920x1080+0+0 output.pdf");


    return 0;
}

