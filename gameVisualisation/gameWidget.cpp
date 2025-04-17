//
// Created by radamir on 16.04.25.
//

#include "gameWidget.h"

#include "../platforms/GreenPlatform.h"

GameWidget::GameWidget(QWidget *parent) {
    prefixPath = "requirments/Sprites/Doodle Jump/";
    backgoundImagePath = "bck@2x.png";
    backgoundLabel = new QLabel(this);
    resize(parent->width(), parent->height());

    backgoundLabel->setScaledContents(true);
    backgoundLabel->setGeometry(QRect(0, 0, parent->width(), parent->height()));

    backgoundLabel->setPixmap(QPixmap(prefixPath + backgoundImagePath));




}
