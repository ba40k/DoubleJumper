//
// Created by radamir on 15.04.25.
//

#ifndef DOUBLEJUMPER_H
#define DOUBLEJUMPER_H

#include <QString>

class DoubleJumper {
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
    long double getSpeed() const;
    long double getDirection() const;
    int getCoordinateX() const;
    int getCoordinateY() const;
};



#endif //DOUBLEJUMPER_H
