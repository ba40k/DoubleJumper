//
// Created by radamir on 17.04.25.
//

#include "AbstractPlatformWidget.h"

AbstractPlatformWidget::AbstractPlatformWidget(QString prefixPath, QString imagePath, QWidget *parent) {
    this->prefixPath = prefixPath;
    this->imagePath = imagePath;
    platformLabel = new QLabel(this);
    platformLabel->setPixmap(QPixmap(prefixPath + imagePath));
}
