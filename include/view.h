#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <vector>
#include <string>
#include <utility>
#include "unit.h"
#include "gameObject.h"

using namespace std;

class View{
public:
    View();
    void render();
    void updateGameObject(GameObject*);
    void resetLatest();
private:
    int _termWidth;
    int _termHeight;
    vector<vector<string>> latest_map, last_map;
    vector<vector<Color>>       latest_fg_color, last_fg_color;
    vector<vector<Color>>       latest_bg_color, last_bg_color;
    static pair<int, int> get_terminal_size();
};

#endif
