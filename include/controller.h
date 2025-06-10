#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <termios.h> // struct termios // termios 結構 // 控制終端機的 I/O 行為
#include <vector>
#include "view.h"
#include "gameObject.h"
#include "gameObjectFactory.h"
#include "collider.h"

using namespace std;

class Controller {
private:
    vector<GameObject*> _objs; // _objs[0] 為動態物件，_objs[1] 為靜止物件
    View& _view;  // _view 是一個 View 物件的參考

    void handleInput(int input); // 處理輸入

public:

    // 建構子 // 輸入的參數是一個 View 物件，而當此物件一被輸入進去後，
    // 此物件將會傳參考到 view，因此 view 即為此物件的參考
    Controller(View& view);
    void run();
    void addGameObject(GameObject* obj);
};

static struct termios old_termios; // 儲存原本終端機的設定
static struct termios new_termios; // 暫時修改終端機的設定
void reset_terminal(); // 將終端機的設定恢復為初始設定
void configure_terminal(); // 終端機的初始設定
int read_input(); // 閱讀輸入

#endif
