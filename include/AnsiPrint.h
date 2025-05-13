#ifndef _ANSIPRINT_H //d
#define _ANSIPRINT_H

using namespace std;

//#define _WIN
enum color {black=0, red, green, yellow, blue, pink, cyan, white, nochange};

// 使用指定的 ANSI 顏色選項來格式化並輸出字串
string AnsiPrint(const char *str, color fg, color bg = nochange, 
                   bool hi = false, bool blinking = false);
string AnsiPrint(const char *str, bool hi = false, bool blinking = false);

#endif
