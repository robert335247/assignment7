#ifndef ICON_H
#define ICON_H

#include <vector>
#include <string>
#include "unit.h"

using namespace std;

// 格子
struct Cell {
    Color color;
    string ascii;

    Cell(Color c, std::string a) : color(c), ascii(a){}

}; 

// Icon 是一個二維的 Cell 陣列
typedef vector<vector<Cell>> Icon; 

// 輸入的參數是一個 Icon 物件，而當此物件一被輸入進去後，
// 此物件將會傳參考到 icon，因此 icon 即為此物件的參考
// 回傳這這張 Icon 的寬度（橫向的 Cell 的數量）
size_t icon_width(const Icon &icon); 

// 回傳這這張 Icon 的高度（直向的 Cell 的數量)
size_t icon_height(const Icon &icon); 


#endif
