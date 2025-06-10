#ifndef GAME_OBJECT_FACTORY_H // d
#define GAME_OBJECT_FACTORY_H

#include "gameObject.h"
#include "collider.h"
#include "iconFactory.h"

class GameObjectFactory {
public:
    static GameObject* createStaticObject(int x, int y); // 建立靜態物件 
    static GameObject* createDynamicObject(int x, int y); // 建立動態物件
};

class StaticObject : public GameObject, public ICollider{
public:
    StaticObject(int x, int y); // 建構子
    
    void update(int x, int y) override;

    void onCollision(GameObject* otherGameObject) override;
 
    bool intersect(GameObject* otherGameObject) override;

    // void update(int x, int y) override {}
    // void onCollision(ICollider* other) override {}
    // bool intersect(ICollider* other) override {}
};

class DynamicObject : public GameObject, public ICollider{
private:
    int _collisionCount; // 碰撞次數
    bool _gameOver; // 遊戲是否結束

public:
    
    DynamicObject(int x, int y);

    int get_collisionCount();

    bool get_gameOver();

    void resetGame();

    void update(int x, int y) override;

    void onCollision(GameObject* otherGameObject) override;
 
    bool intersect(GameObject* otherGameObject) override;
};


#endif
