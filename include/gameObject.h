#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <vector>
#include "unit.h"
#include "icon.h"

using namespace std;

class GameObject {
protected:
    Position _pos;
    Icon _icon;

public:
    Position getPosition() const;
    Icon getIcon() const;
    virtual void update(int x, int y) = 0;
};

#endif
