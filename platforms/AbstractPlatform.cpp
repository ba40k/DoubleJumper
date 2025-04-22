//
// Created by radamir on 16.04.25.
//

#include "AbstractPlatform.h"

AbstractPlatform::AbstractPlatform(const int coordinateX, const int coordinateY) {
    this->coordinateX = coordinateX;
    this->coordinateY = coordinateY;
    prefixPath = "requirments/Sprites/Doodle Jump/";
}
int AbstractPlatform::getX() const {
    return coordinateX;
}
int AbstractPlatform::getY() const {
    return coordinateY;
}
int AbstractPlatform::getHeight() const {
    return HEIGHT;
}
int AbstractPlatform::getWidth() const {
    return WIDTH;
}
void AbstractPlatform::setY(int y) {
    this->coordinateY = y;
}
