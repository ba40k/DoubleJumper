//
// Created by radamir on 17.04.25.
//

#include "Game.h"

#include <iostream>

#include "../items/helicopterHat.h"
#include "../items/Jetpack.h"
#include "../items/Spring.h"
#include "../platforms/BlackHole.h"
#include "../platforms/BluePlatform.h"


Game::Game() : physicsModel(0.003), doubleJumper(doubleJumperSpawnX,doubleJumperSpawnY,defaultSpeed,startDirection){
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
    processHopped();

    if (hatBuffTicks > 0) {
        hatBuffTicks--;
        doubleJumper.setSpeed(hatSpeedBuff);
        if (hatBuffTicks == 0) {
            delete currentHat;
            currentHat = nullptr;
        }
    }
    if (jetPackBuffTicks > 0) {
        jetPackBuffTicks--;
        doubleJumper.setSpeed(jetpackSpeedBuff);
        if (jetPackBuffTicks == 0) {
            delete currentJetpack;
            currentJetpack = nullptr;
        }
    }
    long double deltaY = physicsModel.calculateDistace(deltaTime, doubleJumper.getSpeed());
    if (hatBuffTicks == 0 && jetPackBuffTicks == 0) {
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
        difficulcyCoef*=0.95;
        firstScreen->setDifficulty(difficulcyCoef);
        firstScreen->generatePlatforms();
    }

    minDoubleJumperCoordinate = std::min(minDoubleJumperCoordinate, doubleJumper.getCoordinateY());
    bestScore = std::max(bestScore,(850 - doubleJumper.getCoordinateY())/3);
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
            platformPointer->getY()  + platformPointer->getHeight() >= doubleJumper.getCoordinateY() + doubleJumper.getHeight()
            && platformPointer->getY() + getShift()<=850) {
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
            doubleJumper.getSpeed()<=0 && hatBuffTicks ==0 && jetPackBuffTicks == 0) {
            dynamic_cast<BrownPlatform*>(platformPointer)->setBroken();
            return false;
        }
        if (dynamic_cast<BlackHole*>(platformPointer) && processBlackHoleInterSection(platformPointer)) {
            return false;
        }
        if (isIntersectVertically && isIntersectHorizontally && !dynamic_cast<BrownPlatform*>(platformPointer)  && hatBuffTicks ==0
            && jetPackBuffTicks == 0 && !dynamic_cast<BlackHole*>(platformPointer)) {
            return true;
        }
        isIntersectHorizontally = false;
        isIntersectVertically = false;
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
           itemPointer->getCoordinateY()  + itemPointer->getHeight() >= doubleJumper.getCoordinateY() + doubleJumper.getHeight()
           && dynamic_cast<Spring*>(itemPointer)
           ) {
            isIntersectVertically = true;
           }
        if (itemPointer->getCoordinateY() <= doubleJumper.getCoordinateY() + doubleJumper.getHeight()&&
           itemPointer->getCoordinateY()  + itemPointer->getHeight() >= doubleJumper.getCoordinateY()
           && dynamic_cast<HelicopterHat*>(itemPointer)
           ) {
            isIntersectVertically = true;
           }

        if (itemPointer->getCoordinateY() <= doubleJumper.getCoordinateY() + doubleJumper.getHeight()&&
          itemPointer->getCoordinateY()  + itemPointer->getHeight() >= doubleJumper.getCoordinateY()
          && dynamic_cast<Jetpack*>(itemPointer)
          ) {
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

        if (isIntersectVertically && isIntersectHorizontally  && dynamic_cast<HelicopterHat*>(itemPointer) && hatBuffTicks<=0 && jetPackBuffTicks<=0) {
            // активируем шляпу в любом случае касания - когда падали или когда взлетали
            itemPointer->activate(doubleJumper);
            hatBuffTicks = dynamic_cast<HelicopterHat*>(itemPointer)->getActivatedTicks();
            hatSpeedBuff = dynamic_cast<HelicopterHat*>(itemPointer)->getSpeedBuff();
            currentHat = itemPointer;
            firstScreen->getItems()->erase(firstScreen->getItems()->begin() + index);
            break;
        }
        if (isIntersectVertically && isIntersectHorizontally  && dynamic_cast<Jetpack*>(itemPointer) && hatBuffTicks<=0 && jetPackBuffTicks<=0) {
            // активируем джетпак в любом случае касания - когда падали или когда взлетали
            itemPointer->activate(doubleJumper);
            jetPackBuffTicks = dynamic_cast<Jetpack*>(itemPointer)->getActivatedTicks();
            jetpackSpeedBuff = dynamic_cast<Jetpack*>(itemPointer)->getSpeedBuff();
            currentJetpack = itemPointer;
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
AbstractItem *Game::getJetpackPointer() {
    return currentJetpack;
}

void Game::processHopped() {
    if ( doubleJumper.getSpeed()>=defaultSpeed - 0.2 ) {
        doubleJumper.setHopped(true);
    } else {
        doubleJumper.setHopped(false);
    }
}

bool Game::isGameEnded() {
    return gameEnded;
}
bool Game::processBlackHoleInterSection(AbstractPlatform *platform) {
    int x1 = doubleJumper.getCoordinateX();
    int y1 = doubleJumper.getCoordinateY();
    int width1 = doubleJumper.getWidth();
    int height1 = doubleJumper.getHeight();
    int x2 = platform->getX();
    int y2 = platform->getY();
    int width2 = platform->getWidth();
    int height2 = platform->getHeight();
    int left1 = x1;
    int right1 = x1 + width1;
    int left2 = x2;
    int right2 = x2 + width2;
    bool overlapX = (left1 < right2) && (right1 > left2);
    int top1 = y1;
    int bottom1 = y1 + height1;
    int top2 = y2;
    int bottom2 = y2 + height2;
    bool overlapY = (top1 < bottom2) && (bottom1 > top2);
    if (overlapX && overlapY) {
        finalBlackHole = platform;
        gameEnded = true;
    }
    return overlapX && overlapY;
}
AbstractPlatform *Game::getFinalBlackHole() {
    return finalBlackHole;
}

