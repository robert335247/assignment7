#ifndef GAME_OBJECT_FACTORY_H // d
#define GAME_OBJECT_FACTORY_H

#include "gameObject.h"
#include "collider.h"

class GameObjectFactory {
public:
    static GameObject* createStaticObject(int x, int y); // 建立靜態物件 
    static GameObject* createDynamicObject(int x, int y); // 建立動態物件
};

class StaticObject : public GameObject, public ICollider{
public:
    StaticObject(int x, int y) { // 建構子
        _pos.x() = x; _pos.y() = y;
        _icon = IconFactory::createStaticIcon(); // 從 IconFactory 取得圖案，並將其賦值給 _icon
    }

    void update(int x, int y) override {}
    void onCollision(ICollider* other) override {}
    bool intersect(ICollider* other) override {}
};

class DynamicObject : public GameObject, public ICollider{
private:
    int _collisionCount; // 碰撞次數
    bool _gameOver; // 遊戲是否結束

public:
    
    DynamicObject(int x, int y) {
        _collisionCount = 0;  
        _gameOver = false;   
        _pos.x() = x; _pos.y() = y;
        _icon = IconFactory::createDynamicIcon();
    }

    int get_collisionCount() {
        return _collisionCount;
    }

    bool get_gameOver() {
        return _gameOver;
    }

    void resetGame() {
        _pos.x() = 12;
        _pos.y() = 15;
        _collisionCount = 0;
        _gameOver = false;
    }

    void update(int x, int y) override {
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

    void onCollision(GameObject* otherGameObject) override { // 發生碰撞

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
 
    bool intersect(GameObject* otherGameObject) override { // 是否發生碰撞

        // GameObject* otherGameObject = dynamic_cast<GameObject*>(other);

        if ((otherGameObject != nullptr)) {
            if ((this-> _pos.x() == otherGameObject-> _pos.x()) && 
                (this-> _pos.y() == otherGameObject-> _pos.y())) {
                return ture;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } 
};


#endif
