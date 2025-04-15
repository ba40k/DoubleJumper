//
// Created by radamir on 13.04.25.
//

#ifndef MAINMENUWIDGET_H
#define MAINMENUWIDGET_H

#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QSoundEffect>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include "PhysicsModel.h"
#include "DoubleJumper.h"

class MainMenuWidget : public QWidget {
    Q_OBJECT
    QTimer* timer;
    QString imagePrefixPath;
    QString soundPrefixPath;
    QString jumpSoundPath ;
    QString backgroundImagePath;
    QString playButtonImagePath;
    QString highScoresButtonImagePath;
    QString optionsButtonImagePath;
    QString exitButtonImagePath;
    QString gameTitleImagePath;
    QString doubleJumperImagePath;
    QString ufoImagePath;
    QString ufoPosititionsJsonPath;
    QString ufoNoLightImagePath;

    QSoundEffect jumpSound;

    const int ufoWidth =171;
    const int ufoHeight =257;
    const int doubleJumperStartX = 55;
    const int doubleJumperStartY = 550;
    const int buttonWidth =222;
    const int buttonHeight = 80;
    const int crossSide = 44;
    const int doubleJumperHeight = 120;
    const int doubleJumperWidth = 124;
    QLabel *ufoLabel;
    QPushButton *exitButton;
    QPushButton *playButton;
    QPushButton *optionsButton;
    QPushButton *highScoresButton;
    QLabel *backgroundLabel;
    QLabel *doubleJumperLabel;


    DoubleJumper doubleJumper;

    const int deltaTime  = 10;


    bool stopped;
    PhysicsModel physicsModel;
    void setDefaultStylnig(const QString &prefix,const QString &suffix, QPushButton *button);

    QVector<QPair<int,int>> ufoPositions;
    int currentUfoPosition;
    int ufoTicks = 0;

    QVector<QPair<int,int>> parseJson(const QString& filename) const;
    public:


    void animationRun();
    void stop();
    void play();
    MainMenuWidget(QWidget *parent = nullptr);


};



#endif //MAINMENUWIDGET_H
