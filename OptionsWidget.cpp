//
// Created by radamir on 05.05.25.
//

#include "OptionsWidget.h"
#include <QFontDatabase>


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
OptionsWidget::OptionsWidget(QWidget *parent) {
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

}

