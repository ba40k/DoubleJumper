//
// Created by radamir on 29.04.25.
//

#include "Jetpack.h"
#include <iostream>
#include <QAudioOutput>
QMediaPlayer* Jetpack::player = nullptr;
QAudioOutput* Jetpack::audioOutput = nullptr;
bool Jetpack::isPlayerInitialized = false;
Jetpack::Jetpack(int coordinateX, AbstractPlatform* platform, bool soundsOn) : AbstractItem(coordinateX,35,21,platform, soundsOn) {
    onTileCoordinateX =  391;
    onTileCoordinateY =  527;
    width = 54;
    height = 76;
    shiftY = 3;
    boundingRectsForAnimation.push_back({74,256});
    boundingRectsForAnimation.push_back({10,256});
    boundingRectsForAnimation.push_back({202,128});
    boundingRectsForAnimation.push_back({138,128});
    boundingRectsForAnimation.push_back({74,128});
    boundingRectsForAnimation.push_back({10,128});
    boundingRectsForAnimation.push_back({202,0});
    boundingRectsForAnimation.push_back({138,0});
    boundingRectsForAnimation.push_back({74,0});
    boundingRectsForAnimation.push_back({10,0});
    if (!isPlayerInitialized) {
        player = new QMediaPlayer();
        audioOutput = new QAudioOutput();
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl::fromLocalFile(prefixSoundPath + activatedSoundPath));
        isPlayerInitialized = true;
    }
}
QLabel *Jetpack::getQLabel(QWidget *parent) {
    if (!activated) {
        QLabel *label = new QLabel(parent);
        label->setScaledContents(true);
        label->setGeometry(getCoordinateX(),getCoordinateY(),width, height);
        label->setPixmap(QPixmap(prefixPath + imagePath).copy(onTileCoordinateX,onTileCoordinateY,width,height));

        return label;
    } else {

        currentAnimationTick++;
        int index = (currentAnimationTick/oneImageTick)%boundingRectsForAnimation.size();
        QLabel *label = new QLabel(parent);
        label->setScaledContents(true);
        label->setGeometry(getCoordinateX(),getCoordinateY(),width,height);
        if (jumper->getOrintation() == false) {
            label->setPixmap(QPixmap(prefixPath + activatedImagesPath).copy(boundingRectsForAnimation[index].x(),boundingRectsForAnimation[index].y(),width,height));
        } else {
            QPixmap pix = QPixmap(prefixPath + activatedImagesPath).copy(boundingRectsForAnimation[index].x(),boundingRectsForAnimation[index].y(),width,height);
            pix = pix.transformed(QTransform().scale(-1, 1));
            label->setPixmap(pix);
        }
        return label;
    }
}
void Jetpack::setActivated() {
    activated = true;
}
void Jetpack::activate(DoubleJumper &activator) {
    // std::cout<<1;
    jumper = &activator;
    setActivated();
    height-=5;
    if (soundsOn) {
        player->play();
    }
    width = activatedWidth;
    height = activatedHeight;

}
int Jetpack::getActivatedTicks() {
    return activatedTicks;
}
int Jetpack::getCoordinateX() {
    if (!activated) {
        return platform->getX() + coordinateX + 5;
    } else {
            if (jumper->getOrintation() == false) {
                return jumper->getCoordinateX() + 82;
            } else {
                return jumper->getCoordinateX() - 9;
            }
    }
}
int Jetpack::getCoordinateY() {
    if (!activated) {
        return platform->getY()  - height + shiftY;
    } else {
        return jumper->getCoordinateY() + 20;
    }
}
double Jetpack::getSpeedBuff() {
    return speedBuff;
}