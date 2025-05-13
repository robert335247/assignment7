#ifndef GAME_OBJECT_FACTORY_H // d
#define GAME_OBJECT_FACTORY_H

#include "gameObject.h"

class GameObjectFactory {
public:
    static GameObject* createStaticObject(int x, int y); // 建立靜態物件 
    static GameObject* createDynamicObject(int x, int y); // 建立動態物件
};

#endif
