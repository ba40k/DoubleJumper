//
// Created by radamir on 13.04.25.
//

#include "MainMenuWidget.h"
#include <QPushButton>
#include <QLabel>
#include<QTime>
#include<QTimer>
#include <iostream>
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
   gravitation = 0.0019;
   speed =1.0;
   nullEpsilon = 0.0001;
   currentX = doubleJumperStartX;
   currentY = doubleJumperStartY;
   timer = new QTimer(this);
   timer->setSingleShot(true);
   timer->setInterval(deltaTime);
   connect(timer,&QTimer::timeout,this,&MainMenuWidget::animationRun);
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
    // std::cout<<speed<<' '<<gravitation<<' '<<deltaTime<<' '<<' '<<gravitation*deltaTime<<' '<<sign<<'\n';


      if ( speed < 0 || currentY > doubleJumperStartY) {
       sign*=-1;
       sign<0?speed=0:speed=1.0;
      }
      if (sign == 1) { // ударяется, получает скорость и теряет её
       long double deltaY = speed * deltaTime +  gravitation*deltaTime*deltaTime;
       speed = speed - gravitation*deltaTime;
       currentY -=  deltaY; // минус потому что чем меньше координата тем выше объедок
       doubleJumperLabel->setGeometry(currentX,  currentY, doubleJumperWidth, doubleJumperHeight);
      } else {    // падает и набирает скорость
       long double deltaY = speed * deltaTime +  gravitation*deltaTime*deltaTime;
       speed = speed + gravitation*deltaTime;
       currentY +=   deltaY; // плюс потому что чем юольше координата тем ниже объедок
       doubleJumperLabel->setGeometry(currentX,  currentY, doubleJumperWidth, doubleJumperHeight);
      }
      timer->setSingleShot(true);
      timer->start();
}

