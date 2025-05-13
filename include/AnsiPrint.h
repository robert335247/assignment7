#ifndef _ANSIPRINT_H //d
#define _ANSIPRINT_H

//#define _WIN
enum color {black=0, red, green, yellow, blue, pink, cyan, white, nochange};

// 使用指定的 ANSI 顏色選項來格式化並輸出字串
void AnsiPrint(const char *str, color fg, color bg = nochange, 
                   bool hi = false, bool blinking = false);
void AnsiPrint(const char *str, bool hi = false, bool blinking = false);

#endif
