//
// Created by radamir on 13.04.25.
//

#include "MainMenuWidget.h"
#include <QPushButton>
#include <QLabel>
#include<QTime>
#include<QTimer>
#include <iostream>
#include <QSoundEffect>

MainMenuWidget::MainMenuWidget(QWidget *parent) : physicsModel(0.0019), doubleJumper(doubleJumperStartX,doubleJumperStartY,1.0,-1) {

    resize(parent->width(), parent->height());
    setMinimumSize(QSize(width(), height()));
    backgroundLabel = new QLabel(this);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->resize(width(), height());

    imagePrefixPath = "requirments/Sprites/Doodle Jump/";
    soundPrefixPath = "requirments/Doodle Jump SFX/";
    backgroundImagePath = "Default@2x.png";
    jumpSoundPath = "jump.wav";
    jumpSound.setSource(QUrl::fromLocalFile(soundPrefixPath + jumpSoundPath));

    QPixmap bgPixmap(imagePrefixPath + backgroundImagePath);

    backgroundLabel->setPixmap(bgPixmap);

    playButtonImagePath = "play@2x.png";
    exitButtonImagePath = "news-close@2x.png";
    optionsButtonImagePath = "options@2x.png";
    highScoresButtonImagePath = "scores@2x.png";

    playButton = new QPushButton(this);
    exitButton = new QPushButton(this);
    optionsButton = new QPushButton(this);
    highScoresButton = new QPushButton(this);

    playButton->setGeometry(120, 200, buttonWidth, buttonHeight);
    exitButton->setGeometry(width() - crossSide, 0, crossSide, crossSide);
    optionsButton->setGeometry(width() - buttonWidth, 530, buttonWidth, buttonHeight);
    highScoresButton->setGeometry(width() - buttonWidth, 650, buttonWidth, buttonHeight);

    doubleJumperImagePath = "lik-right@2x.png";
    doubleJumperLabel = new QLabel(this);
    doubleJumperLabel->setPixmap(imagePrefixPath + doubleJumperImagePath);
    doubleJumperLabel->setScaledContents(true);
    doubleJumperLabel->setGeometry(doubleJumperStartX, doubleJumperStartY, doubleJumperWidth, doubleJumperHeight);

    setDefaultStylnig(imagePrefixPath, playButtonImagePath, playButton);

    setDefaultStylnig(imagePrefixPath, optionsButtonImagePath, optionsButton);

    setDefaultStylnig(imagePrefixPath, highScoresButtonImagePath, highScoresButton);

    setDefaultStylnig(imagePrefixPath, exitButtonImagePath, exitButton);


    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(deltaTime);
    connect(timer, &QTimer::timeout, this, &MainMenuWidget::animationRun);
    timer->start();
}

void MainMenuWidget::stop() {
    stopped = true;
}

void MainMenuWidget::play() {
    stopped = false;
}


void MainMenuWidget::animationRun() {
    // x - неизменен
    // y меняется по закону : y0 + v0*t + at^2/2

    if (doubleJumper.getSpeed() < 0 || doubleJumper.getCoordinateY() > doubleJumperStartY) {
        doubleJumper.changeDirection();
        doubleJumper.getDirection() > 0 ? doubleJumper.setSpeed(0) : doubleJumper.setSpeed(1.0);
        if (doubleJumper.getDirection() == -1) {
            jumpSound.play();
        }
    }

    long double deltaY = physicsModel.calculateDistace(deltaTime,doubleJumper.getSpeed());
    doubleJumper.setSpeed(physicsModel.calculateSpeed(deltaTime,doubleJumper.getSpeed(),doubleJumper.getDirection()));
    doubleJumperLabel->setGeometry(doubleJumper.getCoordinateX(), doubleJumper.getCoordinateY(), doubleJumperWidth, doubleJumperHeight);
    doubleJumper.setCoordinateY(doubleJumper.getCoordinateY() + doubleJumper.getDirection()* deltaY);
    timer->setSingleShot(true);
    timer->start();
}

void MainMenuWidget::setDefaultStylnig(const QString &prefix,const QString &suffix, QPushButton *button) {
    button->setStyleSheet(
        "QPushButton {"
        "   background-image: url(\"" + prefix + suffix + "\");"
        "   background-repeat: no-repeat;" // Не повторять изображение
        "   background-position: center;" // Центрировать
        "   border: none;" // Убрать стандартную рамку
        "   padding: 10px;" // Отступ для текста/иконки
        "}"
    );
}
