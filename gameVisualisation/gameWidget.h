//
// Created by radamir on 16.04.25.
//

#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QLabel>
#include "../game/Game.h"
#include <QTimer>
class GameWidget : public QWidget{
    QString prefixPath;
    QString backgoundImagePath;
    QLabel *backgoundLabel;
    Game game;
    int showUpperDoubleJumper = 500;
    int showLowerDoubleJumper = 350;

    QLabel* doubleJumperLabel;
    QVector<QLabel*> platforms;
    const int deltaTime = 10;
    QTimer* timer;
    bool stopped = false;
    void update();
    bool leftArrowPressed = false;
    bool rightArrowPressed = false;

    public:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    GameWidget(QWidget *parent = nullptr);
    void stop();
    void run();

};



#endif //GAMEWIDGET_H
