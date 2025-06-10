#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <vector>
#include "unit.h"
#include "icon.h"
#include "collider.h"

using namespace std;

class GameObject {
protected:
    Position _pos;
    Icon _icon;

public:
    Position getPosition() const;
    Icon getIcon() const;
    virtual void update(int x, int y) = 0;
    bool intersect(ICollider* other) override; // 是否發生碰撞
    void onCollision(ICollider* other) override; // 發生碰撞
};

#endif
