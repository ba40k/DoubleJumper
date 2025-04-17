//
// Created by radamir on 17.04.25.
//

#ifndef ABSTRACTPLATFORMWIDGET_H
#define ABSTRACTPLATFORMWIDGET_H

#include <QWidget>
#include <QString>
#include<QLabel>
class AbstractPlatformWidget : public QWidget {
    protected:
    QString prefixPath;
    QString imagePath;
    QLabel *platformLabel;
    const int WIDTH = 120;
    const int HEIGHT = 32;
    public:
    AbstractPlatformWidget( QString prefixPath, QString imagePath, QWidget *parent = nullptr);
    virtual ~AbstractPlatformWidget() = default;

};



#endif //ABSTRACTPLATFORMWIDGET_H
