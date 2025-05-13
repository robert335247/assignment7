#include "icon.h"

using namespace std;

Cell::Cell(Color c, string a) { // 建構子
    this-> color = c;
    this-> ascii = a;
}

Color Cell::getcolor() const { // 取得顏色
    return color;
}

string Cell::getascii() const { // 取得字串
    return ascii;
}

size_t icon_width(const Icon& icon) {
    if (icon.empty() == 1) {
        return 0;
    } else {
        return icon[0].size(); // 回傳這這張 Icon 的長度（橫向的 Cell 的數量)
    }
}

size_t icon_height(const Icon& icon) {
    return icon.size(); // 回傳這這張 Icon 的高度（直向的 Cell 的數量)
}


