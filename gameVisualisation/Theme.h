//
// Created by radamir on 06.05.25.
//

#ifndef THEME_H
#define THEME_H
#include <QVector>
#include <QString>


class Theme {
protected:
    QString backgroundImagePath;
    QString leftOrientedImagePath;
    QString rightOrientedImagePath;
    QString leftOrientedHoppedImagePath;
    QString rightOrientedHoppedImagePath;
    QString propellerImagePath;
    QString jetpackImagePath;
    QString gameTileImagePath;
    QString scoreBarImagePath;
public:
    QString getBackgroundImagePath();
    QString getLeftOrientedImagePath();
    QString getRightOrientedImagePath();
    QString getLeftOrientedHoppedImagePath();
    QString getRightOrientedHoppedImagePath();
    QString getPropellerImagePath();
    QString getJetpackImagePath();
    QString getGameTileImagePath();
};
class DefaultTheme : public Theme {
    public:
    DefaultTheme();
}
class HaloweenTheme : public Theme {
    public:
    HaloweenTheme();
};
class JungleTheme : public Theme {
public:
    JungleTheme();
};
class Underwater : public Theme {
    public:
    Underwater();
};



#endif //THEME_H
