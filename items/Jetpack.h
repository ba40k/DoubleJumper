//
// Created by radamir on 01.05.25.
//

#ifndef JETPACK_H
#define JETPACK_H



#include "AbstractItem.h"
#include <QMediaPlayer>
#include <QAudioOutput>

class Jetpack : public AbstractItem {
    bool activated = false;
    double speedBuff = 2.0;
    int activatedHeight = 124;
    int activatedWidth = 52;

    QString activatedSoundPath = "jetpack1.mp3";
    QString activatedImagesPath = "jetpack@2x.png";
    QVector<QPoint> boundingRectsForAnimation;
    int oneImageTick = 5;
    int currentAnimationTick=0;
    static QMediaPlayer *player;
    static QAudioOutput *audioOutput;
    static bool isPlayerInitialized;
    int activatedTicks = 300;
    DoubleJumper* jumper;
public:
    Jetpack(int coordinateX, AbstractPlatform* platform);
    QLabel* getQLabel(QWidget *parent = nullptr) override;
    void activate(DoubleJumper &activator) override;
    void setActivated();
    int getActivatedTicks();
    int getCoordinateX() override;
    int getCoordinateY() override;
    double getSpeedBuff();
};


#endif //JETPACK_H
