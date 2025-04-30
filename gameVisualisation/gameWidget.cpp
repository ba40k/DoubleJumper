//
// Created by radamir on 16.04.25.
//

#include "gameWidget.h"

#include "../platforms/GreenPlatform.h"
#include<iostream>
#include <QKeyEvent>

#include "../items/helicopterHat.h"
#include "../items/Spring.h"
#include "../platforms/BluePlatform.h"

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
    scoreBar = new ScoreBar(this);
    auto gamePlatforms = game.getPlatforms();
    platforms.resize(gamePlatforms->size());


    for (int i = 0; i < gamePlatforms->size(); i++) {
        if (dynamic_cast<BrownPlatform*>((*gamePlatforms)[i])) {
            platforms[i] = BrownPlatform((*gamePlatforms)[i]->getX(), (  (*gamePlatforms)[i]->getY()) ,imagePath).getQLabel(this);
        } else if (dynamic_cast<BluePlatform*>((*gamePlatforms)[i])) {
            platforms[i] =  BluePlatform((*gamePlatforms)[i]->getX(), (  (*gamePlatforms)[i]->getY()) ,imagePath).getQLabel(this);
        } else {
            platforms[i] = GreenPlatform((*gamePlatforms)[i]->getX(), (  (*gamePlatforms)[i]->getY()) ,imagePath).getQLabel(this);
        }
    }
    visualizeItems();
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
    auto gamePlatforms = game.getPlatforms();
  //  std::cout<<platforms.size()<<'\n';
    for (int i =0 ;i<platforms.size(); i++) {
        delete platforms[i];
    }
    platforms.clear();
    platforms.resize(gamePlatforms->size());
    for (int i = 0; i < gamePlatforms->size(); i++) {
        if (dynamic_cast<BrownPlatform*>((*gamePlatforms)[i])) {
            auto temp =  BrownPlatform((*gamePlatforms)[i]->getX(),   (*gamePlatforms)[i]->getY() + shift,imagePath);
            if (dynamic_cast<BrownPlatform*>((*gamePlatforms)[i])->isBroken()) {
                temp.setBroken();
            }
            temp.setAnimationCounter(dynamic_cast<BrownPlatform*>((*gamePlatforms)[i])->getAnimationCounter());
            platforms[i] = temp.getQLabel(this);
            if (temp.isBroken()) {
                dynamic_cast<BrownPlatform*>((*gamePlatforms)[i])->setAnimationCounter(dynamic_cast<BrownPlatform*>((*gamePlatforms)[i])->getAnimationCounter()+1);
            }
        } else if (dynamic_cast<GreenPlatform*>((*gamePlatforms)[i])) {
            platforms[i] = GreenPlatform((*gamePlatforms)[i]->getX(),   (*gamePlatforms)[i]->getY() + shift,imagePath).getQLabel(this);
        } else {
            platforms[i] = BluePlatform((*gamePlatforms)[i]->getX(),   (*gamePlatforms)[i]->getY() + shift,imagePath).getQLabel(this);
        }
        if ((dynamic_cast<BrownPlatform*>((*gamePlatforms)[i]) && !dynamic_cast<BrownPlatform*>((*gamePlatforms)[i])->isAnimationEnded())
            || dynamic_cast<GreenPlatform*>((*gamePlatforms)[i]) || dynamic_cast<BluePlatform*>((*gamePlatforms)[i])) {
            platforms[i]->show();
        }

    }
    visualizeItems();
    doubleJumperLabel->setPixmap(game.getDoubleJumper()->getLabel(this)->pixmap());
    doubleJumperLabel->move(game.getDoubleJumperX(), game.getDoubleJumperY() + shift);
    doubleJumperLabel->raise();
    if (currentScoreTick%scoreUpdateTick==0) {
        scoreBar->displayScore(game.getScore());
    }

    if (game.getHatPointer()!=nullptr) {
        if (currentHatLabel!=nullptr) {
            delete currentHatLabel;
        }
        currentHatLabel = game.getHatPointer()->getQLabel(this);
        currentHatLabel->move(currentHatLabel->x(), currentHatLabel->y() + game.getShift());
        currentHatLabel->show();
    } else {
        if (currentHatLabel!=nullptr) {
            delete currentHatLabel;
            currentHatLabel = nullptr;
        }
    }
    scoreBar->raise();
    ++currentScoreTick;
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
void GameWidget::visualizeItems() {
    auto gameItems = game.getItems();
    for (int i =0 ;i<items.size(); i++) {
        delete items[i];
    }
    items.clear();
    items.resize(gameItems->size());
    for (int i = 0; i < gameItems->size(); i++) {
        if ( dynamic_cast<Spring*>((*gameItems)[i])) {
            items[i] = dynamic_cast<Spring*>((*gameItems)[i])->getQLabel(this);
            items[i]->move(items[i]->x(), items[i]->y() + game.getShift());
            items[i]->show();
        } else if ( dynamic_cast<HelicopterHat*>((*gameItems)[i])) {
            items[i] = dynamic_cast<HelicopterHat*>((*gameItems)[i])->getQLabel(this);
            items[i]->move(items[i]->x(), items[i]->y() + game.getShift());
            items[i]->show();
        }
    }

}