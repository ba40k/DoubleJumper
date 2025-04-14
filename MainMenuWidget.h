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
class MainMenuWidget : public QWidget {
    Q_OBJECT
    QTimer* timer;
    QString prefixPath;
    const int doubleJumperStartX = 55;
    const int doubleJumperStartY = 550;
    const int buttonWidth =222;
    const int buttonHeight = 80;
    const int crossSide = 44;
    const int doubleJumperHeight = 120;
    const int doubleJumperWidth = 124;
    QString backgroundImagePath;
    QString playButtonImagePath;
    QString highScoresButtonImagePath;
    QString optionsButtonImagePath;
    QString exitButtonImagePath;
    QString gameTitleImagePath;
    QLabel *gameTitleLabel;
    QPushButton *exitButton;
    QPushButton *playButton;
    QPushButton *optionsButton;
    QPushButton *highScoresButton;
    QLabel *backgroundLabel;
    QString doubleJumperImagePath;
    QLabel *doubleJumperLabel;

    long double speed;
    long double gravitation;
    long double currentX;
    long double currentY;
    const int deltaTime  = 10;
    long double nullEpsilon;
    long double sign = 1;
    bool stopped;
    public:
    void animationRun();
    void stop();
    void play();
    MainMenuWidget(QWidget *parent = nullptr);


};



#endif //MAINMENUWIDGET_H
