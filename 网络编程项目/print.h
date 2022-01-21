#ifndef __PRINT_H__
#define __PRINT_H__

#if 0
关键部分的基本格式是：
printf("\033[字背景颜色;字体颜色m字符串\033[0m" );
printf("\033[47;31mhello world\033[5m");

47是字背景颜色, 31是字体的颜色, hello world是字符串. 后面的\033[5m是控制码

字背景颜色范围: 40--49 字颜色: 30--39

40: 黑 30: 黑

41: 红 31: 红

42: 绿 32: 绿

43: 黄 33: 黄

44: 蓝 34: 蓝

45: 紫 35: 紫

46: 深绿 36: 深绿

47: 白色 37: 白色
#endif
#define RED          "\033[0;32;31m"
#define LIGHT_RED    "\033[1;31m"
#define GREEN        "\033[0;32;32m"
#define LIGHT_GREEN  "\033[1;32m"
#define BLUE         "\033[0;32;34m"
#define LIGHT_BLUE   "\033[1;34m"
#define DARY_GRAY    "\033[1;30m"
#define CYAN         "\033[0;36m"
#define LIGHT_CYAN   "\033[1;36m"
#define PURPLE       "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN        "\033[0;33m"
#define YELLOW       "\033[1;33m"
#define LIGHT_GRAY   "\033[0;37m"
#define WHITE        "\033[1;37m"
//其他的控制码：

#define NONE "\033[0m"    //关闭所有属性

#define HLIGHT "\033[1m"   //设置高亮度
#if 0
\03[4m 下划线

\033[5m 闪烁

\033[7m 反显

\033[8m 消隐

\033[30m -- \033[37m 设置前景色

\033[40m -- \033[47m 设置背景色

\033[nA 光标上移n行

\03[nB 光标下移n行

\033[nC 光标右移n行

\033[nD 光标左移n行

\033[y;xH设置光标位置

\033[2J 清屏

\033[K 清除从光标到行尾的内容

\033[s 保存光标位置

\033[u 恢复光标位置

\033[?25l 隐藏光标

\33[?25h 显示光标
#endif
#endif
