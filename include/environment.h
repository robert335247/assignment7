#ifndef ENVIROMENT_H
#define ENVIROMENT_H

// 遊戲畫面的寬度為 20 個格子
constexpr int GAME_WINDOW_WIDTH = 20; 

// 遊戲畫面的高度為 20 個格子
constexpr int GAME_WINDOW_HEIGHT = 20; 

// 1 個格子的寬度 = 2 個字元的寬度 
constexpr int GAME_WINDOW_CELL_WIDTH = 2; 

// 遊戲畫面的寬度為 40 個字元的寬度
constexpr int WINDOW_PIXEL_WIDTH = GAME_WINDOW_WIDTH * GAME_WINDOW_CELL_WIDTH; 

// 遊戲畫面的高度為 20 個格子
constexpr int WINDOW_PIXEL_HEIGHT = GAME_WINDOW_HEIGHT; 

// 每張畫面預計停留的時間 (1 秒)
constexpr double SPF = 1; 
#endif
