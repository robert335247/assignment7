#ifndef COLLIDER_H
#define COLLIDER_H

#include "gameObject.h"

class ICollider {
public:

    // 解構函式 // ~ICollider 是函式的名稱，~ 代表著當一個 ICollider 物件被銷毀時，
    // 此函式要被自動呼叫
    ~ICollider() {}; 

    virtual bool intersect(GameObject*) = 0; // 交叉
    virtual void onCollision(GameObject*) = 0; // 碰撞
};

#endif