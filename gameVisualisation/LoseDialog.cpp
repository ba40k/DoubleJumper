//
// Created by radamir on 03.05.25.
//

#include "LoseDialog.h"

#include <iostream>
#include <QPushButton>

LoseDialog::LoseDialog(QWidget *parent, int score) {
    background = new QLabel(this);
    background->setPixmap(QPixmap(imagePrefixPath + backgroundPath));
    background->setScaledContents(true);
    background->setGeometry(QRect(0, 0, WIDTH, HEIGHT));
    fontId = QFontDatabase::addApplicationFont(fontPath);
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    font = new QFont(fontFamilies.at(0), 30);
    setFont(*font);
    yourNameLabel = new QLabel(this);
    yourNameLabel->setFont(*font);
    yourNameLabel->setGeometry(QRect(100, 175, 200, 70));
    yourNameLabel->setText("your name: ");
    yourNameLineEdit = new QLineEdit(this);
    yourNameLineEdit->setStyleSheet(
        "QLineEdit {"
        "   background: transparent;" // Прозрачный фон
        "   border: none;" // Убираем рамку
        "   color: black;" // Цвет текста (можно изменить)
        "}"
    );
    yourNameLineEdit->setFont(*font);
    yourNameLineEdit->setGeometry(275, 175, 200, 70);

    yourScoreLabel = new QLabel(this);
    yourScoreLabel->setFont(*font);
    yourScoreLabel->setGeometry(QRect(100, 225, 300, 70));
    yourScoreLabel->setScaledContents(true);
    QString scoreString = "your score: " + QString::number(score);
    yourScoreLabel->setText(scoreString);
    saveButtonImagePath = "done.png";
    saveButton = new QPushButton(this);
    saveButton->setGeometry(QRect(100, 400, 112, 45));

    cancelButtonImagePath = "cancel.png";
    cancelButton = new QPushButton(this);

    cancelButton->setGeometry(QRect(300, 400, 112, 45));

    setDefaultStylnig(imagePrefixPath,saveButtonImagePath,saveButton);
    setDefaultStylnig(imagePrefixPath,cancelButtonImagePath,cancelButton);
}
void LoseDialog::setDefaultStylnig(const QString &prefix, const QString &suffix, QPushButton *button) {
    button->setStyleSheet(
        "QPushButton {"
        "   background-image: url(\"" + prefix + suffix + "\");"
        "   background-repeat: no-repeat;" // Не повторять изображение
        "   background-position: center;" // Центрировать
        "   border: none;" // Убрать стандартную рамку
        "   padding: 10px;" // Отступ для текста/иконки
        "}"
    );
}
LoseDialog::~LoseDialog() {
    delete font;
}
