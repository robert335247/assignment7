#include <iostream> // d
#include <string>
#include <thread>
#include <chrono>
#include "view.h"
#include "controller.h"
#include "AnsiPrint.h"
#include "gameObjectFactory.h"

using namespace std;

// 輸出我的學號
void PrintMyID(string studId) {
    string str = "ID: " + studId;
    cout << AnsiPrint(str.c_str(),YELLOW,RED, true, true) << endl << endl;
}

int main() {
    View view;                      // 建立 View
    Controller controller(view);    // 將 View 傳給 Controller

    // 建立物件
    GameObject* StaticObject1 = GameObjectFactory::createStaticObject(4, 1);
    GameObject* StaticObject2 = GameObjectFactory::createStaticObject(4, 10);
    GameObject* StaticObject3 = GameObjectFactory::createStaticObject(6, 18);
    GameObject* StaticObject4 = GameObjectFactory::createStaticObject(7, 12);
    GameObject* StaticObject5 = GameObjectFactory::createStaticObject(19, 1);
    GameObject* DynamicObject1 = GameObjectFactory::createDynamicObject(12, 15);

    // 加入 Controller 管理
    controller.addGameObject(StaticObject1);
    controller.addGameObject(StaticObject2);
    controller.addGameObject(StaticObject3);
    controller.addGameObject(StaticObject4);
    controller.addGameObject(StaticObject5);
    controller.addGameObject(DynamicObject1);

    // 主迴圈
    controller.run();  // 改為呼叫 run()，內部會處理輸入與更新

    PrintMyID("113703038");

    return 0;
}