//
// Created by radamir on 02.05.25.
//

#include "BlackHole.h"
QMediaPlayer* BlackHole::player = nullptr;
QAudioOutput* BlackHole::audioOutput = nullptr;
bool BlackHole::isPlayerInitialized = false;
BlackHole::BlackHole(int coordinateX, int coordinateY, QString &imagePath) : AbstractPlatform(coordinateX, coordinateY,125) {
    this->imagePath = imagePath;
    if (!isPlayerInitialized) {
        player = new QMediaPlayer();
        audioOutput = new QAudioOutput();
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl::fromLocalFile(soundPrefixPath + activatedSound));
        isPlayerInitialized = true;
    }
    spritesBoundingsRects = {{453,96,150,138}};
    WIDTH = spritesBoundingsRects[0].width();
    HEIGHT = spritesBoundingsRects[0].height();
}
QLabel* BlackHole::getQLabel(QWidget *parent)  {
    QLabel* label = new QLabel(parent);
    label->setScaledContents(true);
    label->setGeometry(coordinateX,coordinateY,spritesBoundingsRects[0].width(), spritesBoundingsRects[0].height());
    label->setPixmap(QPixmap(prefixPath + imagePath).copy(spritesBoundingsRects[0]));
    return label;
}
void BlackHole::playSound() {
    player->play();
}

