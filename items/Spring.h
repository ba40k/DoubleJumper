//
// Created by radamir on 29.04.25.
//

#ifndef SPRING_H
#define SPRING_H

#include "AbstractItem.h"
#include <QMediaPlayer>
class Spring : public AbstractItem{
    bool activated = false;
    const int nonActivatedOnTileCoordinateX = 806;
    const int nonActivatedOnTileCoordinateY = 196;
    const int nonActivatedWidth = 35;
    const int nonActivatedHeight = 21;
    const int ActivatedOnTileCoordinateX = 808;
    const int ActivatedOnTileCoordinateY = 230;
    const int ActivatedWidth = 35;
    const int ActivatedHeight = 53;
    double speedBuff = 2.0;
    QString activatedSoundPath = "spring-arcade.mp3";
    static QMediaPlayer *player;
    static QAudioOutput *audioOutput;
    static bool isPlayerInitialized;
    public:
    Spring(int coordinateX, AbstractPlatform* platform);
    QLabel* getQLabel(QWidget *parent = nullptr) override;
    void activate(DoubleJumper &activator) override;
    void setActivated();


};



#endif //SPRING_H
