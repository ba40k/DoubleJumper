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
    static QMediaPlayer *player;
    static QAudioOutput *audioOutput;
    static bool isPlayerInitialized;
    QString soundPrefixPath = "requirments/Doodle Jump SFX/";
    QString breakingSoundPath = "lomise.mp3";
    QVector<QRect> spritesBoundingsRects;
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
