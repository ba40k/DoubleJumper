//
// Created by radamir on 19.04.25.
//

#include "Screen.h"
#include <cmath>
#include <iostream>

#include "../PhysicsModel.h"
#include "../items/Spring.h"
#include "../platforms/BluePlatform.h"
#include "../items/helicopterHat.h"
#include "../items/Jetpack.h"
#include "../platforms/BlackHole.h"

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
    blackHoleSpawnProbability+= (1 - difficultyLevel) * 0.25;
   int count = 7;
    while (count--) {
        int numberOfAdditionalPlatforms = std::max(1.0,rand()%7 * difficultyLevel); // так как по логике(весьма странной) чем выше число сожности тем НИЖЕ сложность, то и количество спавнящихся платформ тоже уменшьается
        int parentPlatformIndex = platforms.size() - 1;
        while (dynamic_cast<BrownPlatform*>(platforms[parentPlatformIndex])) {
            parentPlatformIndex--;
        }
        AbstractPlatform *parentPlatform = platforms[parentPlatformIndex];

        for (int i = 0; i < numberOfAdditionalPlatforms; i++) {

            int shiftX = rand() % accesableDistanceX +100;
            int shiftY = rand() % accesableDistanceY + 40;
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
            } else if (rand()%100 < blackHoleSpawnProbability) {
                platform = new BlackHole(newX, newY, imagePath);
                i--; // черные дыры, ясное дело, не учитываем
            }
            else {
                platform = new GreenPlatform(newX, newY,imagePath);
            }



            if ( intersectPrevious(newX,newY, dynamic_cast<BluePlatform*>(platform))) {
                delete platform;
                continue; // перегенерируем
            }
            if (rand()%100 < springSpawnProbability && !dynamic_cast<BrownPlatform*>(platform)
                && !dynamic_cast<BlackHole*>(platform)) {
                Spring temp(0,0);
                int springWidth = temp.getWidth();
                int onPlatformX =rand()%(platform->getWidth() - springWidth);
                onPlatformX = std::max(8,onPlatformX);
                onPlatformX = std::min(platform->getWidth() - springWidth - 8,onPlatformX);
                AbstractItem *spring = new Spring(onPlatformX,platform);
                items.push_back(spring);
            } else if (rand()%100 < helicopterHatSpawnProbability && !dynamic_cast<BrownPlatform*>(platform)
                && !dynamic_cast<BlackHole*>(platform)) {

                HelicopterHat temp(0,0);
                int hatWidth = temp.getWidth();
                int onPlatformX =rand()%(platform->getWidth() - hatWidth);
                onPlatformX = std::max(8,onPlatformX);
                onPlatformX = std::min(platform->getWidth() - hatWidth - 8,onPlatformX);
                AbstractItem *hat = new HelicopterHat(onPlatformX,platform);
                items.push_back(hat);

            } else if (rand()%100 < jetpackSpawnProbability && !dynamic_cast<BrownPlatform*>(platform)
                && !dynamic_cast<BlackHole*>(platform)) {
                Jetpack temp(0,0);
                int jetpackWidth = temp.getWidth();
                int onPlatformX =rand()%(platform->getWidth() - jetpackWidth);
                onPlatformX = std::max(8,onPlatformX);
                onPlatformX = std::min(platform->getWidth() - jetpackWidth - 8,onPlatformX);
                AbstractItem *jetpack = new Jetpack(onPlatformX,platform);
                items.push_back(jetpack);
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
    for (int i =0;i<items.size();i++) {
        delete items[i];
    }
}

bool Screen::intersectPrevious(int x,int y, bool isBlue) {
    for (auto &platform : platforms) {
        int x1 = x;
        int w = platform->getWidth();
        int x2 = platform->getX();
        int y1 = y;
        int h = platform->getHeight() + 50;
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
    while (platforms[index]->getY() + shift > 1000) { //  удаляем платформы не сразу как только они вышли за экран, чтобы не было так, что платформа удалилась, но осталась пружинка привязанная к ней
       // std::cout<<platforms[index]<<'\n';
        delete platforms[index];
        platforms[index] = nullptr;
        platforms.pop_front();
    }

}
void Screen::deleteItemsLowerThan(int shift) {
    int index = 0;
    while (index<items.size() && (items[index]->getCoordinateY() + shift > 850 || items[index]->getPlatform()==nullptr)) {
       // std::cout<<"deleted "<<dynamic_cast<HelicopterHat*>(items[index]);
        delete items[index];
        items[index] = nullptr;
        items.pop_front();
    }
}

std::deque<AbstractItem *> *Screen::getItems() {
    return &items;
}

