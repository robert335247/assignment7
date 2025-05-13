#include <iostream> // d
#include "gameObject.h" 
#include "gameObjectFactory.h"
#include "controller.h"
#include "environment.h"
#include "view.h"

// 取得位置
Position GameObject::getPosition() const {
    return _pos;
}

// 取得圖示
Icon GameObject::getIcon() const {
    return _icon;
}
