//
// Created by radamir on 02.05.25.
//

#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "AbstractPlatform.h"
#include "../DoubleJumper.h"
#include <QMediaPlayer>
#include <QAudioOutput>
class BlackHole : public AbstractPlatform{
private:
    static QMediaPlayer *player;
    static QAudioOutput *audioOutput;
    static bool isPlayerInitialized;
    QString soundPrefixPath = "requirments/Doodle Jump SFX/";
    QString activatedSound = "crnarupa.mp3";
    QVector<QRect> spritesBoundingsRects;
public:
    BlackHole(int coordinateX, int coordinateY, QString &imagePath);
    QLabel* getQLabel(QWidget *parent = nullptr)  override;
    void activate(DoubleJumper *activator);
    void playSound();
};
#endif //BLACKHOLE_H
