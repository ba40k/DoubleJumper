//
// Created by radamir on 29.04.25.
//

#include "Spring.h"
#include <iostream>
#include <QAudioOutput>
QMediaPlayer* Spring::player = nullptr;
QAudioOutput* Spring::audioOutput = nullptr;
bool Spring::isPlayerInitialized = false;
Spring::Spring(int coordinateX, AbstractPlatform* platform, bool soundsOn) : AbstractItem(coordinateX,35,21,platform, soundsOn) {
    onTileCoordinateX =  nonActivatedOnTileCoordinateX;
    onTileCoordinateY =  nonActivatedOnTileCoordinateY;
    shiftY = 3;
    if (!isPlayerInitialized) {
        player = new QMediaPlayer();
        audioOutput = new QAudioOutput();
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl::fromLocalFile(prefixSoundPath + activatedSoundPath));
        isPlayerInitialized = true;
    }
}
QLabel *Spring::getQLabel(QWidget *parent) {
    QLabel *label = new QLabel(parent);
    label->setScaledContents(true);
    label->setGeometry(getCoordinateX(),getCoordinateY(),width, height);
    label->setPixmap(QPixmap(prefixPath + imagePath).copy(onTileCoordinateX,onTileCoordinateY,width,height));
    return label;
}
void Spring::setActivated() {
    activated = true;
    width = ActivatedWidth;
    height = ActivatedHeight;
    onTileCoordinateX = ActivatedOnTileCoordinateX;
    onTileCoordinateY = ActivatedOnTileCoordinateY;
}
void Spring::activate(DoubleJumper &activator) {
   // std::cout<<1;
    setActivated();
    if (soundsOn) {
        player->play();
    }
    activator.setSpeed(speedBuff);
}


