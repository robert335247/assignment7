#include "view.h"
#include "environment.h"
#include "AnsiPrint.h"
#include <codecvt>      // wstring_convert
#include <cwchar>       // wcwidth
#include <sys/ioctl.h>   // winsize, TIOCGWINSZ
#include <unistd.h>  //  STDOUT_FILENO
#include <iostream>
#include <locale>
#include <utility>

using namespace std;

// 傳回單一字串在終端機中實際顯示的長度
int displayWidth(const string& utf8) {
    static wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;
    auto u32 = conv.from_bytes(utf8);

    int w = 0;
    for (char32_t ch : u32)
    w += max(0, ::wcwidth(static_cast<wchar_t>(ch)));
    return max(1, w);
}

View::View() {
    setlocale(LC_ALL, "");
    
    auto make_str_buf = [] {
        return vector<vector<string>>(
            GAME_WINDOW_HEIGHT, vector<string>(GAME_WINDOW_WIDTH, ""));
    };
    auto make_col_buf = [] {
        return vector<vector<Color>>(
            GAME_WINDOW_HEIGHT, vector<Color>(GAME_WINDOW_WIDTH, Color::NOCHANGE));
    };

    latest_map   = last_map   = make_str_buf();
    latest_fg_color = last_fg_color = make_col_buf();
    latest_bg_color = last_bg_color = make_col_buf();
    resetLatest();

}

void View::updateGameObject(GameObject* obj) {
    Icon icon = obj->getIcon();
        Position pos  = obj->getPosition();

        for (size_t dy = 0; dy < icon.size(); ++dy) {
            int row = pos.y() + static_cast<int>(dy);
            if (row < 0 || row >= GAME_WINDOW_HEIGHT) continue;

            for (size_t dx = 0; dx < icon[dy].size(); ++dx) {
                int col = pos.x() + static_cast<int>(dx);
                if (col < 0 || col >= GAME_WINDOW_WIDTH) continue;

                const Cell& cell = icon[dy][dx];
                latest_map      [row][col] = cell.ascii;
                latest_bg_color [row][col] = cell.color;
                latest_fg_color [row][col] = cell.color;
            }
        }

}

void View::render(){
    auto [rows, cols] = get_terminal_size();
    bool resized = (rows != _termHeight || cols != _termWidth);
    _termHeight = rows;
    _termWidth  = cols;

    if (resized) cout << "\033[2J\033[H";

    bool dirty = (   last_map      != latest_map
        || last_fg_color != latest_fg_color
        || last_bg_color != latest_bg_color);
    if (!dirty) return;

    string frame;
    frame.reserve((GAME_WINDOW_HEIGHT + 2) * (GAME_WINDOW_CELL_WIDTH * GAME_WINDOW_WIDTH + 3));


    // 上邊界
    frame += '+' + string(GAME_WINDOW_WIDTH * GAME_WINDOW_CELL_WIDTH, '-') + "+\n";

    for (int r = 0; r < GAME_WINDOW_HEIGHT; ++r) {
        int rowScreen = r + 2;

        // 左邊界
        frame += '|';

        int pixelCol = 1;

        for (int c = 0; c < GAME_WINDOW_WIDTH; ++c) {
            const string& txt = latest_map[r][c];
            const auto         fg  = latest_fg_color[r][c];
            const auto         bg  = latest_bg_color[r][c];

            int w        = max(1, displayWidth(txt));
            int padTotal = GAME_WINDOW_CELL_WIDTH - w;
            int padLeft  = padTotal / 2;
            int padRight = padTotal - padLeft;

            // 左空格
            for (int p = 0; p < padLeft; ++p) {
                frame += AnsiPrint(" ", Color::NOCHANGE, bg, false, false);
            }

            // 圖像
            frame += AnsiPrint(txt.c_str(), fg, bg, false, false);

            // 右空格
            for (int p = 0; p < padRight; ++p) {
                frame += AnsiPrint(" ", Color::NOCHANGE, bg, false, false);
            }

            pixelCol += GAME_WINDOW_CELL_WIDTH;
        }


        // 右邊界
        frame += "|\n";

    }
    // 下邊界
    frame += '+' + string(GAME_WINDOW_WIDTH * GAME_WINDOW_CELL_WIDTH, '-') + "+\n";

    cout << "\033[H" << frame << flush;


    // 更新緩衝區
    last_map      = latest_map;
    last_fg_color = latest_fg_color;
    last_bg_color = latest_bg_color;
}


void View::resetLatest(){
    for (int r = 0; r < GAME_WINDOW_HEIGHT; ++r) {
        fill(latest_map[r].begin(),   latest_map[r].end(),   " ");
        fill(latest_fg_color[r].begin(), latest_fg_color[r].end(), Color::NOCHANGE);
        fill(latest_bg_color[r].begin(), latest_bg_color[r].end(), Color::NOCHANGE);
    }
}

pair<int,int> View::get_terminal_size() {
    int rows, cols;
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        rows = w.ws_row;
        cols = w.ws_col;
    } else {
        rows = cols = -1; // 異常情況
    }
    return make_pair(rows, cols);
}

