#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include "AnsiPrint.h"


// a few constant ansi formatting string
const char *init="\x1b[";
const char *endc="m";
const char *hilit="1;";
const char *blink="5;";
const char *recover="\x1b[0m";
const char *fgBase="30;";
const char *bgBase="40;";
const int kFormatStrSize=20;

/** 
 * This function takes a string and ansi formatting option such as 
 * foreground and background colors, hilighting for foreground color,
 * and blinking option and then send the appropriate string to the
 * standard output. 
 * The options except for the foreground color are optional. 
 */
std::string
AnsiPrint(const char *str, Color fg, Color bg, bool hi, bool blinking) {

    // kick out exceptional case
    if ((str==NULL)||(strlen(str)==0))
        return "";
    // creating foreground and background options
    char *foreground=strdup(fgBase);
    foreground[1]+=fg;
    char *background=strdup(bgBase);
    background[1]+=bg;
    // initialize the formatting string
    char formatStr[kFormatStrSize]="";
    strcat(formatStr, init);
    // according to the options, append appropriate string
    if (hi) {
        strcat(formatStr, hilit);
    }
    if (blinking) {
        strcat(formatStr, blink);
    }
    if (fg!=NOCHANGE) {
        strcat(formatStr, foreground);
    }
    if (bg!=NOCHANGE) {
        strcat(formatStr, background);
    }
    // terminate the options
    if (formatStr[strlen(formatStr)-1]==';')
        formatStr[strlen(formatStr)-1]= '\0';
    strcat(formatStr,endc);


    free(background);
    free(foreground);

    std::string res;
#ifdef _WIN
    res.append(str)
#else
    res.append(formatStr);
    res.append(str);
    res.append(recover);
#endif

    return res;
}

/** 
 * This function takes a string and ansi formatting option such as 
 * hilighting for foreground color,  and blinking option and 
 * then send the appropriate string to the standard output. 
 * The two options are optional. So, when no options are given,
 * it prints the string as normal string.
 */

std::string
AnsiPrint(const char *str, bool hi, bool blinking) {

    // kick out exceptional case
    if ((str==NULL)||(strlen(str)==0))
        return "";

    char formatStr[kFormatStrSize]="";
    if (hi||blinking) {
        // initialize the formatting string
        strcat(formatStr, init);
        // according to the options, append appropriate string
        if (hi) {
            strcat(formatStr, hilit);
        }
        if (blinking) {
            strcat(formatStr, blink);
        }
        if (formatStr[strlen(formatStr)-1]==';')
            formatStr[strlen(formatStr)-1]= '\0';
        strcat(formatStr,endc);
    }

    std::string res;
#ifdef _WIN
    res.append(str)
#else
    res.append(formatStr);
    res.append(str);
    res.append(recover);
#endif

    return res;


}




