#ifndef COLLIDER_H
#define COLLIDER_H

class ICollider {
public:

    // 解構函式 // ~ICollider 是函式的名稱，~ 代表著當一個 ICollider 物件被銷毀時，
    // 此函式要被自動呼叫
    ~ICollider() {}; 

    virtual bool intersect(ICollider*) = 0;
    virtual void onCollision(ICollider*) = 0;
};

#endif