//
// Created by radamir on 13.04.25.
//

#ifndef MAINMENUWIDGET_H
#define MAINMENUWIDGET_H

#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QLabel>
class MainMenuWidget : public QWidget {
    Q_OBJECT
    QString prefixPath;
    const int buttonWidth =222;
    const int buttonHeight = 80;
    const int crossSide = 44;
    QString backgroundImagePath;
    QString playButtonImagePath;
    QString highScoresButtonImagePath;
    QString optionsButtonImagePath;
    QString exitButtonImagePath;
    QString gameTitleImagePath;
    QLabel *gameTitleLabel;
    QPushButton *exitButton;
    QPushButton *playButton;
    QPushButton *optionsButton;
    QPushButton *highScoresButton;
    QLabel *backgroundLabel;
protected:

    public:
    MainMenuWidget(QWidget *parent = nullptr);


};



#endif //MAINMENUWIDGET_H
