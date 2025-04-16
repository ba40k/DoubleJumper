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

MainMenuWidget::MainMenuWidget(QWidget *parent) : physicsModel(0.0019),
                                                  doubleJumper(doubleJumperStartX, doubleJumperStartY, 1.0, -1) {
    resize(parent->width(), parent->height());
    setMinimumSize(QSize(width(), height()));
    backgroundLabel = new QLabel(this);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->resize(width(), height());


    ufoPosititionsJsonPath = "requirments/ufoPoint.json";
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
    ufoImagePath = "ufo@2x.png";
    ufoNoLightImagePath = "ufo-no-light@2x.png";

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
    currentUfoPosition = 0;
    ufoPositions = parseJson(ufoPosititionsJsonPath);

    ufoLabel = new QLabel(this);
    ufoLabel->setScaledContents(true);
    ufoLabel->setGeometry(ufoPositions[0].first,ufoPositions[0].second,ufoWidth, ufoHeight);
    ufoLabel->setPixmap(imagePrefixPath + ufoImagePath);
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


    long double deltaY = physicsModel.calculateDistace(deltaTime, doubleJumper.getSpeed());
    doubleJumper.setSpeed(physicsModel.calculateSpeed(deltaTime, doubleJumper.getSpeed(), doubleJumper.getDirection()));
    doubleJumperLabel->setGeometry(doubleJumper.getCoordinateX(), doubleJumper.getCoordinateY(), doubleJumperWidth,
                                   doubleJumperHeight);
    doubleJumper.setCoordinateY(doubleJumper.getCoordinateY() + doubleJumper.getDirection() * deltaY);

    ufoTicks++;
    if (ufoTicks ==25) {

        ufoLabel->setPixmap(imagePrefixPath + ufoNoLightImagePath);
    }
    if (ufoTicks == 2) {

        ufoLabel->setPixmap(imagePrefixPath + ufoImagePath);
    }
    if (ufoTicks %2 == 0) {

        ufoLabel->setGeometry(ufoPositions[currentUfoPosition].first,ufoPositions[currentUfoPosition].second,ufoWidth, ufoHeight);
        currentUfoPosition = (currentUfoPosition + 1) % ufoPositions.size();
        ufoTicks%=50;
    }
    timer->setSingleShot(true);
    timer->start();
}

void MainMenuWidget::setDefaultStylnig(const QString &prefix, const QString &suffix, QPushButton *button) {
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
QVector<QPair<int, int> > MainMenuWidget::parseJson(const QString &filename) const {
    QVector<QPair<int,int>> result;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file:" << file.errorString();
        return result;
    }

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
    if (error.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << error.errorString();
        return result;
    }

    if (!doc.isArray()) {
        qWarning() << "Invalid JSON structure: root is not an array";
        return result;
    }

    QJsonArray arr = doc.array();
    for (const QJsonValue& val : arr) {
        if (!val.isArray()) {
            qWarning() << "Invalid point format";
            continue;
        }

        QJsonArray point = val.toArray();
        if (point.size() != 2) {
            qWarning() << "Invalid point coordinates";
            continue;
        }

        result.emplace_back(
            point[0].toInt(),
            point[1].toInt()
        );
    }

    return result;
}
