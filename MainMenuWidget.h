//
// Created by radamir on 13.04.25.
//

#ifndef MAINMENUWIDGET_H
#define MAINMENUWIDGET_H

#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
#include <QString>

class MainMenuWidget : public QWidget {
    Q_OBJECT
    const int buttonWidth =222;
    const int buttonHeight = 80;
    const int crossSide = 44;
    QString backgroundImagePath;
    QString playButtonImagePath;
    QString highScoresButtonImagePath;
    QString optionsButtonImagePath;
    QString exitButtonImagePath;
    QPushButton *exitButton;
    QPushButton *playButton;
    QPushButton *optionsButton;
    QPushButton *highScoresButton;
    QLabel *backgroundLabel;
protected:
    void resizeEvent(QResizeEvent* event) override;
    public:
    MainMenuWidget(QWidget *parent = nullptr);


};



#endif //MAINMENUWIDGET_H
