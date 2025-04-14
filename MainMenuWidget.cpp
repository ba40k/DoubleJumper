//
// Created by radamir on 13.04.25.
//

#include "MainMenuWidget.h"
#include <QPushButton>
#include <QLabel>
MainMenuWidget::MainMenuWidget(QWidget *parent) {
     // Создаем layout
    resize(parent->width(), parent->height());
    setMinimumSize(QSize(width(), height()));
    backgroundLabel = new QLabel(this);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->resize(width(),height());

    prefixPath = "requirments/Sprites/Doodle Jump/";
    backgroundImagePath =   "Default@2x.png";

    QPixmap bgPixmap(prefixPath + backgroundImagePath);

    backgroundLabel->setPixmap(bgPixmap);

    playButtonImagePath =  "play@2x.png";
    exitButtonImagePath = "news-close@2x.png";
    optionsButtonImagePath = "options@2x.png";
    highScoresButtonImagePath = "scores@2x.png";

    playButton = new QPushButton(this);
    exitButton = new QPushButton(this);
    optionsButton = new QPushButton(this);
    highScoresButton = new QPushButton(this);

    playButton->setGeometry(120,200,buttonWidth,buttonHeight);
    exitButton->setGeometry(width() - crossSide, 0, crossSide,crossSide);
    optionsButton->setGeometry(width() - buttonWidth,530,buttonWidth,buttonHeight);
    highScoresButton->setGeometry(width() - buttonWidth,650,buttonWidth,buttonHeight);

   doubleJumperImagePath = "lik-right@2x.png";
   doubleJumperLabel = new QLabel(this);
   doubleJumperLabel->setPixmap(prefixPath + doubleJumperImagePath);
   doubleJumperLabel->setScaledContents(true);
   doubleJumperLabel->setGeometry(doubleJumperStartX,doubleJumperStartY,doubleJumperWidth,doubleJumperHeight);

    playButton->setStyleSheet(
     "QPushButton {"
     "opacity: 0;"
     "   background-image: url(\"" + prefixPath +  playButtonImagePath + "\");"
     "   background-repeat: no-repeat;"       // Не повторять изображение
     "   background-position: center;"        // Центрировать
     "   border: none;"                       // Убрать стандартную рамку
     "   padding: 10px;"                      // Отступ для текста/иконки
     "}"

    );

    optionsButton->setStyleSheet(
     "QPushButton {"
     "   background-image: url(\"" + prefixPath + optionsButtonImagePath + "\");"
     "   background-repeat: no-repeat;"       // Не повторять изображение
     "   background-position: center;"        // Центрировать
     "   border: none;"                       // Убрать стандартную рамку
     "   padding: 10px;"                      // Отступ для текста/иконки
     "}"

    );

    highScoresButton->setStyleSheet(
     "QPushButton {"
     "   background-image: url(\"" + prefixPath + highScoresButtonImagePath + "\");"
     "   background-repeat: no-repeat;"       // Не повторять изображение
     "   background-position: center;"        // Центрировать
     "   border: none;"                       // Убрать стандартную рамку
     "   padding: 10px;"                      // Отступ для текста/иконки
     "}"

    );

   exitButton->setStyleSheet(
     "QPushButton {"
     "   background-image: url(\"" + prefixPath +  exitButtonImagePath + "\");"
     "   background-repeat: no-repeat;"       // Не повторять изображение
     "   background-position: center;"        // Центрировать
     "   border: none;"                       // Убрать стандартную рамку
     "   padding: 10px;"                      // Отступ для текста/иконки
     "}"

    );

}
