#include "RPSGameObject.h"
#include "unit.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

// 確保只初始化一次隨機種子（可放 main() 內）
namespace {
    bool seeded = false;
    void seedRandom() {
        if (!seeded) {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            seeded = true;
        }
    }

    Direction getRandomDirection() {
        int dir = std::rand() % 4;
        return static_cast<Direction>(dir); // 假設 enum 是從 0~3 對應 UP, DOWN, LEFT, RIGHT
    }
}

bool RPSGameObject::intersect(ICollider *other) {
    RPSGameObject *otherRPS = dynamic_cast<RPSGameObject *>(other);
    if (!otherRPS) return false;
    return this->getX() == otherRPS->getX() && this->getY() == otherRPS->getY();
}

void RPSGameObject::onCollision(ICollider *other) {
    RPSGameObject *otherRPS = dynamic_cast<RPSGameObject *>(other);
    if (!otherRPS) return;

    if (_type == otherRPS->_type) return;

    if ((_type == ROCK && otherRPS->_type == SCISSORS) ||
        (_type == SCISSORS && otherRPS->_type == PAPER) ||
        (_type == PAPER && otherRPS->_type == ROCK)) {
        otherRPS->_type = _type;
    }
}

void RPSGameObject::update() {
    seedRandom();
    _dir = getRandomDirection();

    switch (_dir) {
    case UP:
        setY(getY() - 1);
        break;
    case DOWN:
        setY(getY() + 1);
        break;
    case LEFT:
        setX(getX() - 1);
        break;
    case RIGHT:
        setX(getX() + 1);
        break;
    case NONE:
        break;
    }
}

RPSType RPSGameObject::getType() const {
    return _type;
}

void RPSGameObject::setType(RPSType type) {
    _type = type;
}

void RPSGameObject::setDirection(Direction dir) {
    _dir = dir;
}