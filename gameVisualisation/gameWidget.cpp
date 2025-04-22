//
// Created by radamir on 16.04.25.
//

#include "gameWidget.h"

#include "../platforms/GreenPlatform.h"
#include<iostream>
#include <QKeyEvent>
GameWidget::GameWidget(QWidget *parent) {
    setFocusPolicy(Qt::StrongFocus); // Разрешаем фокус клавиатуры
    setFocus(); // Захватываем фокус
    game.gameInitialize();
    prefixPath = "requirments/Sprites/Doodle Jump/";
    backgoundImagePath = "bck@2x.png";
    backgoundLabel = new QLabel(this);
    resize(parent->width(), parent->height());

    backgoundLabel->setScaledContents(true);
    backgoundLabel->setGeometry(QRect(0, 0, parent->width(), parent->height()));

    backgoundLabel->setPixmap(QPixmap(prefixPath + backgoundImagePath));

    auto gamePlatforms = game.getPlatforms();
    platforms.resize(gamePlatforms->size());

    QString  imagePath = "game-tiles@2x.png";
    for (int i = 0; i < gamePlatforms->size(); i++) {
     //  std::cout<<(*gamePlatforms)[i]->getX()<<' '<< (*gamePlatforms)[i]->getY()<<'\n';
        platforms[i] = GreenPlatform((*gamePlatforms)[i]->getX(), (  (*gamePlatforms)[i]->getY()) ,imagePath).getQLabel(this);
    }
    timer = new QTimer(this);
    timer->setInterval(deltaTime);
    timer->setSingleShot(false);


    doubleJumperLabel = game.getDoubleJumper()->getLabel(this);

    connect(timer, &QTimer::timeout ,this, &GameWidget::update);
    stop();
}
void GameWidget::update() {

    int shift = game.getShift();
    game.gameStateUpdate(deltaTime,leftArrowPressed,rightArrowPressed);
    doubleJumperLabel->setPixmap(game.getDoubleJumper()->getLabel(this)->pixmap());
    doubleJumperLabel->move(game.getDoubleJumperX(), game.getDoubleJumperY() + shift);
     auto gamePlatforms = game.getPlatforms();
    QString imagePath = "game-tiles@2x.png";
  //  std::cout<<platforms.size()<<'\n';
    for (int i =0 ;i<platforms.size(); i++) {
        delete platforms[i];
    }
    platforms.clear();
    platforms.resize(gamePlatforms->size());

    std::cout<<shift<<std::endl;
    for (int i = 0; i < gamePlatforms->size(); i++) {
        platforms[i] = GreenPlatform((*gamePlatforms)[i]->getX(),   (*gamePlatforms)[i]->getY() + shift,imagePath).getQLabel(this);
        platforms[i]->show();
    }

}
void GameWidget::stop() {
    timer->stop();
    stopped = true;
}
void GameWidget::run() {
    timer->start();
    stopped = false;
}
void GameWidget::keyPressEvent(QKeyEvent *event) {

    switch (event->key()) {
        case Qt::Key_Left:
            if (game.getDoubleJumper()->getOrintation() == 1) {
                game.getDoubleJumper()->changeOrintation();
            }
            leftArrowPressed = true;


        break;
        case Qt::Key_Right:
            rightArrowPressed = true;
        if (game.getDoubleJumper()->getOrintation() == 0) {
            game.getDoubleJumper()->changeOrintation();
        }
        break;

        default:
            QWidget::keyPressEvent(event); // передаём остальные события родителю
    }
}

void GameWidget::keyReleaseEvent(QKeyEvent *event) {

    switch (event->key()) {
        case Qt::Key_Left:
            leftArrowPressed = false;
        break;
        case Qt::Key_Right:
            rightArrowPressed = false;
        break;

        default:
            QWidget::keyPressEvent(event); // передаём остальные события родителю
    }
}
