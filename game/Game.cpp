//
// Created by radamir on 17.04.25.
//

#include "Game.h"

#include <iostream>

#include "../items/helicopterHat.h"
#include "../items/Spring.h"
#include "../platforms/BluePlatform.h"


Game::Game() : physicsModel(0.0025), doubleJumper(doubleJumperSpawnX,doubleJumperSpawnY,defaultSpeed,startDirection){
    srand(time(NULL));
}
void Game::gameInitialize() {
    lastDoubleJumperMinCoordinate = getMinDoubleJumperCoordinate();
    soundPrefixPath = "requirments/Doodle Jump SFX/";
    jumpSoundPath = "jump.wav";
    jumpSound.setSource(QUrl::fromLocalFile(soundPrefixPath + jumpSoundPath));
    QString path = "game-tiles@2x.png";
    AbstractPlatform* startPlatform = new GreenPlatform(260, SCREEN_HEIGHT- PLATFORM_HEIGHT,path);
    std::deque<AbstractPlatform*> platforms;
    platforms.push_back(startPlatform);
    firstScreen = new Screen(0,850,platforms,1.0);
    platforms.push_back(startPlatform);
}
void Game::gameStateUpdate(int deltaTime, bool leftArrowPressed, bool rightArrowPressed) {
    moveBluePlatforms(deltaTime);
    processItemPickup();

    if (hatBuffTicks > 0) {
        hatBuffTicks--;
        doubleJumper.setSpeed(hatSpeedBuff);
        if (hatBuffTicks == 0) {
            delete currentHat;
            currentHat = nullptr;
        }
    }
    long double deltaY = physicsModel.calculateDistace(deltaTime, doubleJumper.getSpeed());
    if (hatBuffTicks == 0) {
        doubleJumper.setSpeed(physicsModel.calculateSpeed(deltaTime, doubleJumper.getSpeed(), doubleJumper.getDirection()));
    }
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
        difficulcyCoef*=0.9;
        firstScreen->setDifficulty(difficulcyCoef);
        firstScreen->generatePlatforms();
    }

    minDoubleJumperCoordinate = std::min(minDoubleJumperCoordinate, doubleJumper.getCoordinateY());
    bestScore = std::max(bestScore,(850 - doubleJumper.getCoordinateY())/5);
    firstScreen->deletePlatformsLowerThan(getShift());
    firstScreen->deleteItemsLowerThan(getShift());
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
        if (isIntersectVertically && isIntersectHorizontally && dynamic_cast<BrownPlatform*>(platformPointer) &&
            doubleJumper.getSpeed()<=0 && hatBuffTicks ==0) {
            dynamic_cast<BrownPlatform*>(platformPointer)->setBroken();
            return false;
        }
        if (isIntersectVertically && isIntersectHorizontally && !dynamic_cast<BrownPlatform*>(platformPointer)  && hatBuffTicks ==0) {
            return true;
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
void Game::moveBluePlatforms(int deltaTime) {
    for (auto &platfromPointer : *firstScreen->getPlatforms()) {
        if (dynamic_cast<BluePlatform*>(platfromPointer)) {
            dynamic_cast<BluePlatform*>(platfromPointer)->updateCoordinate(deltaTime);
            if (dynamic_cast<BluePlatform*>(platfromPointer)->getSpeedDirection() < 0 && platfromPointer->getX()<=0) {
                dynamic_cast<BluePlatform*>(platfromPointer)->changeSpeedDirection();
            }
            if (dynamic_cast<BluePlatform*>(platfromPointer)->getSpeedDirection()>0
                && platfromPointer->getX() + platfromPointer->getWidth()>=SCREEN_WIDTH) {
                dynamic_cast<BluePlatform*>(platfromPointer)->changeSpeedDirection();
            }
        }
    }
}
void Game::processItemPickup() {
    int index = 0;
    for (auto &itemPointer : *firstScreen->getItems()) {
        bool isIntersectVertically = false;
        bool isIntersectHorizontally = false;

        if (itemPointer->getCoordinateY() <= doubleJumper.getCoordinateY() + doubleJumper.getHeight()&&
           itemPointer->getCoordinateY()  + itemPointer->getHeight() >= doubleJumper.getCoordinateY() + doubleJumper.getHeight()) {
            isIntersectVertically = true;
           }
        if (itemPointer->getCoordinateX() <=doubleJumper.getRightestHitboxPoint() &&
            itemPointer->getCoordinateX() + itemPointer->getWidth() >= doubleJumper.getLeftestHitboxPoint()) {
            isIntersectHorizontally = true;
            }
        if (!isIntersectVertically || !isIntersectHorizontally) { // обнуление, чтобы флаги не выставились по отдельности
            isIntersectVertically = false;
            isIntersectHorizontally = false;
        }

        if (isIntersectVertically && isIntersectHorizontally && doubleJumper.getSpeed() <=0 && dynamic_cast<Spring*>(itemPointer)) {
            // активируем пружинку только если упали на неё
           // std::cout<<"deleted: "<<itemPointer->getPlatform()<<'\n';
            itemPointer->activate(doubleJumper);
            break;
        }
        if (isIntersectVertically && isIntersectHorizontally  && dynamic_cast<HelicopterHat*>(itemPointer) && hatBuffTicks<=0) {
            // активируем шляпу в любом случае касания - когда падали или когда взлетали
            itemPointer->activate(doubleJumper);
            hatBuffTicks = dynamic_cast<HelicopterHat*>(itemPointer)->getActivatedTicks();
            hatSpeedBuff = dynamic_cast<HelicopterHat*>(itemPointer)->getSpeedBuff();
            currentHat = itemPointer;
            firstScreen->getItems()->erase(firstScreen->getItems()->begin() + index);
            break;
        }
        index++;
    }
}

int Game::getScore() const {
    return bestScore;
}

std::deque<AbstractItem *> *Game::getItems() {
    return firstScreen->getItems();
}
AbstractItem *Game::getHatPointer() {
    return currentHat;
}
