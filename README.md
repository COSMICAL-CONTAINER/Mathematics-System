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
