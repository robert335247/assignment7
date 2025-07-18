#include "gameObjectFactory.h" // d
#include "iconFactory.h"
#include "environment.h"

StaticObject::StaticObject(int x, int y) { // 建構子
    _pos.x() = x; _pos.y() = y;
    _icon = IconFactory::createStaticIcon(); // 從 IconFactory 取得圖案，並將其賦值給 _icon
}

void StaticObject::update(int x, int y) {}

void StaticObject::onCollision(GameObject* otherGameObject) {};
 
bool StaticObject::intersect(GameObject* otherGameObject) {};

    // void update(int x, int y) override {}
    // void onCollision(ICollider* other) override {}
    // bool intersect(ICollider* other) override {}
    
DynamicObject::DynamicObject(int x, int y) {
    _collisionCount = 0;  
    _gameOver = false;   
    _pos.x() = x; _pos.y() = y;
    _icon = IconFactory::createDynamicIcon();
}

int DynamicObject::get_collisionCount() {
    return _collisionCount;
}

bool DynamicObject::get_gameOver() {
    return _gameOver;
}

void DynamicObject::resetGame() {
    _pos.x() = 12;
    _pos.y() = 15;
    _collisionCount = 0;
    _gameOver = false;
}

void DynamicObject::update(int x, int y) {
    if (x == 0 && y == 1) {
    _pos.y() += 1;
    } else if (x == 0 && y == -1) {
    _pos.y() -= 1;
    } else if (x == 1 && y == 0) {
    _pos.x() += 1;
    } else if (x == -1 && y == 0) {
    _pos.x() -= 1;
    }

    if (_pos.x() > GAME_WINDOW_WIDTH - 1) {
        _pos.x() = 0;
    }

    if (_pos.x() < 0) {
        _pos.x() = GAME_WINDOW_WIDTH - 1;
    }

    if (_pos.y() > GAME_WINDOW_HEIGHT - 1) {
        _pos.y() = 0;
    }

    if (_pos.y() < 0) {
        _pos.y() = GAME_WINDOW_HEIGHT - 1;
    }
}

    void DynamicObject::onCollision(GameObject* otherGameObject) { // 發生碰撞

        // 透過 dynamic_cast 嘗試將 other 的型態從 ICollider* 轉換成 GameObject*
        // GameObject* otherGameObject = dynamic_cast<GameObject*>(other);

        // 如果轉換成功 (otherGameObject != nullptr) 
        if (otherGameObject != nullptr) {
            _pos.x() = 12;
            _pos.y() = 15;
        }

        _collisionCount++; // 碰撞次數 +1

        if (_collisionCount >= 3) {
            _gameOver = true;
        }
    }
 
    bool DynamicObject::intersect(GameObject* otherGameObject) { // 是否發生碰撞

        // GameObject* otherGameObject = dynamic_cast<GameObject*>(other);

        if ((otherGameObject != nullptr)) {
            if ((this-> getPosition().x() == otherGameObject-> getPosition().x()) && 
                (this-> getPosition().y() == otherGameObject-> getPosition().y())) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } 

GameObject* GameObjectFactory::createStaticObject(int x, int y) {
    return new StaticObject(x, y);
    // 動態分配記憶體 // 建立一個新的 StaticObject(x, y)，並將其存入此新分配的記憶體中
    // 回傳此 StaticObject 的指標
}

GameObject* GameObjectFactory::createDynamicObject(int x, int y) {
    return new DynamicObject(x, y);
}


