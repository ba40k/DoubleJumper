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
#include "LoseDialog.h"
#include "../game/RecordDatabase.h"

class GameWidget : public QWidget{
    RecordDatabase *records;

    LoseDialog *loseDialog;
    QString prefixPath;
    QString backgoundImagePath;
    QLabel *backgoundLabel;
    QString  imagePath = "game-tiles@2x.png";
    Game game;
    QLabel* doubleJumperLabel;
    QVector<QLabel*> platforms;
    QVector<QLabel*> items;
    const int deltaTime = 8;
    int blackHoleAnimationTicks = 50;
    QTimer* timer;
    bool stopped = false;
    void update();
    bool leftArrowPressed = false;
    bool rightArrowPressed = false;
    ScoreBar* scoreBar;
    const int scoreUpdateTick = 10;
    int currentScoreTick = 0;
    QLabel* currentHatLabel=nullptr;
    QLabel* currentJetpackLabel = nullptr;
    void visualizeItems();
    public:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    GameWidget(QWidget *parent = nullptr);
    void stop();
    void run();
    void playBlackHoleAnimation();
    RecordDatabase* getRecordDatabase();

};



#endif //GAMEWIDGET_H
