//
// Created by radamir on 17.04.25.
//

#include "Game.h"

#include <iostream>

Game::Game() : physicsModel(0.0019), doubleJumper(260,850 - 32 - 115,1.0,-1){
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
        int coordinateY = SCREEN_HEIGHT - 32 - rand()%50;

        AbstractPlatform* platform = new GreenPlatform(coordinateX, coordinateY,path);
        platforms.push_back(platform);
    }
    AbstractPlatform* startPlatform = new GreenPlatform(260, SCREEN_HEIGHT- 32,path);
    platforms.push_back(startPlatform);

}
void Game::gameStateUpdate(int deltaTime, bool leftArrowPressed, bool rightArrowPressed) {
    long double deltaY = physicsModel.calculateDistace(deltaTime, doubleJumper.getSpeed());
    doubleJumper.setSpeed(physicsModel.calculateSpeed(deltaTime, doubleJumper.getSpeed(), doubleJumper.getDirection()));
    doubleJumper.setCoordinateY(doubleJumper.getCoordinateY() + doubleJumper.getDirection() * deltaY);
   // std::cout<<doubleJumper.getCoordinateY()<<std::endl;
    if (leftArrowPressed) {
        doubleJumper.setCoordinateX(doubleJumper.getCoordinateX() - deltaTime * horizontalSpeed);
    } else if (rightArrowPressed) {
        doubleJumper.setCoordinateX(doubleJumper.getCoordinateX() + deltaTime * horizontalSpeed);
    }
    for (auto &platformPointer : platforms) {
        if ((platformPointer->getY() <= doubleJumper.getCoordinateY() + doubleJumper.getHeight()
            && doubleJumper.getCoordinateY()+doubleJumper.getHeight() >= platformPointer->getY() + platformPointer->getHeight())
            && (platformPointer->getX()<=doubleJumper.getCoordinateX() + doubleJumper.getHitboxWidth() &&
                platformPointer->getX() + platformPointer->getWidth() >= doubleJumper.getCoordinateX() )){

            jumpSound.play();
            doubleJumper.setSpeed(1.0);
            break;
        }
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
