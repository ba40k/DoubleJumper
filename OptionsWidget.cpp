//
// Created by radamir on 05.05.25.
//

#include "OptionsWidget.h"


void OptionsWidget::setDefaultStylnig(const QString &prefix, const QString &suffix, QPushButton *button) {
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
OptionsWidget::OptionsWidget(QWidget *parent) {
    setParent(parent);
    setFixedHeight(HEIGHT);
    setFixedWidth(WIDTH);
    backGroundLabel = new QLabel(this);
    backGroundLabel->setGeometry(0,0,WIDTH,HEIGHT);
    backGroundLabel->setPixmap(QPixmap(imagePrefixPath + backGroundPath));
    backGroundLabel->setScaledContents(true);
}

