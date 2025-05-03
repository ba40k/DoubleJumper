//
// Created by radamir on 03.05.25.
//

#ifndef LOSEDIALOG_H
#define LOSEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QFontDatabase>

class LoseDialog : public QDialog {
private:
    const int HEIGHT = 500;
    const int WIDTH = 500;
    QLabel *background;
    QLabel *yourScoreLabel;
    QLabel *yourNameLabel;
    QLineEdit *yourNameLineEdit;
    QPushButton *saveButton;
    QString saveButtonImagePath;
    QPushButton *cancelButton;
    QString cancelButtonImagePath;
    QString fontPath = "/home/radamir/CLionProjects/doubleJumper/requirments/DoodleJump.ttf";
    QString imagePrefixPath = "requirments/Sprites/Doodle Jump/";
    QString backgroundPath = "bck@2x.png";

    void setDefaultStylnig(const QString &prefix, const QString &suffix, QPushButton *button);

    int fontId;
    QFont *font;

public:
    LoseDialog(QWidget *parent, int score);

    ~LoseDialog();
};


#endif //LOSEDIALOG_H
