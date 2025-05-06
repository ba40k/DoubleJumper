//
// Created by radamir on 15.04.25.
//

#ifndef DOUBLEJUMPER_H
#define DOUBLEJUMPER_H

#include <QLabel>
#include <QString>

#include "gameVisualisation/Theme.h"

class DoubleJumper {
    Theme* theme;
    const int WIDTH = 124;
    const int HEIGHT = 120;
    const int shiftFromBack=120 - 83; // расстояние от спины до ножки
    const int shiftFromFront = 30;  // расстояние от хоботка до ножки
    QString prefixPath ;
    bool hopped = false;
    int coordinateX;
    int coordinateY;
    long double speed;
    int8_t direction;
    bool orintation = false; // 0 - лево, 1 - право
    public:
    DoubleJumper(int coordinateX, int coordinateY, long double speed, long double direction);
    void setSpeed(long double speed);
    void changeDirection();
    void setCoordinateX(int coordinateX);
    void setCoordinateY(int coordinateY);
    void setHopped(bool hopped);
    QLabel* getLabel(QWidget *parent);
    long double getSpeed() const;
    long double getDirection() const;
    int getCoordinateX() const;
    int getCoordinateY() const;
    int getHeight() const ;
    int getWidth() const;
    void changeOrintation();
    bool getOrintation() const;
    int getLeftestHitboxPoint();
    int getRightestHitboxPoint();
    void setTheme(Theme* theme);
};



#endif //DOUBLEJUMPER_H
