//
// Created by radamir on 19.04.25.
//

#ifndef SCREEN_H
#define SCREEN_H

#include "../platforms/GreenPlatform.h"
#include <deque>

#include "../items/AbstractItem.h"
#include "../platforms/BrownPLatform.h"
class Screen {
    QString imagePath = "game-tile@2x.png";
    const int HEIGHT = 850;
    const int WIDTH = 640-120;
    const int accesableDistanceX  = 200;
    const int accesableDistanceY  = 280;
    const int brownPlatformSpawnProbability = 15;
    double bluePlatformSpawnProbability = 1.0;
    const int springSpawnProbability = 10;
    const int helicopterHatSpawnProbability = 3;


    int lowerBound;
    double difficultyLevel;
    std::deque<AbstractPlatform*> platforms;
    std::deque<AbstractItem*> items;

    bool outOfBoundX(int x);
    bool outOfBoundY(int y);

    bool intersectPrevious(int x,int y, bool isBlue);

    public:
    Screen(int lowerBound, int upperBound, std::deque<AbstractPlatform*> &platforms, double difficultyLevel);
    std::deque<AbstractPlatform*>* getPlatforms();
    std::deque<AbstractItem*>* getItems();
    int getHighestPlatformCoordinate() const;
    void setDifficulty(double dif);
    void generatePlatforms();
    void deletePlatformsLowerThan(int shift);
    void deleteItemsLowerThan(int shift);
    ~Screen();
};



#endif //SCREEN_H
