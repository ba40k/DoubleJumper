//
// Created by radamir on 16.04.25.
//

#ifndef GREENPLATFORM_H
#define GREENPLATFORM_H

#include "AbstractPlatform.h"

class GreenPlatform  : public AbstractPlatform{
    public:
    GreenPlatform(int coordinateX, int coordinateY, QString &imagePath);
    QLabel* getQLabel(QWidget *parent = nullptr)  override;
};



#endif //GREENPLATFORM_H
