//
// Created by radamir on 25.04.25.
//

#ifndef BLUEPLATFORM_H
#define BLUEPLATFORM_H

#include "AbstractPlatform.h"

class BluePlatform  : public AbstractPlatform{
    double speed = 0.5;
public:
    BluePlatform(int coordinateX, int coordinateY, QString &imagePath);
    QLabel* getQLabel(QWidget *parent = nullptr)  override;
    void changeSpeedDirection();
    void updateCoordinate(int deltaTime);
    double getSpeedDirection();
};



#endif //BLUEPLATFORM_H
