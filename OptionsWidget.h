//
// Created by radamir on 05.05.25.
//

#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
class OptionsWidget : public QDialog {
    const int WIDTH = 640;
    const int HEIGHT = 850;
    QString imagePrefixPath = "requirments/Sprites/Doodle Jump/";
    bool soundOn = true;
    bool scoreMarkers = true;
    QString backGroundPath = "bck@2x.png";
    QString onImageOnPath = "on-button-on@2x.png";
    QString offImageOnPath = "off-button-on@2x.png";
    QString offImageOffPath = "off-button@2x.png";
    QString onImageOffPath = "on-button@2x.png";
    QString menuImagePath = "menu@2x.png";
    QLabel* optionsLabel;
    QLabel* backGroundLabel;
    QPushButton* soundOnButton;
    QPushButton* soundOffButton;
    QPushButton* scoreMarkersOnButton;
    QPushButton* scoreMarkersOffButton;
    QPushButton* menuButton;
    void setDefaultStylnig(const QString &prefix,const QString &suffix, QPushButton *button);
public:
    OptionsWidget(QWidget* parent = nullptr);

};



#endif //OPTIONSWIDGET_H
