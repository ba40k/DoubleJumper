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


    LoseDialog *loseDialog;
    QString prefixPath;
    QString backgoundImagePath;
    QLabel *backgoundLabel;
    QString  imagePath = "game-tiles@2x.png";
    QString scoreMarkerImagePath = "score-marker@2x.png";
    Game game;
    QLabel* doubleJumperLabel;
    QVector<QLabel*> platforms;
    QVector<QLabel*> items;
    QVector<QLabel*> scoreMarkers;
    QVector<QLabel*> scoreMarkerNames;
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
    void visualizeScoreMarkers();

    int calculateLabelWidth(const QLabel* label, const QString& text);
    public:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    GameWidget(QWidget *parent = nullptr);
    ~GameWidget();
    void stop();
    void run();
    void playBlackHoleAnimation();


};



#endif //GAMEWIDGET_H
