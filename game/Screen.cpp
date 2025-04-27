//
// Created by radamir on 19.04.25.
//

#include "Screen.h"
#include <cmath>
#include <iostream>

#include "../PhysicsModel.h"
#include "../platforms/BluePlatform.h"

Screen::Screen(int lowerBound, int upperBound, std::deque<AbstractPlatform*> &platforms, double difficultyLevel) {
    srand(time(NULL));
    this->lowerBound = lowerBound;
    this->platforms = platforms;
    this->difficultyLevel = difficultyLevel;
    generatePlatforms();
}
std::deque<AbstractPlatform*>* Screen::getPlatforms() {
    return &platforms;
}
void Screen::generatePlatforms() {
    bluePlatformSpawnProbability += (1 - difficultyLevel) * 0.25;
   int count = 5;
    while (count--) {
        int numberOfAdditionalPlatforms = std::max(1.0,rand()%5 * difficultyLevel); // так как по логике(весьма странной) чем выше число сожности тем НИЖЕ сложность, то и количество спавнящихся платформ тоже уменшьается
        int parentPlatformIndex = platforms.size() - 1;
        while (dynamic_cast<BrownPlatform*>(platforms[parentPlatformIndex])) {
            parentPlatformIndex--;
        }
        AbstractPlatform *parentPlatform = platforms[parentPlatformIndex];
        for (int i = 0; i < numberOfAdditionalPlatforms; i++) {
            int shiftX = rand() % accesableDistanceX +50;
            int shiftY = rand() % accesableDistanceY + 50;
            shiftY = std::min(accesableDistanceY, static_cast<int>(shiftY + (1.0 - difficultyLevel)*50)); // чем выше сложность тем большее число будет тут добавляться
            int shiftSign = 1;
            rand()%2==0?shiftSign=-1:1;
            int newX = PhysicsModel::getByModulo(platforms.back()->getX() + shiftSign*shiftX,WIDTH);
            int newY = parentPlatform->getY() - shiftY;

            AbstractPlatform* platform;
            if (rand()%100 < bluePlatformSpawnProbability) {
                platform = new BluePlatform(newX,newY,imagePath);

            } else if (rand()%100 < brownPlatformSpawnProbability) {
                platform = new BrownPlatform(newX, newY,imagePath);
                i--; // коричневые плафтормы не учитываем при генерации
            } else {
                platform = new GreenPlatform(newX, newY,imagePath);
            }
            if ( intersectPrevious(newX,newY, dynamic_cast<BluePlatform*>(platform))) {
                delete platform;
                continue; // перегенерируем
            }
            platforms.push_back(platform);
        }
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

bool Screen::intersectPrevious(int x,int y, bool isBlue) {
    for (auto &platform : platforms) {
        int x1 = x;
        int w = platform->getWidth();
        int x2 = platform->getX();
        int y1 = y;
        int h = platform->getHeight();
        int y2 = platform->getY();
        if (dynamic_cast<BluePlatform*>(platform) ||isBlue) {
            w = WIDTH;
        }
        bool notOverlapX = ((x1 + w < x2) || (x2 + w < x1));
        bool notOverlapY = ((y1 + h < y2) || (y2 + h < y1));
        if (!(notOverlapX || notOverlapY)) {
            return true;
        }
    }
    return false;
}
int Screen::getHighestPlatformCoordinate() const {
    return platforms.back()->getY();
}
void Screen::setDifficulty(double dif) {
    difficultyLevel = dif;
}
void Screen::deletePlatformsLowerThan(int shift) {
    int index = 0;
    while (platforms[index]->getY() + shift > 850) {
        delete platforms[index];
        platforms.pop_front();
    }
}


