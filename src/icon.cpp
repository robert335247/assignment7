#include "icon.h"

using namespace std;

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


