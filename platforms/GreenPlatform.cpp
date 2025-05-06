//
// Created by radamir on 16.04.25.
//

#include "GreenPlatform.h"

GreenPlatform::GreenPlatform(int coordinateX, int coordinateY, QString &imagePath, bool soundsOn) : AbstractPlatform(coordinateX, coordinateY,soundsOn) {
    this->imagePath = imagePath;
}
QLabel* GreenPlatform::getQLabel(QWidget *parent)  {
    QLabel* label = new QLabel(parent);
    label->setGeometry(coordinateX,coordinateY,WIDTH, HEIGHT);
    label->setScaledContents(true);
    label->setPixmap(QPixmap(prefixPath + imagePath).copy(0,0,WIDTH,HEIGHT));
    return label;
}
