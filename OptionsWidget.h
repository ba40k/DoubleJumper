//
// Created by radamir on 05.05.25.
//

#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "gameVisualisation/Theme.h"
class OptionsWidget : public QDialog {
    const int WIDTH = 640;
    const int HEIGHT = 850;
    QString imagePrefixPath = "requirments/Sprites/Doodle Jump/";
    bool soundOn = true;
    bool scoreMarkersOn = true;
    QString backGroundPath = "bck@2x.png";
    QString onImageOnPath = "on-button-on@2x.png";
    QString offImageOnPath = "off-button-on@2x.png";
    QString offImageOffPath = "off-button@2x.png";
    QString onImageOffPath = "on-button@2x.png";
    QString menuImagePath = "menu@2x.png";
    QString fontPath = "/home/radamir/CLionProjects/doubleJumper/requirments/DoodleJump.ttf";
    QString templateButtonImagePath = "button-template@2x.png";
    QString recordsFilePath = "/home/radamir/CLionProjects/doubleJumper/game/records.json";
    QString leftArrowPath = "left-arrow@2x.png";
    QString rightArrowPath = "right-arrow@2x.png";
    QLabel* optionsLabel;
    QLabel* backGroundLabel;
    QLabel* soundLabel;
    QLabel* scoreMarkersLabel;
    QPushButton* leftArrow;
    QPushButton* rightArrow;
    QPushButton* soundOnButton;
    QPushButton* soundOffButton;
    QPushButton* scoreMarkersOnButton;
    QPushButton* scoreMarkersOffButton;
    QPushButton* menuButton;
    QPushButton* resetHighScoresButton;
    int fontId;
    QFont *font;
    void setDefaultStylnig(const QString &prefix,const QString &suffix, QPushButton *button);
    void soundOnButtonClicked();
    void soundOffButtonClicked();
    void scoreMarkersOnButtonClicked();
    void scoreMarkersOffButtonClicked();
    void menuButtonClicked();
    void resetHighScoresButtonClicked();
    QVector<Theme*> themes;
    QLabel* currentThemePreview;
    static int currentSprite;
    static int currentBackGround;
public:
    OptionsWidget(QWidget* parent, bool currentSoundState, bool currentMarkersState);

};



#endif //OPTIONSWIDGET_H
