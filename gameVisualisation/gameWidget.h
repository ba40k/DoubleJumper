//
// Created by radamir on 16.04.25.
//

#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QLabel>


class GameWidget : public QWidget{
    QString prefixPath;
    QString backgoundImagePath;
    QLabel *backgoundLabel;

    public:
    GameWidget(QWidget *parent = nullptr);

};



#endif //GAMEWIDGET_H
