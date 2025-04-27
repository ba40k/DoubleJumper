//
// Created by radamir on 24.04.25.
//

#ifndef BROWNPLATFORM_H
#define BROWNPLATFORM_H

#include "AbstractPlatform.h"
#include <QMediaPlayer>
#include <QAudioOutput>
class BrownPlatform : public AbstractPlatform{
    private:
    bool broken = false;
    bool animationEnded = false;
    int animationCounter = 1;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QString soundPrefixPath = "requirments/Doodle Jump SFX/";
    QString breakingSoundPath = "egg-crack.mp3";
    public:
    BrownPlatform(int coordinateX, int coordinateY, QString &imagePath);
    QLabel* getQLabel(QWidget *parent = nullptr)  override;
    void setBroken();
    bool isBroken();
    bool isAnimationEnded();
    int getAnimationCounter();
    void setAnimationCounter(int counter);
};



#endif //BROWNPLATFORM_H
