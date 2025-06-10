#include "gameObjectFactory.h" // d
#include "iconFactory.h"
#include "environment.h"

GameObject* GameObjectFactory::createStaticObject(int x, int y) {
    return new StaticObject(x, y);
    // 動態分配記憶體 // 建立一個新的 StaticObject(x, y)，並將其存入此新分配的記憶體中
    // 回傳此 StaticObject 的指標
}

GameObject* GameObjectFactory::createDynamicObject(int x, int y) {
    return new DynamicObject(x, y);
}


