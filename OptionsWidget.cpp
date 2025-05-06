//
// Created by radamir on 05.05.25.
//

#include "OptionsWidget.h"
#include <QFontDatabase>
#include <iostream>

#include "MainMenuWidget.h"
#include "mainwindow.h"
int OptionsWidget::currentSprite = 0;
int OptionsWidget::currentBackGround = 0;
void OptionsWidget::setDefaultStylnig(const QString &prefix, const QString &suffix, QPushButton *button) {
    button->setStyleSheet(
        "QPushButton {"
        "   background-image: url(\"" + prefix + suffix + "\");"
        "   background-repeat: no-repeat;" // Не повторять изображение
        "   background-position: center;" // Центрировать
        "   border: none;" // Убрать стандартную рамку
        "   padding: 10px;" // Отступ для текста/иконки
        "   font-family: " + font->family() + ";"  // Сохраняем шрифт
        "   font-size: " + QString::number(50) + "px;"  // Размер
        "}"
    );
}
OptionsWidget::OptionsWidget(QWidget *parent,bool currentSoundState, bool currentMarkersState) {
    soundOn = currentSoundState;
    scoreMarkersOn = currentMarkersState;
    fontId = QFontDatabase::addApplicationFont(fontPath);
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    font = new QFont(fontFamilies.at(0), 40);
    setFont(*font);
    setParent(parent);
    setFixedHeight(HEIGHT);
    setFixedWidth(WIDTH);
    backGroundLabel = new QLabel(this);
    backGroundLabel->setGeometry(0,0,WIDTH,HEIGHT);
    backGroundLabel->setPixmap(QPixmap(imagePrefixPath + backGroundPath));
    backGroundLabel->setScaledContents(true);
    optionsLabel = new QLabel(this);
    optionsLabel->setGeometry(250,40,200,50);
    optionsLabel->setText("Options");

    soundLabel = new QLabel(this);
    soundLabel->setGeometry(100,80,150,150);
    soundLabel->setText("Sound: ");

    scoreMarkersLabel = new QLabel(this);
    scoreMarkersLabel->setGeometry(100,160,350,150);
    scoreMarkersLabel->setText("Score markers: ");

    soundOnButton = new QPushButton(this);
    soundOnButton->setGeometry(300,145,40,28);
    setDefaultStylnig(imagePrefixPath,onImageOnPath,soundOnButton);

    soundOffButton = new QPushButton(this);
    soundOffButton->setGeometry(400,145,50,28);
    setDefaultStylnig(imagePrefixPath,offImageOffPath,soundOffButton);

    scoreMarkersOnButton = new QPushButton(this);
    scoreMarkersOnButton->setGeometry(475,225,40,28);
    setDefaultStylnig(imagePrefixPath,onImageOnPath,scoreMarkersOnButton);

    scoreMarkersOffButton = new QPushButton(this);
    scoreMarkersOffButton->setGeometry(575,225,50,28);
    setDefaultStylnig(imagePrefixPath,offImageOffPath,scoreMarkersOffButton);

    menuButton = new QPushButton(this);
    menuButton->setGeometry(400,750,224,82);
    setDefaultStylnig(imagePrefixPath,templateButtonImagePath,menuButton);
    menuButton->setText("Menu");

    resetHighScoresButton = new QPushButton(this);
    resetHighScoresButton->setGeometry(30,750,225,82);
    setDefaultStylnig(imagePrefixPath,templateButtonImagePath,resetHighScoresButton);
    resetHighScoresButton->setText("Reset");

    if (soundOn == false) {
        soundOffButtonClicked();
    }
    if (scoreMarkersOn == false) {
        scoreMarkersOffButtonClicked();
    }
    connect(soundOnButton,&QPushButton::clicked,this,&OptionsWidget::soundOnButtonClicked);
    connect(soundOffButton,&QPushButton::clicked,this,&OptionsWidget::soundOffButtonClicked);
    connect(scoreMarkersOnButton,&QPushButton::clicked,this,&OptionsWidget::scoreMarkersOnButtonClicked);
    connect(scoreMarkersOffButton,&QPushButton::clicked,this,&OptionsWidget::scoreMarkersOffButtonClicked);
    connect(menuButton,&QPushButton::clicked,this,&OptionsWidget::menuButtonClicked);
    connect(resetHighScoresButton,&QPushButton::clicked,this,&OptionsWidget::resetHighScoresButtonClicked);

}
void OptionsWidget::soundOnButtonClicked() {
    soundOn = true;
    setDefaultStylnig(imagePrefixPath,onImageOnPath,soundOnButton);
    setDefaultStylnig(imagePrefixPath,offImageOffPath,soundOffButton);
    dynamic_cast<MainWindow*>(parent()->parent())->soundOn = true;
}
void OptionsWidget::soundOffButtonClicked() {
    soundOn = false;
    setDefaultStylnig(imagePrefixPath,offImageOnPath,soundOffButton);
    setDefaultStylnig(imagePrefixPath,onImageOffPath,soundOnButton);
    dynamic_cast<MainWindow*>(parent()->parent())->soundOn = false;
}
void OptionsWidget::menuButtonClicked() {
    dynamic_cast<MainMenuWidget*>(parent())->play();
    delete this;
}
void OptionsWidget::resetHighScoresButtonClicked() {
    QFile file(recordsFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return ; // Не удалось открыть файл
    }
    file.close();
}
void OptionsWidget::scoreMarkersOffButtonClicked() {
    scoreMarkersOn = false;
    setDefaultStylnig(imagePrefixPath,offImageOnPath,scoreMarkersOffButton);
    setDefaultStylnig(imagePrefixPath,onImageOffPath,scoreMarkersOnButton);
    dynamic_cast<MainWindow*>(parent()->parent())->visibleScoreMarkers = false;
}
void OptionsWidget::scoreMarkersOnButtonClicked() {
    scoreMarkersOn = true;
    setDefaultStylnig(imagePrefixPath,onImageOnPath,scoreMarkersOnButton);
    setDefaultStylnig(imagePrefixPath,offImageOffPath,scoreMarkersOffButton);
    dynamic_cast<MainWindow*>(parent()->parent())->visibleScoreMarkers = true;

}




