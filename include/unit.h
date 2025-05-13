#ifndef UNIT_H
#define UNIT_H

typedef struct {
    int e1;
    int e2;

    // 回傳的參數類型是 int ，而當此參數一被回傳後，
    // 其將會傳參考到 x()，因此 x() 即為此參數的參考
    int &x() { return e1; } 
    int &y() { return e2; }
    int &width() { return e1; }
    int &height() { return e2; }

} Position;

enum Color {BLACK = 0, RED = 1, GREEN = 2, YELLOW = 3, BLUE = 4, 
            PINK = 5, CYAN = 6, WHITE = 7, NOCHANGE = 8};

#endif
