// #pragma clang diagnostic push
// #pragma clang diagnostic ignored "-Wundefined-internal"

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

// #pragma clang diagnostic pop

using namespace SymEngine;

int main() {
    std::cout << "你好，SymEngine!" << std::endl;

    // 创建符号和表达式
    RCP<const Basic> x = symbol("x");
    RCP<const Basic> y = symbol("y");
    RCP<const Basic> z = symbol("z");
    RCP<const Basic> w = symbol("w");

    // 创建一个表达式: (x + 2*y)**2
    RCP<const Basic> expr = pow(add(x, mul(integer(2), y)), integer(2));

    // 展开表达式
    RCP<const Basic> expanded = expand(expr);

    // 转化为 Latex 字符串
    std::string expr_latex = latex(*expr);
    std::string expanded_latex = latex(*expanded);

    std::cout << "原始表达式： " << expr_latex << std::endl;
    std::cout << "展开表达式： " << expanded_latex << std::endl;

    // 创建 LaTeX 文档内容
    std::string latex_doc =
R"(\documentclass{ctexart}
\usepackage[left=1.0cm,right=2cm,top=1cm,bottom=1.2cm,]{geometry}
\usepackage{paralist}
\let\itemize\compactitem
\let\enditemize\endcompactitem
\let\enumerate\compactenum
\let\endenumerate\endcompactenum
\let\description\compactdesc
\let\enddescription\endcompactdesc
\usepackage{extarrows}
\usepackage{amsmath}

\usepackage{color}%%写GoodA4这个文档的时候加的2022-3-3，因为我想改变某些文字的颜色。方法是在前面包含这个，然后\textcolor{red/blue/green/black/white/cyan/magenta/yellow}{text}其中textcolor{...}中包含的是系统定义好的颜色。实验证明，很好用。
\usepackage{bm}%%写GoodA4这个文档的时候加的2022-3-10，因为我想给公式中字体加粗。方法是在前面包含这个，然后\bm{text}。实验证明，很好用。
\usepackage{setspace}%设置行间距为22pt。在下面\begin {document}之后，加上\setstretch{1.8}，这个非常好用，非常美观，而且不需要我在代码中调整。
\usepackage{xcolor} % 想给文字加上边框和颜色，来突出重点。\fcolorbox    https://blog.csdn.net/qq_58517981/article/details/127080796
\usepackage{ulem} % 加下划线、波浪线、删除线等 \uline{下划线示例}  \uuline{双下划线示例} \dashuline{虚划线示例} \dotuline{点划线示例} \uwave{波浪线示例} \sout{删除线示例} \xout{斜删除线示例}
\usepackage{multirow} % for cmd 'multirow', 'multicolumn'
\usepackage{chemfig}
\usepackage[version=4]{mhchem} % 化学式宏包
\usepackage{fontawesome}
\usepackage{tabularx}
\usepackage{makecell}

\usepackage{output}
%\usepackage{hyperref} %生成引用链接，注：该宏包可能与其他宏包冲突，故放在所有引用的宏包之后。查了帮助，没有文字加粗选项。使用方法：\href{URL}{\textbf{text}}
%\hypersetup{colorlinks = true, %将链接文字带颜色
%	    linkcolor = black, %图表引用颜色设置为蓝色
%	    urlcolor = blue,%网页链接为蓝色
%            citecolor = blue} %文献引用颜色设置为蓝色

\title{\textcolor{red}{\textbf{平时学习的Linux知识003}}}
\author{孙伟国}
\date{\today}

\begin{document}
\maketitle
	\setstretch{1.8}%设置行间距为22pt。在前面加上\usepackage{setspace}，这个非常好用，非常美观，而且不需要我在代码中调整。
	\begin{enumerate}[left=0pt .. \parindent]
		\setcounter{enumi}{0}
% 从这行开始，为文档内容

\item \textcolor{red}{\textbf{第一题：椭圆}}\\
原始表达式： $)" + expr_latex + R"($\\
展开表达式： $)" + expanded_latex + R"($

\end{enumerate}
\end{document})";

    // 写入 .tex 文件
    std::ofstream outfile("output.tex");
    outfile << latex_doc;
    outfile.close();

    // 调用系统命令编译 LaTeX （需要系统安装有 pdflatex）
    system("xelatex -synctex=1 -shell-escape -interaction=nonstopmode output.tex");

    system("okular output.pdf");


    return 0;
}

