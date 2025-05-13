#include <iostream>
#include <ctime> // clock_t // 時間型別 // 儲存時間點
#include <thread> // this_thread // 目前這個執行緒
#include <unistd.h> // chrono // 將數字轉換成時間
#include <termios.h>
#include "environment.h"
#include "controller.h"
#include "gameObject.h"
#include "gameObjectFactory.h"
#include "view.h"

using namespace std;

// 建構子
// 輸入的參數是一個 View 物件
Controller::Controller(View& view)
    : _view(view) { 
    // 將 view 賦值給 _view // 參考無法使用 this

}

void Controller::run() {
    // I/O加速
    ios::sync_with_stdio(false);
    cin.tie(0); 

    // 初始化狀態
    configure_terminal();
    int input = -1;
    clock_t start, end;
    
    // 主迴圈 // 無限迴圈
    while (true) {

        start = clock(); // 記錄開始時間
        input = read_input();

        // 若玩家按下 ESC 鍵，則會跳出迴圈
        if (input == 27) {
            break;
        }

        handleInput(input);
        _view.resetLatest(); // 初始化畫面

        for(int i = 0; i < _objs.size(); i++) {
            _view.updateGameObject(_objs[i]); // 變更畫面
        }

        _view.render(); // 將畫面顯示於螢幕
        end = clock(); // 紀錄結束時間

        // 將此張畫面實際停留的時間的單位轉換為秒 
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

        // 判斷是否需要延遲此張畫面
        // 若此張畫面實際停留的時間 >= 此張畫面預計停留的時間，則不需要延遲此張畫面
        if (time_taken >= SPF) { 
            continue;

        // 若此張畫面實際停留的時間 < 此張畫面預計停留的時間，則需要延遲此張畫面
        } else if (time_taken < SPF) { 

            // 計算此張畫面需要延遲幾毫秒 (1 秒 = 1000 毫秒)
            int frameDelay = int((SPF - time_taken) * 1000); 

            // 將目前這個執行緒休眠 frameDelay 毫秒
            this_thread::sleep_for(chrono::milliseconds(frameDelay)); 
        }       
    }
}

void Controller::addGameObject(GameObject* obj) {
    _objs.push_back(obj);
}

void Controller::handleInput(int input) { // d
    if (input == 119) { 
        _objs[0]-> update(0, -1); // w // 上 
    } else if (input == 115) {  
        _objs[0]-> update(0, 1); // s // 下
    } else if (input == 97) { 
        _objs[0]-> update(-1, 0); // a // 右
    } else if (input == 100) { 
        _objs[0]-> update(1, 0); // d // 左
    } else {
        return;
    }
}

void reset_terminal() {
    printf("\e[m"); // 改變文字樣式
    printf("\e[?25h"); // 顯示游標
    fflush(stdout); // 清空標準輸出緩衝區
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios); // 還原舊設定
}

void configure_terminal() {
    tcgetattr(STDIN_FILENO, &old_termios); // 取得目前終端機的設定，並將其儲存在 old_termios 結構中
	new_termios = old_termios; 
    
    new_termios.c_lflag &= ~(ICANON | ECHO); // 關閉自動回顯與行緩衝模式
    new_termios.c_cc[VMIN] = 0;
    new_termios.c_cc[VTIME] = 0; // 開啟非阻塞輸入

    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios); // 將修改後的新設定 new_termios 套用到標準輸入

    printf("\e[?25l"); // 隱藏游標
    atexit(reset_terminal); // 此函式需於一個程式結束時自動執行
}


int read_input() {
    fflush(stdout);
   	char buf[4096]; // 建立標準輸入緩衝區
	int n = read(STDIN_FILENO, buf, sizeof(buf)); // 輸入的字元數量
    
    if (n > 0) {
        return buf[n - 1]; // 回傳最後一個輸入的字元
    } else {
        return -1; // 表示沒有輸入任何資料
    }
}

