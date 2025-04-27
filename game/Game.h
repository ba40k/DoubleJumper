//
// Created by radamir on 17.04.25.
//

#ifndef GAME_H
#define GAME_H

#include "../platforms/GreenPlatform.h"
#include "../platforms/AbstractPlatform.h"
#include "../DoubleJumper.h"
#include "../PhysicsModel.h"

#include <QVector>
#include <QSoundEffect>
#include "Screen.h"
class Game {
    double difficulcyCoef = 1.0;
    const int doubleJumperSpawnX = 260;
    int minDoubleJumperCoordinate=400;
    int lastDoubleJumperMinCoordinate=850;
    const int doubleJumperSpawnY = 850 - 32 - 115;
    long double defaultSpeed = 1.5;
    int startDirection = -1;

    const int PLATFORM_HEIGHT = 32;

    int defaultPlatformSpawnCount = 5;
    PhysicsModel physicsModel;
    DoubleJumper doubleJumper;
    Screen* firstScreen;
    const int SCREEN_HEIGHT = 850;
    const int SCREEN_WIDTH = 640;
    QString soundPrefixPath;
    QString jumpSoundPath ;
    QSoundEffect jumpSound;
    float horizontalSpeed = 0.8;
    bool isIntersectAnyPLatfrom();
    void moveBluePlatforms(int deltaTime);
    int bestScore = 0;
    public:
    Game();
    int getScore() const;
    void gameInitialize();
    void gameStateUpdate(int deltaTime, bool leftArrowPressed, bool rightArrowPressed);
    int getDoubleJumperX() const;
    int getDoubleJumperY() const;
    DoubleJumper* getDoubleJumper();
    int getMinDoubleJumperCoordinate();
    std::deque<AbstractPlatform*>* getPlatforms();
    int getShift() const;
};



#endif //GAME_H
