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
    backgroundImagePath = "requirments/Sprites/Doodle Jump/bck@2x.png";

    QPixmap bgPixmap(backgroundImagePath);

    backgroundLabel->setPixmap(bgPixmap);

    playButtonImagePath =  "requirments/Sprites/Doodle Jump/play@2x.png";
    exitButtonImagePath = "requirments/Sprites/Doodle Jump/news-close@2x.png";
    optionsButtonImagePath = "requirments/Sprites/Doodle Jump/options@2x.png";
    highScoresButtonImagePath = "requirments/Sprites/Doodle Jump/scores@2x.png";

    playButton = new QPushButton(this);
    exitButton = new QPushButton(this);
    optionsButton = new QPushButton(this);
    highScoresButton = new QPushButton(this);

    playButton->setGeometry(100,200,buttonWidth,buttonHeight);
    exitButton->setGeometry(width() - crossSide, 0, crossSide,crossSide);
    optionsButton->setGeometry(width() - buttonWidth,height() - buttonHeight,buttonWidth,buttonHeight);
    highScoresButton->setGeometry(width() - buttonWidth,600,buttonWidth,buttonHeight);

    playButton->setStyleSheet(
     "QPushButton {"
     "   background-image: url(\"" + playButtonImagePath + "\");"
     "   background-repeat: no-repeat;"       // Не повторять изображение
     "   background-position: center;"        // Центрировать
     "   border: none;"                       // Убрать стандартную рамку
     "   padding: 10px;"                      // Отступ для текста/иконки
     "}"

    );

    optionsButton->setStyleSheet(
     "QPushButton {"
     "   background-image: url(\"" + optionsButtonImagePath + "\");"
     "   background-repeat: no-repeat;"       // Не повторять изображение
     "   background-position: center;"        // Центрировать
     "   border: none;"                       // Убрать стандартную рамку
     "   padding: 10px;"                      // Отступ для текста/иконки
     "}"

    );

    highScoresButton->setStyleSheet(
     "QPushButton {"
     "   background-image: url(\"" + highScoresButtonImagePath + "\");"
     "   background-repeat: no-repeat;"       // Не повторять изображение
     "   background-position: center;"        // Центрировать
     "   border: none;"                       // Убрать стандартную рамку
     "   padding: 10px;"                      // Отступ для текста/иконки
     "}"

    );

   exitButton->setStyleSheet(
     "QPushButton {"
     "   background-image: url(\"" + exitButtonImagePath + "\");"
     "   background-repeat: no-repeat;"       // Не повторять изображение
     "   background-position: center;"        // Центрировать
     "   border: none;"                       // Убрать стандартную рамку
     "   padding: 10px;"                      // Отступ для текста/иконки
     "}"

    );

}
void MainMenuWidget::resizeEvent(QResizeEvent* event) {
    QPixmap bgPixmap(backgroundImagePath);
    bgPixmap = bgPixmap.scaled(size(), Qt::KeepAspectRatioByExpanding);
    backgroundLabel->setPixmap(bgPixmap);
    QWidget::resizeEvent(event);
}
