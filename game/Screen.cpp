//
// Created by radamir on 19.04.25.
//

#include "Screen.h"
#include <cmath>

#include "../PhysicsModel.h"

Screen::Screen(int lowerBound, int upperBound, QVector<AbstractPlatform*> &platforms, double difficultyLevel) {
    srand(time(NULL));
    this->lowerBound = lowerBound;
    this->upperBound = upperBound;
    this->platforms = platforms;
    this->difficultyLevel = difficultyLevel;
    generatePlatforms();
}
QVector<AbstractPlatform*>* Screen::getPlatforms() {
    return &platforms;
}
void Screen::generatePlatforms() {
    bool upperBoundAchieved = false;
    while (!upperBoundAchieved) {
        int shiftX = rand() % accesableDistanceX + WIDTH;
        int shiftY = rand() % accesableDistanceY;
        int shiftSign = 1;
        rand()%2==0?shiftSign=-1:1;
        int newX = PhysicsModel::getByModulo(platforms.back()->getX() + shiftSign*shiftX,WIDTH);
        int newY = platforms.back()->getY() - shiftY;
        if ( intersectPrevious(newX,newY)) {
            continue; // перегенерируем
        }

        if (outOfBoundY(newY)) {
            upperBoundAchieved = true;
            break;
        }

        AbstractPlatform* platform = new GreenPlatform(newX, newY,imagePath);
        platforms.push_back(platform);
    }
}
bool Screen::outOfBoundX(int x) {
    return !(x >=0 && x<=WIDTH);
}
bool Screen::outOfBoundY(int y) {
    return !(y >=0 && y<=HEIGHT - 32); // отнимаая 32 мы проверяем, что платформа не находится частично вне экрана
}
Screen::~Screen() {
    for (int i =0 ;i<platforms.size();i++) {
        delete platforms[i];
    }
}

bool Screen::intersectPrevious(int x,int y) {
    for (auto platform : platforms) {
        int x1 = x;
        int w = platform->getWidth();
        int x2 = platform->getX();
        bool notOverlapX = ((x1 + w < x2) || (x2 + w < x1));
        int y1 = y;
        int h = platform->getHeight();
        int y2 = platform->getY();
        bool notOverlapY = ((y1 + h < y2) || (y2 + h < y1));
        if (!(notOverlapX || notOverlapY)) {
            return true;
        }
    }
    return false;
}
