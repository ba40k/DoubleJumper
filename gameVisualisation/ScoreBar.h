//
// Created by radamir on 28.04.25.
//

#ifndef SCOREBAR_H
#define SCOREBAR_H

#include <QWidget>
#include <QVector>
#include <QLabel>

#include "Theme.h"

class ScoreBar : public QWidget{
    QString imagePrefixPath =  "requirments/Sprites/Doodle Jump/";
    Theme* theme;
    const int backGroundHeight = 92;
    const int backGroundWidth = 401;
    QVector<QLabel*> currentScore;
    QVector<QRect> digitsCoords;
    QLabel* backGround;

    public:
    ScoreBar(QWidget *parent = nullptr);
    void displayScore(int score);
    void setTheme(Theme* theme);
    ~ScoreBar();
};


#endif //SCOREBAR_H
