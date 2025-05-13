#include "gameObjectFactory.h" // d
#include "iconFactory.h"
#include "environment.h"

class StaticObject : public GameObject {
public:
    StaticObject(int x, int y) { // 建構子
        _pos.e1 = x; _pos.e2 = y;
        _icon = IconFactory::createStaticIcon(); // 從 IconFactory 取得圖案，並將其賦值給 _icon
    }

    void update(int x, int y) override {}
};

class DynamicObject : public GameObject {
public:
    DynamicObject(int x, int y) {
        _pos.e1 = x; _pos.e2 = y;
        _icon = IconFactory::createDynamicIcon();
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
};

GameObject* GameObjectFactory::createStaticObject(int x, int y) {
    return new StaticObject(x, y);
    // 動態分配記憶體 // 建立一個新的 StaticObject(x, y)，並將其存入此新分配的記憶體中
    // 回傳此 StaticObject 的指標
}

GameObject* GameObjectFactory::createDynamicObject(int x, int y) {
    return new DynamicObject(x, y);
}


