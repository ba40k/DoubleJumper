//
// Created by radamir on 05.05.25.
//

#ifndef RECORDSWIDGET_H
#define RECORDSWIDGET_H

#include <QDialog>
#include <QLabel>


class RecordsWidget : public QDialog {
    int fontId;
    QFont *font;
    const int recordWidth = 400;
    const int reordHeight = 120;
    QString fontPath = "/home/radamir/CLionProjects/doubleJumper/requirments/DoodleJump.ttf";
    int WIDTH = 640;
    int HEIGHT = 850;
    QString prefixPath = "requirments/Sprites/Doodle Jump/";

    QLabel* backGroundLabel;
    QString backGroundPath = "bck@2x.png";

    QString bottomImagePath = "high-scores-bottom@2x.png";
    QLabel* bottomLabel= nullptr;

    QString leftImagePath = "high-scores-left@2x.png";
    QLabel* leftLabel= nullptr;

    QString topImagePath = "high-scores-top@2x.png";
    QLabel* topLabel = nullptr;
    QVector<QLabel*> recordsLabels;

    int wheelShift=0;

    void wheelEvent(QWheelEvent* event) override;

    QString recordDelimiterPath = "record-delimiter@2x.png";
    void showRecords();
    void showFrame();
    int calculateLabelWidth(const QLabel* label, const QString& text);

    QTimer *timer;
    const int deltaTime = 20;

public:
    RecordsWidget(QWidget *parent = nullptr);
};



#endif //RECORDSWIDGET_H
