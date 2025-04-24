//
// Created by radamir on 24.04.25.
//

#include "BrownPLatform.h"

BrownPlatform::BrownPlatform(int coordinateX, int coordinateY, QString &imagePath) : AbstractPlatform(coordinateX, coordinateY,125) {
    this->imagePath = imagePath;
}
QLabel* BrownPlatform::getQLabel(QWidget *parent) const {
    QLabel* label = new QLabel(parent);
    label->setGeometry(coordinateX,coordinateY,WIDTH, HEIGHT);
    label->setScaledContents(true);
    label->setPixmap(QPixmap(prefixPath + imagePath).copy(0,145,WIDTH ,HEIGHT));
    return label;
}
void BrownPlatform::setBroken() {
    broken = true;
}
bool BrownPlatform::isBroken() {
    return broken;
}
