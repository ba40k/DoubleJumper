//
// Created by radamir on 19.04.25.
//

#ifndef SCREEN_H
#define SCREEN_H

#include "../platforms/GreenPlatform.h""
#include <QVector>
class Screen {
    const int HEIGHT = 850;
    const int WIDTH = 640;
    double accesableDistance  = 150;
    int lowerBound;
    int upperBound;
    double difficultyLevel;
    QVector<AbstractPlatform*> platforms;
    void generatePlatforms();
public:
    public:
    Screen(int lowerBound, int upperBound, QVector<AbstractPlatform*> &platforms, double difficultyLevel);
    QVector<AbstractPlatform*>* getPlatforms();
    ~Screen();
};



#endif //SCREEN_H
