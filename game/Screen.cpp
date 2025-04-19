//
// Created by radamir on 19.04.25.
//

#include "Screen.h"

Screen::Screen(int lowerBound, int upperBound, QVector<AbstractPlatform*> &platforms, double difficultyLevel) {
    this->lowerBound = lowerBound;
    this->upperBound = upperBound;
    this->platforms = platforms;
    this->difficultyLevel = difficultyLevel;
}
QVector<AbstractPlatform*>* Screen::getPlatforms() {
    return &platforms;
}
Screen::~Screen() {
    for (int i =0 ;i<platforms.size();i++) {
        delete platforms[i];
    }
}
