//
// Created by radamir on 29.04.25.
//

#include "AbstractItem.h"


AbstractItem::AbstractItem(int coordinateX, int width, int height, AbstractPlatform* platform, bool soundsOn) {
    this->coordinateX = coordinateX;
    this->width = width;
    this->height = height;
    this->platform = platform;
    this->soundsOn = soundsOn;
}
int AbstractItem::getCoordinateX() {
    return platform->getX() + coordinateX;
}
int AbstractItem::getCoordinateY() {
    return platform->getY()  - height + shiftY;
}
int AbstractItem::getWidth() {
    return width;
}
int AbstractItem::getHeight() {
    return height;
}


AbstractPlatform* AbstractItem::getPlatform() {
    return platform;
}