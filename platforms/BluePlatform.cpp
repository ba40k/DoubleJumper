//
// Created by radamir on 25.04.25.
//
#include "BluePlatform.h"

#include <iostream>
#include <QMediaPlayer>

BluePlatform::BluePlatform(int coordinateX, int coordinateY, QString &imagePath) : AbstractPlatform(coordinateX, coordinateY,soundsOn) {

}
void BluePlatform::changeSpeedDirection() {
    speed*=-1;
}
void BluePlatform::updateCoordinate(int deltaTime) {
    this->coordinateX += (double)speed*deltaTime;
}
QLabel *BluePlatform::getQLabel(QWidget *parent) {
    QLabel* label = new QLabel(parent);
    label->setGeometry(coordinateX,coordinateY,WIDTH, HEIGHT);
    label->setScaledContents(true);
    label->setPixmap(QPixmap(prefixPath + theme->getGameTileImagePath()).copy(0,35,WIDTH,HEIGHT));
    return label;
}
double BluePlatform::getSpeedDirection() {
    return speed;
}



