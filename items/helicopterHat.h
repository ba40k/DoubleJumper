//
// Created by radamir on 29.04.25.
//

#ifndef HELICOPTERHAT_H
#define HELICOPTERHAT_H

#include "AbstractItem.h"
#include <QMediaPlayer>
#include <QAudioOutput>

class HelicopterHat : public AbstractItem {
    bool activated = false;

    double speedBuff = 1.5;
    QString activatedSoundPath = "propeller1.mp3";
    static QMediaPlayer *player;
    static QAudioOutput *audioOutput;
    static bool isPlayerInitialized;
    int activatedTicks = 100;
public:
    HelicopterHat(int coordinateX, AbstractPlatform* platform);
    QLabel* getQLabel(QWidget *parent = nullptr) override;
    void activate(DoubleJumper &activator) override;
    void setActivated();
    int getActivatedTicks();
};



#endif //HELICOPTERHAT_H
