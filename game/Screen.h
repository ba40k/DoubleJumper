//
// Created by radamir on 19.04.25.
//

#ifndef SCREEN_H
#define SCREEN_H

#include "../platforms/GreenPlatform.h"
#include <deque>
class Screen {
    QString imagePath = "game-tile@2x.png";
    const int HEIGHT = 850;
    const int WIDTH = 640-120;
    const int accesableDistanceX  = 200;
    const int accesableDistanceY  = 200;
    int lowerBound;
    double difficultyLevel;
    std::deque<AbstractPlatform*> platforms;
    bool outOfBoundX(int x);
    bool outOfBoundY(int y);

    bool intersectPrevious(int x,int y);

public:
    public:
    Screen(int lowerBound, int upperBound, std::deque<AbstractPlatform*> &platforms, double difficultyLevel);
    std::deque<AbstractPlatform*>* getPlatforms();
    int getHighestPlatformCoordinate() const;
    void setDifficulty(double dif);
    void generatePlatforms();
    void deletePlatformsLowerThan(int shift);
    ~Screen();
};



#endif //SCREEN_H
