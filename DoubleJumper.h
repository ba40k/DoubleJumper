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
     QString prefixPath ;
    QString leftOrientedSpritePath ;
    QString rightOrientedSpritePath;
    int coordinateX;
    int coordinateY;
    const int hitBoxWidth = 57;
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
    int getHeight() const ;
    int getWidth() const;
    int getHitboxWidth() const;
};



#endif //DOUBLEJUMPER_H
