//
// Created by radamir on 15.04.25.
//

#include "DoubleJumper.h"

DoubleJumper::DoubleJumper(int coordinateX, int coordinateY, long double speed, long double direction) {
    this->coordinateX = coordinateX;
    this->coordinateY = coordinateY;
    this->speed = speed;
    this->direction = direction;
    prefixPath = "requirments/Sprites/Doodle Jump/";
    leftOrientedSpritePath = "lik-left@2x.png";
    rightOrientedSpritePath = "lik-right@2x.png";
}
long double DoubleJumper::getDirection() const {
    return direction;
}
long double DoubleJumper::getSpeed() const {
    return speed;
}
int DoubleJumper::getCoordinateX() const {
    return coordinateX;
}
int DoubleJumper::getCoordinateY() const {
    return coordinateY;
}
void DoubleJumper::setCoordinateX(int coordinateX) {
    this->coordinateX = coordinateX;
}
void DoubleJumper::setCoordinateY(int coordinateY) {
    this->coordinateY = coordinateY;
}
void DoubleJumper::setSpeed(long double speed) {
    this->speed = speed;
}
void DoubleJumper::changeDirection() {
    direction*=-1;
}
QLabel *DoubleJumper::getLeftOrientedLabel(QWidget *parent) {
    QLabel *label = new QLabel(parent);
    label->setGeometry(coordinateX,coordinateY,WIDTH,HEIGHT);
    label->setScaledContents(true);
    label->setPixmap(QPixmap(prefixPath + leftOrientedSpritePath));

    return label;
}
QLabel *DoubleJumper::getRightOrientedLabel(QWidget *parent) {
    QLabel *label = new QLabel(parent);
    label->setGeometry(coordinateX,coordinateY,WIDTH,HEIGHT);
    label->setPixmap(QPixmap(prefixPath + rightOrientedSpritePath));
    label->setScaledContents(true);
    return label;
}
int DoubleJumper::getHeight() const {
    return HEIGHT;
}
int DoubleJumper::getWidth() const {
    return WIDTH;
}
int DoubleJumper::getHitboxWidth() const {
    return hitBoxWidth;
}

