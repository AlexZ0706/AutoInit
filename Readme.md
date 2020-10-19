# Auto initialize

修改自 rtthread 系统，用于函数列表自动初始化

修改参考了 [RTT笔记-分析自动初始化机制](#https://www.jianshu.com/p/9d377ddc8acc) 文章的分析

使用时在 main 函数开头调用 `level1_init();` 和 `level2_6_init()` 函数进行函数列表初始化
