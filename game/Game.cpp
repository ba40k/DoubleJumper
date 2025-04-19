//
// Created by radamir on 17.04.25.
//

#include "Game.h"

#include <iostream>


Game::Game() : physicsModel(0.0019), doubleJumper(doubleJumperSpawnX,doubleJumperSpawnY,defaultSpeed,startDirection){
    srand(time(NULL));
}
void Game::gameInitialize() {
    soundPrefixPath = "requirments/Doodle Jump SFX/";
    jumpSoundPath = "jump.wav";
    jumpSound.setSource(QUrl::fromLocalFile(soundPrefixPath + jumpSoundPath));
    int platformsCount = 3 + rand()%defaultPlatformSpawnCount;
    QString path = "game-tiles@2x.png";
    for(int i = 0; i < platformsCount; i++) {
        int coordinateX = rand()%SCREEN_WIDTH;
        int coordinateY = SCREEN_HEIGHT - PLATFORM_HEIGHT - rand()%50; // так как координата зранится как координата левого верхнего угла, сращу надо вытащить на экран, а уже потом немного случайно поднимать
        AbstractPlatform* platform = new GreenPlatform(coordinateX, coordinateY,path);
        platforms.push_back(platform);
    }
    AbstractPlatform* startPlatform = new GreenPlatform(260, SCREEN_HEIGHT- PLATFORM_HEIGHT,path);
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

    if (isIntersectAnyPLatfrom()) {
        jumpSound.play();
        doubleJumper.setSpeed(defaultSpeed);
    }

}
QVector<AbstractPlatform*>* Game::getPlatforms() {
    return &platforms;
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
    for (auto &platformPointer : platforms) {
        if (platformPointer->getY() <= doubleJumper.getCoordinateY() + doubleJumper.getHeight()&&
            platformPointer->getY() + platformPointer->getHeight() >= doubleJumper.getCoordinateY() + doubleJumper.getHeight()) {
            isIntersectVertically = true;
        }
        if (platformPointer->getX() <= doubleJumper.getCoordinateX() + doubleJumper.getWidth() &&
            platformPointer->getX() + platformPointer->getWidth() >= doubleJumper.getCoordinateX()) {
            isIntersectHorizontally = true;
        }
        if (!isIntersectVertically || !isIntersectHorizontally) { // обнуление, чтобы флаги не выставились по отдельности
            isIntersectVertically = false;
            isIntersectHorizontally = false;
        }
    }
    return (isIntersectVertically & isIntersectHorizontally);
}
