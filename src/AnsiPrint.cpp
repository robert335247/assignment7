#include <cstdlib> // d
#include <cstring>
#include <iostream>
#include "AnsiPrint.h"

using namespace std;

// 一些與 ANSI 格式化相關的常數字串
const char *init="\x1b[";
const char *endc="m";
const char *hilit="1;";
const char *blink="5;";
const char *recover="\x1b[0m";
const char *fgBase="30;";
const char *bgBase="40;";
const int kFormatStrSize=20;


// 此函式接收一個字串和 ANSI 格式化選項，如前景色、背景色、前景色加亮、閃爍效果等，  
// 然後將適當的格式化字串輸出到標準輸出。除了前景色外，其餘選項都是可選的。  
void AnsiPrint(const char *str, color fg, color bg, bool hi, bool blinking) {

    // 排除異常情況
    if ((str==NULL)||(strlen(str)==0))
     return;

    // 建立前景色與背景色選項
    char *foreground=strdup(fgBase);
    foreground[1]+=fg;
    char *background=strdup(bgBase);
    background[1]+=bg;

    char formatStr[kFormatStrSize]="";

    // 初始化格式化字串
    strcat(formatStr, init);

    // 根據選項附加適當的格式字串
    if (hi) {
        strcat(formatStr, hilit);
    }
    if (blinking) {
        strcat(formatStr, blink);
    }
    if (fg!=nochange) {
        strcat(formatStr, foreground);
    }
    if (bg!=nochange) {
        strcat(formatStr, background);
    }

    // 結束格式設定 
    if (formatStr[strlen(formatStr)-1]==';')
        formatStr[strlen(formatStr)-1]= '\0';
    strcat(formatStr,endc);

    // 輸出到標準輸出
    #ifdef _WIN
    cout << str;
    #else
    cout << formatStr << str << recover;
    #endif
    // 釋放已分配的緩衝區 
    free(background);
    free(foreground);
    return;

}

// 此函式接收一個字串和 ANSI 格式化選項，如前景色加亮與閃爍效果，  
// 然後將適當的格式化字串輸出到標準輸出。這兩個選項都是可選的，
// 因此如果未提供選項，則會以普通字串的方式輸出。  
void AnsiPrint(const char *str, bool hi, bool blinking) {

    // 排除異常情況 
    if ((str==NULL)||(strlen(str)==0))
        return;
    
    char formatStr[kFormatStrSize]="";

    if (hi||blinking) {
        // 初始化格式化字串 
        strcat(formatStr, init);

        // 根據選項附加適當的格式字串
        if (hi) {
            strcat(formatStr, hilit);
        }
        if (blinking) {
            strcat(formatStr, blink);
        }

        // 結束格式設定 
        if (formatStr[strlen(formatStr)-1]==';')
            formatStr[strlen(formatStr)-1]= '\0';
        strcat(formatStr,endc);
    }

    // 輸出到標準輸出
    #ifdef _WIN
    cout << str;
    #else
    cout << formatStr << str << recover;
    #endif
    return;

}





