# mathematics-system

C 语言数学工具集（A collection of math utilities written in C）。

## Matrix

矩阵运算库（V1.0 / V1.0.1，2023 年 2-3 月）：矩阵的创建、加减乘等基本运算，附测试程序。

## BigInterge

字符串大整数四则运算（2023 年 3 月动工，8 月底重写完成）：符号与数值分离存储，
加法用反转+进位的竖式模拟，减法只做大减小（换序由上层符号系统负责），乘法用
错位相加，除法从"循环减法"重构成移位竖式。`BigInterge.c` 里的符号化归把
`-a + b => b - a` 这类四种组合全部落到无符号运算上。

```sh
gcc -std=c99 BigInterge/BigInterge.c BigInterge/string_math.c BigInterge/my_string.c BigInterge/memmanager.c -o biginterge
```

配套博文（含真实的运行输出与复盘）：[BigInterge 开发记：当 long long 装不下的时候](https://cosmical-container.github.io/posts/4d6809c9/)

## Fraction

分数运算库（2022 年 10-11 月）：`Fractional` 结构体构造即约分（递归 gcd +
负号化归），四则运算用"相反数借还"和"倒数乘回"两个小技巧复用加法与乘法；
`add/sub/mul/div(int n, ...)` 变参一次折叠 n 个分数；`float_to_Fractional`
把循环小数精确转回分数（0.123123... = 41/333）。`my_malloc_temp` 记账池
统一回收临时分数。`小数转分数.c` 是它的单文件调试前身，保留逐步打印。

```sh
gcc "Fraction/我的分数.c" -o fraction
```

配套博文（含真实的运行输出与复盘）：[我的分数开发记：手写一个分数运算库](https://cosmical-container.github.io/posts/2d141d28/)
