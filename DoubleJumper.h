//
// Created by radamir on 15.04.25.
//

#ifndef DOUBLEJUMPER_H
#define DOUBLEJUMPER_H

#include <QLabel>
#include <QString>

class DoubleJumper {
    const int WIDTH = 124;
    const int HEIGHT = 120;
    QString prefixPath = "requirments/Sprites/Doodle Jump/";
    QString leftOrientedSpritePath = "lic-left@2x.png";
    QString rightOrientedSpritePath = "lic-right@2x.png";
    int coordinateX;
    int coordinateY;

    long double speed;
    int8_t direction;

    public:
    DoubleJumper(int coordinateX, int coordinateY, long double speed, long double direction);
    void setSpeed(long double speed);
    void changeDirection();
    void setCoordinateX(int coordinateX);
    void setCoordinateY(int coordinateY);
    QLabel* getLeftOrientedLabel(QWidget *parent);
    QLabel* getRightOrientedLabel(QWidget *parent);
    long double getSpeed() const;
    long double getDirection() const;
    int getCoordinateX() const;
    int getCoordinateY() const;
};



#endif //DOUBLEJUMPER_H
