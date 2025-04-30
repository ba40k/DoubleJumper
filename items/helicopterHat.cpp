//
// Created by radamir on 29.04.25.
//

#include "helicopterHat.h"
#include <iostream>
#include <QAudioOutput>
QMediaPlayer* HelicopterHat::player = nullptr;
QAudioOutput* HelicopterHat::audioOutput = nullptr;
bool HelicopterHat::isPlayerInitialized = false;
HelicopterHat::HelicopterHat(int coordinateX, AbstractPlatform* platform) : AbstractItem(coordinateX,35,21,platform) {
    onTileCoordinateX =  662;
    onTileCoordinateY =  470;
    width = 65;
    height = 39;
    shiftY = 3;
    if (!isPlayerInitialized) {
        player = new QMediaPlayer();
        audioOutput = new QAudioOutput();
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl::fromLocalFile(prefixSoundPath + activatedSoundPath));
        isPlayerInitialized = true;
    }
}
QLabel *HelicopterHat::getQLabel(QWidget *parent) {
    QLabel *label = new QLabel(parent);
    label->setScaledContents(true);
    label->setGeometry(getCoordinateX(),getCoordinateY(),width, height);
    label->setPixmap(QPixmap(prefixPath + imagePath).copy(onTileCoordinateX,onTileCoordinateY,width,height));
    return label;
}
void HelicopterHat::setActivated() {
    activated = true;
}
void HelicopterHat::activate(DoubleJumper &activator) {
    // std::cout<<1;
    jumper = &activator;
    setActivated();
    height-=5;
    player->play();
}
int HelicopterHat::getActivatedTicks() {
    return activatedTicks;
}
int HelicopterHat::getCoordinateX() {
    if (!activated) {
        return platform->getX() + coordinateX + 5;
    } else {

            return jumper->getCoordinateX() + 30;

    }
}
int HelicopterHat::getCoordinateY() {
    if (!activated) {
        return platform->getY()  - height + shiftY;
    } else {
        return jumper->getCoordinateY()  -shiftY - 8;
    }
}
double HelicopterHat::getSpeedBuff() {
    return speedBuff;
}