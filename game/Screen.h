//
// Created by radamir on 19.04.25.
//

#ifndef SCREEN_H
#define SCREEN_H

#include "../platforms/GreenPlatform.h"
#include <QVector>
class Screen {
    QString imagePath = "game-tile@2x.png";
    const int HEIGHT = 850;
    const int WIDTH = 640-120;
    const int accesableDistanceX  = 200;
    const int accesableDistanceY  = 200;
    int lowerBound;
    int upperBound;
    double difficultyLevel;
    QVector<AbstractPlatform*> platforms;
    bool outOfBoundX(int x);
    bool outOfBoundY(int y);
    void generatePlatforms();
    bool intersectPrevious(int x,int y);

public:
    public:
    Screen(int lowerBound, int upperBound, QVector<AbstractPlatform*> &platforms, double difficultyLevel);
    QVector<AbstractPlatform*>* getPlatforms();
    ~Screen();
};



#endif //SCREEN_H
