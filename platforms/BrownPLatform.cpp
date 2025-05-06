//
// Created by radamir on 24.04.25.
//

#include "BrownPLatform.h"
#include <iostream>
QMediaPlayer* BrownPlatform::player = nullptr;
QAudioOutput* BrownPlatform::audioOutput = nullptr;
bool BrownPlatform::isPlayerInitialized = false;
BrownPlatform::BrownPlatform(int coordinateX, int coordinateY, QString &imagePath,bool soundsOn) : AbstractPlatform(coordinateX, coordinateY,125,soundsOn) {
    this->imagePath = imagePath;
    if (!isPlayerInitialized) {
        player = new QMediaPlayer();
        audioOutput = new QAudioOutput();
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl::fromLocalFile(soundPrefixPath + breakingSoundPath));
        isPlayerInitialized = true;
    }
    spritesBoundingsRects = {{0,144,127,34},{0,183,131,40},{0,233,121,60},{0,295,130,68}};
}
QLabel* BrownPlatform::getQLabel(QWidget *parent)  {
  //  std::cout<<animationCounter<<'\n';
    QLabel* label = new QLabel(parent);

    label->setScaledContents(true);

    if (!broken) {
        label->setGeometry(coordinateX,coordinateY,spritesBoundingsRects[0].width(), spritesBoundingsRects[0].height());
        label->setPixmap(QPixmap(prefixPath + imagePath).copy(spritesBoundingsRects[0]));
    }
   else {
       if (animationCounter<7) {
           label->setGeometry(coordinateX,coordinateY,spritesBoundingsRects[1].width(), spritesBoundingsRects[1].height());
           label->setPixmap(QPixmap(prefixPath + imagePath).copy(spritesBoundingsRects[1]));
       }
       else if (animationCounter>7& animationCounter<9) {
           label->setGeometry(coordinateX,coordinateY,spritesBoundingsRects[2].width(), spritesBoundingsRects[2].height());
           label->setPixmap(QPixmap(prefixPath + imagePath).copy(spritesBoundingsRects[2]));
       }
       else if (animationCounter>9) {
           label->setGeometry(coordinateX,coordinateY,spritesBoundingsRects[3].width(), spritesBoundingsRects[3].height());
           label->setPixmap(QPixmap(prefixPath + imagePath).copy(spritesBoundingsRects[3]));
       }

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
    if (!broken) {
        animationCounter = 0;
        return ;
    }
    if (broken && animationCounter == 1 && soundsOn) {
        player->play();
    }
    if (animationCounter> 9 && broken) {
        coordinateY+=3;
    }
}
int BrownPlatform::getAnimationCounter() {
    return animationCounter;
}


