//
// Created by radamir on 16.04.25.
//

#include "GreenPlatform.h"

GreenPlatform::GreenPlatform(int coordinateX, int coordinateY, QString &imagePath) : AbstractPlatform(coordinateX, coordinateY) {
    this->imagePath = imagePath;
}
QLabel* GreenPlatform::getQLabel(QWidget *parent) const {
    QLabel* label = new QLabel(parent);
    label->resize(WIDTH, HEIGHT);
    label->setScaledContents(true);
    label->setPixmap(QPixmap(prefixPath + imagePath).copy(0,0,WIDTH,HEIGHT));
    return label;
}
