//
// Created by radamir on 17.04.25.
//

#include "Game.h"

#include <iostream>


Game::Game() : physicsModel(0.0019), doubleJumper(doubleJumperSpawnX,doubleJumperSpawnY,defaultSpeed,startDirection){
    srand(time(NULL));
}
void Game::gameInitialize() {
    lastDoubleJumperMinCoordinate = getMinDoubleJumperCoordinate();
    soundPrefixPath = "requirments/Doodle Jump SFX/";
    jumpSoundPath = "jump.wav";
    jumpSound.setSource(QUrl::fromLocalFile(soundPrefixPath + jumpSoundPath));
    int platformsCount = 3 + rand()%defaultPlatformSpawnCount;
    QString path = "game-tiles@2x.png";

    AbstractPlatform* startPlatform = new GreenPlatform(260, SCREEN_HEIGHT- PLATFORM_HEIGHT,path);
    std::deque<AbstractPlatform*> platforms;
    platforms.push_back(startPlatform);
    firstScreen = new Screen(0,850,platforms,1.0);
    platforms.push_back(startPlatform);

}
void Game::gameStateUpdate(int deltaTime, bool leftArrowPressed, bool rightArrowPressed) {





    long double deltaY = physicsModel.calculateDistace(deltaTime, doubleJumper.getSpeed());



    doubleJumper.setSpeed(physicsModel.calculateSpeed(deltaTime, doubleJumper.getSpeed(), doubleJumper.getDirection()));
    doubleJumper.setCoordinateY(doubleJumper.getCoordinateY() + doubleJumper.getDirection() * deltaY);
    if (leftArrowPressed) {
        doubleJumper.setCoordinateX(doubleJumper.getCoordinateX() - deltaTime * horizontalSpeed);
    } else if (rightArrowPressed) {
        doubleJumper.setCoordinateX(doubleJumper.getCoordinateX() + deltaTime * horizontalSpeed);
    }
    if (doubleJumper.getRightestHitboxPoint() < 0) {
        doubleJumper.setCoordinateX(SCREEN_WIDTH - 120);
    }
    if (doubleJumper.getLeftestHitboxPoint() > SCREEN_WIDTH ) {
        doubleJumper.setCoordinateX(0);
    }
    if (isIntersectAnyPLatfrom() && doubleJumper.getSpeed()<=0) { // делаем отскок только тогда, когда он паадет
        jumpSound.play();
        doubleJumper.setSpeed(defaultSpeed);
    }

    if (abs(minDoubleJumperCoordinate - firstScreen->getHighestPlatformCoordinate()) < 500) {
        difficulcyCoef*=0.99;
        firstScreen->setDifficulty(difficulcyCoef);
        firstScreen->generatePlatforms();
    }

    minDoubleJumperCoordinate = std::min(minDoubleJumperCoordinate, doubleJumper.getCoordinateY());




  //  firstScreen->deletePlatformsLowerThan(minDoubleJumperCoordinate,SCREEN_HEIGHT);
}
std::deque<AbstractPlatform*>* Game::getPlatforms() {
    return firstScreen->getPlatforms();
}
int Game::getDoubleJumperX() const {
    return doubleJumper.getCoordinateX();
}
int Game::getDoubleJumperY() const {
    return doubleJumper.getCoordinateY();
}
DoubleJumper* Game::getDoubleJumper() {
    return &doubleJumper;
}
bool Game::isIntersectAnyPLatfrom() {
    bool isIntersectVertically = false;
    bool isIntersectHorizontally = false;

    for (auto &platformPointer : *firstScreen->getPlatforms()) {
        if (platformPointer->getY() <= doubleJumper.getCoordinateY() + doubleJumper.getHeight()&&
            platformPointer->getY()  + platformPointer->getHeight() >= doubleJumper.getCoordinateY() + doubleJumper.getHeight()) {
            isIntersectVertically = true;
        }
        if (platformPointer->getX() <=doubleJumper.getRightestHitboxPoint() &&
            platformPointer->getX() + platformPointer->getWidth() >= doubleJumper.getLeftestHitboxPoint()) {
            isIntersectHorizontally = true;
        }
        if (!isIntersectVertically || !isIntersectHorizontally) { // обнуление, чтобы флаги не выставились по отдельности
            isIntersectVertically = false;
            isIntersectHorizontally = false;
        }
    }
    return (isIntersectVertically & isIntersectHorizontally);
}
int Game::getMinDoubleJumperCoordinate() {
    return minDoubleJumperCoordinate;
}
int Game::getShift() const {
    int shiftY = abs(lastDoubleJumperMinCoordinate - minDoubleJumperCoordinate);
    return shiftY;
}

