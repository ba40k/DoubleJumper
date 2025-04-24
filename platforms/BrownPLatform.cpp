//
// Created by radamir on 24.04.25.
//

#include "BrownPLatform.h"

BrownPlatform::BrownPlatform(int coordinateX, int coordinateY, QString &imagePath) : AbstractPlatform(coordinateX, coordinateY,125) {
    this->imagePath = imagePath;
}
QLabel* BrownPlatform::getQLabel(QWidget *parent)  {
    QLabel* label = new QLabel(parent);
    label->setGeometry(coordinateX,coordinateY,WIDTH, HEIGHT);
    label->setScaledContents(true);
    if (animationCounter==0 ) {
        label->setPixmap(QPixmap(prefixPath + imagePath).copy(0,145,WIDTH ,HEIGHT));
    }
    if (animationCounter==1 && broken) {
         label->setPixmap(QPixmap(prefixPath + imagePath).copy(0,182,WIDTH ,38));
    }
    if (animationCounter==2 && broken) {
         label->setPixmap(QPixmap(prefixPath + imagePath).copy(0,232,WIDTH ,57));
    }
    animationCounter++;
    if (animationCounter == 3) animationEnded = true;
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