//
// Created by radamir on 16.04.25.
//

#include "AbstractPlatform.h"

AbstractPlatform::AbstractPlatform(const int coordinateX, const int coordinateY, bool soundsOn) {
    this->soundsOn = soundsOn;
    this->coordinateX = coordinateX;
    this->coordinateY = coordinateY;
    prefixPath = "requirments/Sprites/Doodle Jump/";
}
AbstractPlatform::AbstractPlatform(const int coordinateX, const int coordinateY, const int width, bool soundsOn) : WIDTH(width) {
    this->coordinateX = coordinateX;
    this->coordinateY = coordinateY;
    this->soundsOn = soundsOn;
    prefixPath = "requirments/Sprites/Doodle Jump/";
}

AbstractPlatform::AbstractPlatform(const int coordinateX, const int coordinateY, const int width, const int height, bool soundsOn) : WIDTH(width),HEIGHT(height) {
    this->coordinateX = coordinateX;
    this->coordinateY = coordinateY;
    this->soundsOn = soundsOn;
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
void AbstractPlatform::setTheme(Theme *theme) {
    this->theme = theme;
}
