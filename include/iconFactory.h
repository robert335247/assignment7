#ifndef ICON_FACTORY_H // d
#define ICON_FACTORY_H

#include "icon.h"

class IconFactory {
public:
    static Icon createStaticIcon(); // 建立靜態物件圖像
    static Icon createDynamicIcon(); // 建立動態物件圖像
};

#endif
