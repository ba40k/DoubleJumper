//
// Created by radamir on 24.04.25.
//

#include "BrownPLatform.h"
#include <iostream>
QMediaPlayer* BrownPlatform::player = nullptr;
QAudioOutput* BrownPlatform::audioOutput = nullptr;
bool BrownPlatform::isPlayerInitialized = false;
BrownPlatform::BrownPlatform(int coordinateX, int coordinateY, QString &imagePath) : AbstractPlatform(coordinateX, coordinateY,125) {
    this->imagePath = imagePath;
    if (!isPlayerInitialized) {
        player = new QMediaPlayer();
        audioOutput = new QAudioOutput();
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl::fromLocalFile(soundPrefixPath + breakingSoundPath));
        isPlayerInitialized = true;
    }

}
QLabel* BrownPlatform::getQLabel(QWidget *parent)  {
    QLabel* label = new QLabel(parent);
    label->setGeometry(coordinateX,coordinateY,WIDTH, HEIGHT);
    label->setScaledContents(true);

    if (!broken) {
        label->setPixmap(QPixmap(prefixPath + imagePath).copy(0,145,WIDTH ,HEIGHT));
    }
    if (animationCounter<=1 && broken) {
        player->play();
         label->setPixmap(QPixmap(prefixPath + imagePath).copy(0,182,WIDTH ,38));
        animationCounter++;
    }
    if (animationCounter>=2 && animationCounter<=12 && broken) {
         label->setPixmap(QPixmap(prefixPath + imagePath).copy(0,232,WIDTH ,70));
        animationCounter++;
    }
    if (animationCounter>=4 && animationCounter<=24 && broken) {
        label->setPixmap(QPixmap(prefixPath + imagePath).copy(0,297,WIDTH ,70));
        animationCounter++;
    }

    if (animationCounter == 24) {
        animationEnded = true;
    }
    return label;
}
void BrownPlatform::setBroken() {
    broken = true;
}
bool BrownPlatform::isBroken() {
    return broken;
}
bool BrownPlatform::isAnimationEnded() {
    return animationEnded;
}
void BrownPlatform::setAnimationCounter(int counter) {
    animationCounter = counter;
    if (animationCounter == 24) {
        animationEnded = true;
    }
}
int BrownPlatform::getAnimationCounter() {
    return animationCounter;
}


