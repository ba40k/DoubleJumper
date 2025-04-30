//
// Created by radamir on 16.04.25.
//

#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QLabel>
#include "../game/Game.h"
#include <QTimer>
#include "ScoreBar.h"
class GameWidget : public QWidget{
    QString prefixPath;
    QString backgoundImagePath;
    QLabel *backgoundLabel;
    QString  imagePath = "game-tiles@2x.png";
    Game game;
    QLabel* doubleJumperLabel;
    QVector<QLabel*> platforms;
    QVector<QLabel*> items;
    const int deltaTime = 15;
    QTimer* timer;
    bool stopped = false;
    void update();
    bool leftArrowPressed = false;
    bool rightArrowPressed = false;
    ScoreBar* scoreBar;
    const int scoreUpdateTick = 10;
    int currentScoreTick = 0;
    QLabel* currentHatLabel=nullptr;
    void visualizeItems();
    public:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    GameWidget(QWidget *parent = nullptr);
    void stop();
    void run();

};



#endif //GAMEWIDGET_H
