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




}
void MainMenuWidget::resizeEvent(QResizeEvent* event) {
    QPixmap bgPixmap(backgroundImagePath);
    bgPixmap = bgPixmap.scaled(size(), Qt::KeepAspectRatioByExpanding);
    backgroundLabel->setPixmap(bgPixmap);
    QWidget::resizeEvent(event);
}
